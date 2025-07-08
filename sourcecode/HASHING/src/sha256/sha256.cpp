#include "sha256.hpp"

CNCS::cryptography::SHA256::SHA256() {
    digest_context = EVP_MD_CTX_new();
    if (digest_context != nullptr) {
        initialised = true;
    }
}

bool CNCS::cryptography::SHA256::encrypt(std::string& msg_to_encrypt,
                                         unsigned char* result,
                                         uint32_t result_len) {
    if (!initialised) {
        return false;
    }

    if (!EVP_DigestInit_ex(digest_context, EVP_sha256(), NULL)) {
        return false;
    }

    if (!EVP_DigestUpdate(digest_context, msg_to_encrypt.c_str(),
                          msg_to_encrypt.size())) {
        return false;
    }

    if (!EVP_DigestFinal_ex(digest_context, result, &result_len)) {
        return false;
    }

    return true;
}

CNCS::cryptography::SHA256::~SHA256() {
    if (digest_context != nullptr) {
        EVP_MD_CTX_free(digest_context);
        digest_context = nullptr;
    }
}
