//
// Created by Alan de Freitas on 19/10/2017.
//

#include "response.h"
#include "application.h"

namespace wpp {

    void request::parse_cookies()
    {
        // get the cookies from the user
        int count = this->headers.count("Cookie");
        if (!count) {
            return; // return if there are no cookies
        }
        if (count > 1)
        {
            return;
        }
        // string with all cookies
        std::string cookies = this->get_header_value("Cookie");
        size_t pos = 0;
        while(pos < cookies.size())
        {
            // find position of next "=" of a cookie
            size_t pos_equal = cookies.find('=', pos);
            if (pos_equal == cookies.npos)
                break;
            // then we have the cookie's key from pos to pos_equal
            std::string name = cookies.substr(pos, pos_equal-pos);
            boost::trim(name);

            // then we look for the cookies value
            pos = pos_equal+1;
            // ignore spaces
            while(pos < cookies.size() && cookies[pos] == ' ') pos++;
            // check if there are still chars to check
            if (pos == cookies.size())
                break;
            // begin to parse string
            std::string value;
            // cookie value has to begin with " (opening string) or ; (empty cookie)
            if (cookies[pos] == '"')
            {
                int dquote_meet_count = 0;
                pos ++;
                size_t pos_dquote = pos-1;
                // look for closing quote after position of opening quote (and skipping the escaped quotes \\")
                do
                {
                    pos_dquote = cookies.find('"', pos_dquote+1);
                    dquote_meet_count ++;
                } while(pos_dquote < cookies.size() && cookies[pos_dquote-1] == '\\');
                // break if we got to the last position in the string
                if (pos_dquote == cookies.npos)
                    break;
                // if there are no escaped \\s we just copy the whole thing as the cookie value
                if (dquote_meet_count == 1)
                    value = cookies.substr(pos, pos_dquote - pos);
                    // else
                else
                {
                    // reserve space for the whole value
                    value.clear();
                    value.reserve(pos_dquote-pos);
                    // go position by position
                    for(size_t p = pos; p < pos_dquote; p++)
                    {
                        // FIXME minimal escaping
                        // TODO: improve the parse cookie function
                        // if it's a \\ that comes before the last position found
                        if (cookies[p] == '\\' && p + 1 < pos_dquote)
                        {
                            p++;
                            // if the pos_dquote represents a legitimate \\ ou "
                            if (cookies[p] == '\\' || cookies[p] == '"')
                                // we copy the value without the \\ straight to the value string
                                value += cookies[p];
                            else
                            {
                                // else, just add \\ and whatever follows
                                value += '\\';
                                value += cookies[p];
                            }
                        }
                        else
                            // if it's not a \\ we just copy it
                            value += cookies[p];
                    }
                }
                // we put the cookies we found in the jar
                cookie_jar.emplace(std::move(name), std::move(value));
                // find where the next cookie begins
                pos = cookies.find(";", pos_dquote+1);
                // check if it's not over
                if (pos == cookies.npos)
                    break;
                pos++;
                // skip spaces
                while(pos < cookies.size() && cookies[pos] == ' ') pos++;
                // check if it's not over
                if (pos == cookies.size())
                    break;
            }
                // else (if there is no " to mark the beggining of a cookie)
            else
            {
                // look for the next cookie
                size_t pos_semicolon = cookies.find(';', pos);
                // put whatever is between = and the ; (even if it's without the "s)
                value = cookies.substr(pos, pos_semicolon - pos);
                // trim the value (probably is going to be empty but this is just a workaround on an invalid input)
                boost::trim(value);
                // put the cookie in the jar
                cookie_jar.emplace(std::move(name), std::move(value));
                // go to next cookie
                pos = pos_semicolon;
                // check if it's over
                if (pos == cookies.npos)
                    break;
                // advance
                pos ++;
                // skip spaces
                while(pos < cookies.size() && cookies[pos] == ' ') pos++;
                // check if it's over
                if (pos == cookies.size())
                    break;
            }
        }
    }


    request& request::session_regenerate(response& res) {
        // generate session id
        std::string unix_timestamp = to_string(std::time(nullptr));

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::minstd_rand0 generator(seed);
        string random_number = to_string(generator());

        std::random_device rd;

        string total;
        if (rd.entropy() > 0){
            string real_random_number = to_string(rd());
            total = unix_timestamp + this->remote_endpoint_address + random_number + real_random_number;
        } else {
            total = unix_timestamp + this->remote_endpoint_address + random_number;
        }

        // digest the id
        string serialized_session_id = parent_application->digest(total);

        if (!this->session_data.is_object()){
            this->session_data = json::object();
        }
        this->session_data["id"] = serialized_session_id;
        this->session_data["ip_address"] = this->remote_endpoint_address;
        this->session_data["user_agent"] = this->user_agent_header();
        this->session_data["port"] = to_string(this->remote_endpoint_port);
        this->session_data["last_activity"] = to_string(std::time(nullptr));

        parent_application->get_cache().put("session_"+serialized_session_id,session_data, parent_application->max_session_inactive_time_);

        this->session_data = std::move(session_data);
        
        return *this;
    }


    std::string request::url() const {
        int slashes = 0;
        if (!parent_application->web_root_path().empty() && parent_application->web_root_path().back() == '/'){
            slashes++;
        }
        if (!url_.empty() && url_.front() == '/'){
            slashes++;
        }
        switch (slashes){
            case 0:
                return parent_application->web_root_path() + "/" + url_;
                break;
            case 1:
                return parent_application->web_root_path() + url_;
                break;
            case 2:
                return parent_application->web_root_path() + std::string(url_.begin()+1,url_.end());
                break;
            default:
                return "";
        }
    }

    // includes query string
    std::string request::full_url() const {
        if (query_string.empty()){
            return url();
        } else {
            return url() + "?" + query_string;
        }
    }

    string request::route_name() {
        return this->current_route->_name;
    }

}