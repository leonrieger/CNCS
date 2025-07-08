#include "sha256.hpp"
#include "../base64/base64.hpp"

#include <format>
#include <iostream>
#include <openssl/evp.h>

CNCS::cryptography::SHA256::SHA256() {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    const char* msg = "Hello, world!";

    // 1. Create a digest context
    mdctx = EVP_MD_CTX_new();
    if (mdctx == nullptr) {
        // handle error
    }

    // 3. Initialize the digest operation
    if (!EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        // handle error
    }

    // 4. Provide the message to be hashed
    if (!EVP_DigestUpdate(mdctx, msg, strlen(msg))) {
        // handle error
    }

    // 5. Finalize the digest
    if (!EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        // handle error
    }

    // 6. Clean up
    EVP_MD_CTX_free(mdctx);

    std::cout << base64_encode(hash, hash_len) << std::endl;
    std::cout << to_hex(hash, hash_len) << std::endl;

    // is_already_initialised = true;
}
