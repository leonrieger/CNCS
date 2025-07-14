#include <cstring>
#include <iostream>
#include <vector>
extern "C" {
#include <correct.h>
}

int main() {
    // Reed-Solomon parameters: 8-bit symbols, 255 total, 32 parity, primitive
    // polynomial 1
    correct_reed_solomon* rs = correct_reed_solomon_create(8, 255, 32, 1);

    // Message length = 255 - 32 = 223 bytes
    std::vector<unsigned char> input(223, 0);
    std::string message = "Hello, Reed-Solomon! This is a test message for "
                          "error correction with libcorrect.";
    std::memcpy(input.data(), message.c_str(),
                std::min(input.size(), message.size()));

    // Encode
    std::vector<unsigned char> encoded(255, 0);
    correct_reed_solomon_encode(rs, input.data(), input.size(), encoded.data());

    // Simulate some symbol errors
    encoded[10] ^= 0xFF;
    encoded[50] ^= 0xAA;
    encoded[100] ^= 0x01;

    // Decode
    std::vector<unsigned char> decoded(223, 0);
    ssize_t decoded_len = correct_reed_solomon_decode(
        rs, encoded.data(), encoded.size(), decoded.data());

    if (decoded_len > 0) {
        std::cout << "Decoded (" << decoded_len << " bytes): ";
        std::cout.write(reinterpret_cast<char*>(decoded.data()), decoded_len);
        std::cout << std::endl;
    } else {
        std::cout << "Decoding failed!" << std::endl;
    }

    correct_reed_solomon_destroy(rs);
    return 0;
}
