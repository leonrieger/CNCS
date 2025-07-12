#pragma once

#include <array>
#include <openssl/evp.h>
#include <stdint.h>
#include <string>
#include <vector>
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

        bool set_key(std::array<uint8_t, 32>& key_arr);
        bool set_key(std::array<uint8_t, 24>& key_arr);
        bool set_key(std::array<uint8_t, 16>& key_arr);

        bool set_iv(std::array<uint8_t, 16>& iv_array);

        bool generate_key();
        bool generate_iv();

        bool get_key(char* key, size_t& key_len);
        bool get_iv(char* iv);

        bool encrypt(std::string& msg_to_encrypt,
                     std::vector<uint8_t>& encrypted_msg);

        bool decrypt(std::vector<uint8_t>& encrypted_msg,
                     std::string& decrypted_msg);

        ~AES();

    private:
        EVP_CIPHER_CTX* context = nullptr;
        const EVP_CIPHER* encryption_type = nullptr;

        const AES_TYPE aes_type;
        std::array<uint8_t, 32> key_array = {0};
        // used for randomizing encryption output
        std::array<uint8_t, 16> initialisation_vector = {0};

        bool is_key_set = false;
        bool is_iv_set = false;
    };
} // namespace CNCS::cryptography
