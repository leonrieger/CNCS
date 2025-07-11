#include "AES.hpp"

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

bool CNCS::cryptography::AES::set_key(const char* key, size_t key_len) {

}

bool CNCS::cryptography::AES::encrypt(std::string& msg_to_encrypt,
                                      uint8_t* encrypted_text,
                                      size_t& encypted_text_len) {}
