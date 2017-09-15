#pragma once

// predicates determine whether if a substring is contained in the input string under various conditions
#include <boost/algorithm/string/predicate.hpp>
// STL
#include <array>

// class the keeps the request data (but doesn't process much)
#include "http_request.h"
// wrappers for boost::asio::tcp::socket, representing connection to the client
#include "socket_adaptors.h"
// SHA1 cryptographic hash function algorithm
#include "TinySHA1.hpp"
#include "function_traits.h"

namespace wpp
{
    namespace websocket
    {
        // actions depend on the socket state
        enum class WebSocketReadState
        {
            MiniHeader,
            Len16,
            Len64,
            Mask,
            Payload,
        };

        // abstract interface for uses of a connection
		struct connection
		{
            // return a binary to the connected client
            virtual void send_binary(const std::string& msg) = 0;
            // return plain text to the connected client
            virtual void send_text(const std::string& msg) = 0;
            // end the connection
            virtual void close(const std::string& msg = "quit") = 0;
            virtual ~connection(){}

            // set and update a pointer to the user data
            void userdata(void* u) { userdata_ = u; }
            void* userdata() { return userdata_; }

        private:
            void* userdata_;
		};

        // concrete implementation of the connection (dependant on the type of socket adaptor)
		template <typename Adaptor>
        class Connection : public connection
        {
			public:
                /// \brief Open/construct a connection
                /// \param req request struct from http_request.h
                /// \param adaptor some adaptor (normal or ssl) from socket_adaptors.h
                /// \param open_handler function to start connection
                /// \param message_handler function to send message
                /// \param close_handler function to close connection
                /// \param error_handler function to find error
				Connection(const wpp::request& req, Adaptor&& adaptor,
						std::function<void(wpp::websocket::connection&)> open_handler,
						std::function<void(wpp::websocket::connection&, const std::string&, bool)> message_handler,
						std::function<void(wpp::websocket::connection&, const std::string&)> close_handler,
						std::function<void(wpp::websocket::connection&)> error_handler)
					: adaptor_(std::move(adaptor)), open_handler_(std::move(open_handler)), message_handler_(std::move(message_handler)), close_handler_(std::move(close_handler)), error_handler_(std::move(error_handler))
				{
                    // case insensitive comparison
                    // Upgrade header can be Upgrade: HTTPS/1.3, IRC/6.9, RTA/x11, websocket
                    // if request is not asking to upgrade the protocol to websocket
					if (!boost::iequals(req.get_header_value("upgrade"), "websocket"))
					{
                        // close the adaptor and delete the connection
						adaptor.close();
						delete this;
						return;
					}
                    // WebSocket also uses this mechanism to set up a connection with a HTTP server in a compatible way
                    // The WebSocket Protocol has two parts: a handshake to establish the upgraded connection, then the actual data transfer
                    // Once the handshake is completed successfully, data transfer begins

                    // To prove that the handshake was received, the server has to take two pieces of information and combine them to form a response
                    // first piece of information comes from the |Sec-WebSocket-Key| header field in the client handshake:
					// Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==
					// Sec-WebSocket-Version: 13
                    // For this header field, the server has to take the value (as present in the header field, e.g. the base64-encoded [RFC4648] version minus any leading and trailing whitespace), and concatenate this with the Globally Unique Identifier (GUID, [RFC4122]) "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" in string form, which is unlikely to be used by network endpoints that do not understand the WebSocket protocol
                    std::string magic = req.get_header_value("Sec-WebSocket-Key") +  "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
                    //  SHA-1 hash (160 bits), base64-encoded (see Section 4 of [RFC4648]), of this concatenation is then returned in the server's handshake [FIPS.180-2.2002]
                    sha1::SHA1 s;
                    s.processBytes(magic.data(), magic.size());
                    uint8_t digest[20];
                    s.getDigestBytes(digest);
                    //  SHA-1 hash (160 bits), base64-encoded (see Section 4 of [RFC4648]), of this concatenation is then returned in the server's handshake [FIPS.180-2.2002]
                    // Connection::start the connection / handshake with the digest of the magic string
                    start(wpp::utility::base64encode((char*)digest, 20));
				}

                template<typename CompletionHandler>
                void dispatch(CompletionHandler handler)
                {
                    adaptor_.get_io_service().dispatch(handler);
                }

                template<typename CompletionHandler>
                void post(CompletionHandler handler)
                {
                    adaptor_.get_io_service().post(handler);
                }

                void send_pong(const std::string& msg)
                {
                    dispatch([this, msg]{
                        char buf[3] = "\x8A\x00";
                        buf[1] += msg.size();
                        write_buffers_.emplace_back(buf, buf+2);
                        write_buffers_.emplace_back(msg);
                        do_write();
                    });
                }

                void send_binary(const std::string& msg) override
                {
                    dispatch([this, msg]{
                        auto header = build_header(2, msg.size());
                        write_buffers_.emplace_back(std::move(header));
                        write_buffers_.emplace_back(msg);
                        do_write();
                    });
                }

                void send_text(const std::string& msg) override
                {
                    dispatch([this, msg]{
                        auto header = build_header(1, msg.size());
                        write_buffers_.emplace_back(std::move(header));
                        write_buffers_.emplace_back(msg);
                        do_write();
                    });
                }

                void close(const std::string& msg) override
                {
                    dispatch([this, msg]{
                        has_sent_close_ = true;
                        if (has_recv_close_ && !is_close_handler_called_)
                        {
                            is_close_handler_called_ = true;
                            if (close_handler_)
                                close_handler_(*this, msg);
                        }
                        auto header = build_header(0x8, msg.size());
                        write_buffers_.emplace_back(std::move(header));
                        write_buffers_.emplace_back(msg);
                        do_write();
                    });
                }

            protected:

                std::string build_header(int opcode, size_t size)
                {
                    char buf[2+8] = "\x80\x00";
                    buf[0] += opcode;
                    if (size < 126)
                    {
                        buf[1] += size;
                        return {buf, buf+2};
                    }
                    else if (size < 0x10000)
                    {
                        buf[1] += 126;
                        *(uint16_t*)(buf+2) = htons((uint16_t)size);
                        return {buf, buf+4};
                    }
                    else
                    {
                        buf[1] += 127;
                        *(uint64_t*)(buf+2) = ((1==htonl(1)) ? (uint64_t)size : ((uint64_t)htonl((size) & 0xFFFFFFFF) << 32) | htonl((size) >> 32));
                        return {buf, buf+10};
                    }
                }

                void start(std::string&& hello)
                {
                    // reply the handshake from the client
                    static std::string header = "HTTP/1.1 101 Switching Protocols\r\n"
                        "Upgrade: websocket\r\n"
                        "Connection: Upgrade\r\n"
                        "Sec-WebSocket-Accept: ";
                    static std::string crlf = "\r\n";
                    // push back header, and hand shake on write_buffers_ (vector of strings)
                    write_buffers_.emplace_back(header);
                    write_buffers_.emplace_back(std::move(hello));
                    write_buffers_.emplace_back(crlf);
                    write_buffers_.emplace_back(crlf);
                    // write everything on the buffer to the client
                    do_write();
                    // if there is a function to open the handler (receiving the connection)
                    if (open_handler_)
                        // call the function on this very handler
                        open_handler_(*this);
                    // read the response (and keep reading until connection is over)
                    do_read();
                }

                void do_read()
                {
                    is_reading = true;
                    // reading from the client depends on what is expected
                    switch(state_)
                    {
                        // miniheader is the initial state
                        case WebSocketReadState::MiniHeader:
                            {
                                //boost::asio::async_read(adaptor_.socket(), boost::asio::buffer(&mini_header_, 1),
                                // asynchronously read data from the stream socket
                                // buffer = where to put the data
                                // The handler to be called when the read operation completes (data, size)
                                adaptor_.socket().async_read_some(boost::asio::buffer(&mini_header_, 2), 
                                    [this](const boost::system::error_code& ec, std::size_t bytes_transferred) 
                                    {
                                        // if we finished reading
                                        is_reading = false;
                                        mini_header_ = htons(mini_header_);
                                        if (wpp_settings::enable_debug){
                                            if (!ec && bytes_transferred != 2)
                                            {
                                                throw std::runtime_error("WebSocket:MiniHeader:async_read fail:asio bug?");
                                            }
                                        }
                                        // there is no error and the header is OK
                                        if (!ec && ((mini_header_ & 0x80) == 0x80))
                                        {
                                            // identify new read state
                                            if ((mini_header_ & 0x7f) == 127)
                                            {
                                                state_ = WebSocketReadState::Len64;
                                            }
                                            else if ((mini_header_ & 0x7f) == 126)
                                            {
                                                state_ = WebSocketReadState::Len16;
                                            }
                                            else
                                            {
                                                remaining_length_ = mini_header_ & 0x7f;
                                                state_ = WebSocketReadState::Mask;
                                            }
                                            // try reading again in a new read state
                                            do_read();
                                        }
                                        else
                                        {
                                            // close the connection and destroy it
                                            close_connection_ = true;
                                            adaptor_.close();
                                            // calls the function that handles error on this very connection
                                            if (error_handler_)
                                                error_handler_(*this);
                                            // destroy
                                            check_destroy();
                                        }
                                    });
                            }
                            break;
                        case WebSocketReadState::Len16:
                            {
                                remaining_length_ = 0;
                                boost::asio::async_read(adaptor_.socket(), boost::asio::buffer(&remaining_length_, 2), 
                                    [this](const boost::system::error_code& ec, std::size_t bytes_transferred) 
                                    {
                                        is_reading = false;
                                        remaining_length_ = ntohs(*(uint16_t*)&remaining_length_);
                                        if (wpp_settings::enable_debug) {
                                            if (!ec && bytes_transferred != 2) {
                                                throw std::runtime_error("WebSocket:Len16:async_read fail:asio bug?");
                                            }
                                        }
                                        // if there is no error, move to mask state
                                        if (!ec)
                                        {
                                            state_ = WebSocketReadState::Mask;
                                            do_read();
                                        }
                                        else
                                        {
                                            // close connection
                                            close_connection_ = true;
                                            adaptor_.close();
                                            if (error_handler_)
                                                error_handler_(*this);
                                            check_destroy();
                                        }
                                    });
                            }
                            break;
                        case WebSocketReadState::Len64:
                            {
                                boost::asio::async_read(adaptor_.socket(), boost::asio::buffer(&remaining_length_, 8), 
                                    [this](const boost::system::error_code& ec, std::size_t bytes_transferred) 
                                    {
                                        is_reading = false;
                                        remaining_length_ = ((1==ntohl(1)) ? (remaining_length_) : ((uint64_t)ntohl((remaining_length_) & 0xFFFFFFFF) << 32) | ntohl((remaining_length_) >> 32));
                                        if (wpp_settings::enable_debug) {
                                            if (!ec && bytes_transferred != 8) {
                                                throw std::runtime_error("WebSocket:Len16:async_read fail:asio bug?");
                                            }
                                        }
                                        // if there is no error, move to mask state
                                        if (!ec)
                                        {
                                            state_ = WebSocketReadState::Mask;
                                            do_read();
                                        }
                                        else
                                        {
                                            close_connection_ = true;
                                            adaptor_.close();
                                            if (error_handler_)
                                                error_handler_(*this);
                                            check_destroy();
                                        }
                                    });
                            }
                            break;
                        case WebSocketReadState::Mask:
                                boost::asio::async_read(adaptor_.socket(), boost::asio::buffer((char*)&mask_, 4), 
                                    [this](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                    {
                                        is_reading = false;
                                        if (wpp_settings::enable_debug) {
                                            if (!ec && bytes_transferred != 4) {
                                                throw std::runtime_error("WebSocket:Mask:async_read fail:asio bug?");
                                            }
                                        }
                                        // if there is no error, move to payload state
                                        if (!ec)
                                        {
                                            state_ = WebSocketReadState::Payload;
                                            do_read();
                                        }
                                        else
                                        {
                                            // close connection
                                            close_connection_ = true;
                                            if (error_handler_)
                                                error_handler_(*this);
                                            adaptor_.close();
                                        }
                                    });
                            break;
                        case WebSocketReadState::Payload:
                            {
                                size_t to_read = buffer_.size();
                                if (remaining_length_ < to_read)
                                    to_read = remaining_length_;
                                // read little by little
                                adaptor_.socket().async_read_some( boost::asio::buffer(buffer_, to_read), 
                                    [this](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                    {
                                        // when finished reading
                                        is_reading = false;
                                        // if there is no error (that is, it didn't finish reading)
                                        if (!ec)
                                        {
                                            // we keep this fragment in a string
                                            fragment_.insert(fragment_.end(), buffer_.begin(), buffer_.begin() + bytes_transferred);
                                            // calculate remaining
                                            remaining_length_ -= bytes_transferred;
                                            // if remaining is 0, we've finished reading the message
                                            if (remaining_length_ == 0)
                                            {
                                                // so we handle the fragment we have and go back to reading in the original state
                                                handle_fragment();
                                                state_ = WebSocketReadState::MiniHeader;
                                                do_read();
                                            }
                                        }
                                        else
                                        {
                                            close_connection_ = true;
                                            if (error_handler_)
                                                error_handler_(*this);
                                            adaptor_.close();
                                        }
                                    });
                            }
                            break;
                    }
                }

                bool is_FIN()
                {
                    return mini_header_ & 0x8000;
                }

                int opcode()
                {
                    return (mini_header_ & 0x0f00) >> 8;
                }

                void handle_fragment()
                {
                    for(decltype(fragment_.length()) i = 0; i < fragment_.length(); i ++)
                    {
                        fragment_[i] ^= ((char*)&mask_)[i%4];
                    }
                    // check the kind of fragment
                    switch(opcode())
                    {
                        case 0: // Continuation
                            {
                                message_ += fragment_;
                                if (is_FIN())
                                {
                                    if (message_handler_)
                                        message_handler_(*this, message_, is_binary_);
                                    message_.clear();
                                }
                            }
                        case 1: // Text
                            {
                                is_binary_ = false;
                                message_ += fragment_;
                                if (is_FIN())
                                {
                                    if (message_handler_)
                                        message_handler_(*this, message_, is_binary_);
                                    message_.clear();
                                }
                            }
                            break;
                        case 2: // Binary
                            {
                                is_binary_ = true;
                                message_ += fragment_;
                                if (is_FIN())
                                {
                                    if (message_handler_)
                                        message_handler_(*this, message_, is_binary_);
                                    message_.clear();
                                }
                            }
                            break;
                        case 0x8: // Close
                            {
                                has_recv_close_ = true;
                                if (!has_sent_close_)
                                {
                                    close(fragment_);
                                }
                                else
                                {
                                    adaptor_.close();
                                    close_connection_ = true;
                                    if (!is_close_handler_called_)
                                    {
                                        if (close_handler_)
                                            close_handler_(*this, fragment_);
                                        is_close_handler_called_ = true;
                                    }
                                    check_destroy();
                                }
                            }
                            break;
                        case 0x9: // Ping
                            {
                                send_pong(fragment_);
                            }
                            break;
                        case 0xA: // Pong
                            {
                                pong_received_ = true;
                            }
                            break;
                    }

                    fragment_.clear();
                }

                void do_write()
                {
                    // if there are no buffers to send
                    if (sending_buffers_.empty())
                    {
                        // we'll send what we wrone on write_buffers
                        sending_buffers_.swap(write_buffers_);
                        // asio's buffer (that doesn't own the underlying data)
                        std::vector<boost::asio::const_buffer> buffers;
                        // asio's buffers keep the sending_buffers
                        buffers.reserve(sending_buffers_.size());
                        for(auto& s:sending_buffers_)
                        {
                            buffers.emplace_back(boost::asio::buffer(s));
                        }
                        // start an asynchronous operation to write a certain amount of data to a stream
                        // raw or ssl socket, buffers, and function that handles the writting
                        boost::asio::async_write(adaptor_.socket(), buffers, 
                            [&](const boost::system::error_code& ec, std::size_t /*bytes_transferred*/)
                            {
                                sending_buffers_.clear();
                                // if there is error (stop sign) AND we shouldn't close the connect
                                if (!ec && !close_connection_)
                                {
                                    // if there is still something in the write_buffers
                                    if (!write_buffers_.empty())
                                        do_write(); // recursively call the function
                                    if (has_sent_close_)
                                        close_connection_ = true;
                                }
                                else
                                {
                                    // if we finished transmitting the message
                                    close_connection_ = true;
                                    check_destroy();
                                }
                            });
                    }
                }

                void check_destroy()
                {
                    // check if we're going to close and if there is nothing else to do

                    //if (has_sent_close_ && has_recv_close_)
                    if (!is_close_handler_called_)
                        if (close_handler_)
                            close_handler_(*this, "uncleanly");
                    if (sending_buffers_.empty() && !is_reading)
                        delete this;
                }
			private:
				Adaptor adaptor_;

                std::vector<std::string> sending_buffers_;
                std::vector<std::string> write_buffers_;

                std::array<char, 4096> buffer_;
                bool is_binary_;
                std::string message_;
                std::string fragment_;
                WebSocketReadState state_{WebSocketReadState::MiniHeader};
                uint64_t remaining_length_{0};
                bool close_connection_{false};
                bool is_reading{false};
                uint32_t mask_;
                uint16_t mini_header_;
                bool has_sent_close_{false};
                bool has_recv_close_{false};
                bool error_occured_{false};
                bool pong_received_{false};
                bool is_close_handler_called_{false};

				std::function<void(wpp::websocket::connection&)> open_handler_;
				std::function<void(wpp::websocket::connection&, const std::string&, bool)> message_handler_;
				std::function<void(wpp::websocket::connection&, const std::string&)> close_handler_;
				std::function<void(wpp::websocket::connection&)> error_handler_;
        };
    }
}
