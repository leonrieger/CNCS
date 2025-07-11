#include "AES.hpp"

CNCS::cryptography::AES::AES(const AES_TYPE& type) : aes_type(type) {
    context = EVP_CIPHER_CTX_new();
}

bool CNCS::cryptography::AES::encrypt(std::string& msg_to_encrypt, uint8_t* encrypted_text,
    size_t& encypted_text_len) {

}
