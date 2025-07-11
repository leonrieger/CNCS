#include <cstring>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>

void handleErrors() {
    //ERR_print_errors_fp(stderr);
    abort();
}

int aes_encrypt(const unsigned char* plaintext, int plaintext_len,
                const unsigned char* key, const unsigned char* iv,
                unsigned char* ciphertext) {
    EVP_CIPHER_CTX* ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int aes_decrypt(const unsigned char* ciphertext, int ciphertext_len,
                const unsigned char* key, const unsigned char* iv,
                unsigned char* plaintext) {
    EVP_CIPHER_CTX* ctx;
    int len;
    int plaintext_len;

    if (!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
        handleErrors();

    if (1 !=
        EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int main() {
    // Key and IV should be random and secret in real applications
    unsigned char key[32]; // AES-256 key size
    unsigned char iv[16];  // AES block size

    RAND_bytes(key, sizeof(key));
    RAND_bytes(iv, sizeof(iv));

    const char* plaintext = "Hello, AES with OpenSSL 3.5!";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int ciphertext_len = aes_encrypt((unsigned char*)plaintext,
                                     strlen(plaintext), key, iv, ciphertext);

    int decryptedtext_len =
        aes_decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    decryptedtext[decryptedtext_len] = '\0';

    std::cout << "Decrypted text: " << decryptedtext << std::endl;
    return 0;
}
