#include <correct.h>

int main() {
    // Create encoder/decoder: 8-bit symbols, 255 symbol block, 32 parity
    // symbols (can correct up to 16 symbol errors)
    correct_reed_solomon* rs = correct_reed_solomon_create(8, 255, 32, 1);

    // Example input data (223 bytes, since 255-32=223 for message length)
    unsigned char input[223] = "Hello, Reed-Solomon! This is a test message "
                               "for error correction with libcorrect.";
    size_t inlen = 223;

    // Encode
    unsigned char encoded[255] = {0};
    correct_reed_solomon_encode(rs, input, inlen, encoded);

    // Simulate errors: flip some bytes in the encoded array
    encoded[10] ^= 0xFF;
    encoded[50] ^= 0xAA;
    encoded[100] ^= 0x01;

    // Decode
    unsigned char decoded[223] = {0};
    ssize_t decoded_len =
        correct_reed_solomon_decode(rs, encoded, 255, decoded);

    if (decoded_len > 0) {
        printf("Decoded (%zd bytes): %.*s\n", decoded_len, (int)decoded_len,
               decoded);
    } else {
        printf("Decoding failed!\n");
    }

    correct_reed_solomon_destroy(rs);
    return 0;
}
