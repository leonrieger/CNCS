#include "AES.hpp"

#include <algorithm>
#include <cmath>

CNCS::cryptography::AES::AES(const AES_TYPE& type) : aes_type(type) {
    context = EVP_CIPHER_CTX_new();

    switch (type) {
    case AES128:
        encryption_type = EVP_aes_128_cbc();
        break;
    case AES192:
        encryption_type = EVP_aes_192_cbc();
        break;
    case AES256:
        encryption_type = EVP_aes_256_cbc();
        break;
    }
}

bool CNCS::cryptography::AES::set_key(std::array<uint8_t, 32>& key_arr) {
    if (aes_type != AES256) {
        return false;
    }

    is_key_set = true;

    key_array = key_arr;

    return true;
}

bool CNCS::cryptography::AES::set_key(std::array<uint8_t, 24>& key_arr) {
    if (aes_type != AES192) {
        return false;
    }

    is_key_set = true;

    std::copy(key_arr.begin(), key_arr.end(), key_array.begin());

    return true;
}

bool CNCS::cryptography::AES::set_key(std::array<uint8_t, 16>& key_arr) {
    if (aes_type != AES128) {
        return false;
    }

    is_key_set = true;

    std::copy(key_arr.begin(), key_arr.end(), key_array.begin());

    return true;
}

bool CNCS::cryptography::AES::set_iv(std::array<uint8_t, 16>& iv_array) {
    is_iv_set = true;

    initialisation_vector = iv_array;

    return true;
}

bool CNCS::cryptography::AES::encrypt(std::string& msg_to_encrypt,
                                      std::vector<uint8_t>& encrypted_msg) {
    // why do I need math?
    encrypted_msg.reserve(
        (static_cast<size_t>(std::floor(msg_to_encrypt.length() / 16)) + 1) *
        16);
}
