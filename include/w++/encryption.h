//
// Created by Alan de Freitas on 17/10/2017.
//

#ifndef WPP_ENCRYPTION_H
#define WPP_ENCRYPTION_H

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

namespace wpp {
    typedef unsigned char byte;

    template<typename T>
    struct zallocator {
        public:
            typedef T value_type;
            typedef value_type *pointer;
            typedef const value_type *const_pointer;
            typedef value_type &reference;
            typedef const value_type &const_reference;
            typedef std::size_t size_type;
            typedef std::ptrdiff_t difference_type;

            pointer address(reference v) const { return &v; }

            const_pointer address(const_reference v) const { return &v; }

            pointer allocate(size_type n, const void *hint = 0) {
                if (n > std::numeric_limits<size_type>::max() / sizeof(T)) {
                    throw std::bad_alloc();
                }
                return static_cast<pointer> (::operator new(n * sizeof(value_type)));
            }

            void deallocate(pointer p, size_type n) {
                OPENSSL_cleanse(p, n * sizeof(T));
                ::operator delete(p);
            }

            size_type max_size() const {
                return std::numeric_limits<size_type>::max() / sizeof(T);
            }

            template<typename U>
            struct rebind {
                typedef zallocator<U> other;
            };

            void construct(pointer ptr, const T &val) {
                new(static_cast<T *>(ptr)) T(val);
            }

            void destroy(pointer ptr) {
                static_cast<T *>(ptr)->~T();
            }

            #if __cpluplus >= 201103L
            template<typename U, typename... Args>
        void construct (U* ptr, Args&&  ... args) {
            ::new (static_cast<void*> (ptr) ) U (std::forward<Args> (args)...);
        }

        template<typename U>
        void destroy(U* ptr) {
            ptr->~U();
        }
            #endif
    };

    typedef std::basic_string<char, std::char_traits<char>, zallocator<char> > secure_string;
    using EVP_CIPHER_CTX_free_ptr = std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;

    void handleErrors(void)
    {
        ERR_print_errors_fp(stderr);
        abort();
    }

    void digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len)
    {
        // Create a Message Digest context
        EVP_MD_CTX *mdctx;
        if((mdctx = EVP_MD_CTX_create()) == NULL)
            handleErrors();

        // Initialise the context by identifying the algorithm to be used (built-in algorithms are defined in evp.h)
        if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
            handleErrors();

        // Provide the message whose digest needs to be calculated. Messages can be divided into sections and provided over a number of calls to the library if necessary
        if(1 != EVP_DigestUpdate(mdctx, message, message_len))
            handleErrors();

        // Caculate the digest
        if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
            handleErrors();

        // Clean up the context if no longer required
        if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))
            handleErrors();

        EVP_MD_CTX_destroy(mdctx);
    }

    void gen_params(vector<byte>& key, vector<byte>& iv, unsigned int KEY_SIZE = 32, unsigned int BLOCK_SIZE = 16)
    {
        key.resize(KEY_SIZE);
        iv.resize(BLOCK_SIZE);
        int rc = RAND_bytes(key.data(), KEY_SIZE);
        if (rc != 1)
            throw std::runtime_error("RAND_bytes key failed");

        rc = RAND_bytes(iv.data(), BLOCK_SIZE);
        if (rc != 1)
            throw std::runtime_error("RAND_bytes for iv failed");
    }

    void aes_encrypt(const byte *key, const byte* iv, const secure_string& ptext, secure_string& ctext, unsigned int KEY_SIZE = 32, unsigned int BLOCK_SIZE = 16)
    {
        EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
        int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
        if (rc != 1){
            //ctext = "EVP_EncryptInit_ex failed";
            ctext = "";
        }

        // Recovered text expands upto BLOCK_SIZE
        ctext.resize(ptext.size()+BLOCK_SIZE);
        int out_len1 = (int)ctext.size();

        rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1, (const byte*)&ptext[0], (int)ptext.size());
        if (rc != 1){
            //ctext = "EVP_EncryptUpdate failed";
            ctext = "";
        }

        int out_len2 = (int)ctext.size() - out_len1;
        rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0]+out_len1, &out_len2);
        if (rc != 1) {
            //ctext = "EVP_EncryptFinal_ex failed";
            ctext = "";
        }

        // Set cipher text size now that we know it
        ctext.resize(out_len1 + out_len2);
    }

    void aes_decrypt(const byte *key, const byte* iv, const secure_string& ctext, secure_string& rtext, bool& success, unsigned int KEY_SIZE = 32, unsigned int BLOCK_SIZE = 16)
    {
        EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
        int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
        if (rc != 1){
            success = false; // "EVP_DecryptInit_ex failed";
            rtext = "";
        }


        // Recovered text contracts upto BLOCK_SIZE
        rtext.resize(ctext.size());
        int out_len1 = (int)rtext.size();

        rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1, (const byte*)&ctext[0], (int)ctext.size());
        if (rc != 1){
            success = false; // "EVP_DecryptUpdate failed";
            rtext = "";
        }

        int out_len2 = (int)rtext.size() - out_len1;
        rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0]+out_len1, &out_len2);
        if (rc != 1){
            success = false; // "EVP_DecryptFinal_ex failed";
            rtext = "";
        }

        // Set recovered text size now that we know it
        rtext.resize(out_len1 + out_len2);
        success = true;
    }

}

#endif //WPP_ENCRYPTION_H
