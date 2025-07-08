#include "sha256.hpp"
#include "../base64/base64.hpp"

#include <format>
#include <iostream>
#include <openssl/evp.h>

CNCS::cryptography::SHA256::SHA256() {
    // if (is_already_initialised) {
    //     return;
    // }

    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    const char* msg = "Hello, world!";

    // 1. Create a digest context
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        // handle error
    }

    // 2. Get the SHA256 digest method
    md = EVP_sha256();

    // 3. Initialize the digest operation
    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        // handle error
    }

    // 4. Provide the message to be hashed
    if (1 != EVP_DigestUpdate(mdctx, msg, strlen(msg))) {
        // handle error
    }

    // 5. Finalize the digest
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        // handle error
    }

    // 6. Clean up
    EVP_MD_CTX_free(mdctx);

    // Print the hash in hex
    //for (unsigned int i = 0; i < hash_len; ++i) {
    //    std::cout << std::format("{}", hash[i]);
    //}
    std::cout << base64_encode(hash, hash_len) << std::endl;

    // is_already_initialised = true;
}
