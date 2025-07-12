#pragma once

#include <openssl/evp.h>
#include <string>

namespace CNCS::cryptography {
    class SHA256 {
    public:
        SHA256();

        bool encrypt(std::string& msg_to_encrypt, unsigned char* result,
                     uint32_t result_len);

        ~SHA256();

    private:
        EVP_MD_CTX* digest_context = nullptr;
        bool initialised = 0;
    };
} // namespace CNCS::cryptography
