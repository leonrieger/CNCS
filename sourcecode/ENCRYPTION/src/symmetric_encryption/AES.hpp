#pragma once

#include <openssl/evp.h>
#include <stdint.h>
#include <string>
// #include <openssl/rand.h>

namespace CNCS::cryptography {
    enum AES_TYPE {
        AES128 = 1,
        AES192 = 2,
        AES256 = 3,
        // !!!DO NOT, UNDER NO CIRCUMSTANCES, CHANGE THE VALUES!!!
    };

    class AES {
    public:
        // uses CBC
        AES(const AES_TYPE& type);

        bool set_key(const char* key, size_t key_len);
        bool set_iv(const char* iv);

        bool generate_key();
        bool generate_iv();

        bool get_key(char* key, size_t& key_len);
        bool get_iv(char* iv);

        bool encrypt(std::string& msg_to_encrypt, uint8_t* encrypted_text,
                     size_t& encypted_text_len);

        bool decrypt(uint8_t* encrypted_text, size_t& encypted_text_len,
                     std::string& msg_to_encrypt);

        ~AES();

    private:
        EVP_CIPHER_CTX* context = nullptr;
        const AES_TYPE aes_type;
        uint8_t key[32] = {};
        // used for randomizing encryption output
        uint8_t initialisation_vector[16] = {0};
        bool is_key_set = false;

        // 64bit + aes_type * 64 = key_len
    };
} // namespace CNCS::cryptography
