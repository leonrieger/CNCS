#pragma once

#include <stdint.h>

namespace CNCS::cryptography {
    enum AES_TYPE {
        AES128 = 1,
        AES192 = 2,
        AES256 = 3,
    };

    class AES {
    public:
        // uses CBC
        AES(const AES_TYPE& type) : aes_type(type) {};

        bool set_key();

        bool encrypt();

        bool decrypt();

        ~AES();

    private:
        const AES_TYPE aes_type;
        uint8_t key[32];
        // 64bit + aes_type * 64
    };
} // namespace CNCS::cryptography
