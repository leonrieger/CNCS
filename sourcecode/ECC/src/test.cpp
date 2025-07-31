#include "reed_solomon.hpp"

#include <iostream>

int main() {
    char message[] = "Some very important message ought to be delivered";
    constexpr int msglen = sizeof(message);
    const int ecclen = 8;

    char repaired[msglen];
    char encoded[msglen + ecclen];

    CNCS::ecc::ReedSolomon rs(msglen, ecclen);

    std::cout << "Original:  " << std::string(message) << std::endl;

    rs.Encode(message, encoded);

    std::cout << "we got far" << std::endl;

    for (uint32_t i = 0; i < ecclen / 2 +1; ++i) {
        encoded[i] = 'E';
    }

    std::cout << "we got far x2" << std::endl;

    rs.Decode(encoded, repaired);

    std::cout << "we got far x3" << std::endl;
    
    std::cout << "Corrupted: " << std::string(encoded) << std::endl;
    std::cout << "Repaired:  " << std::string(repaired) << std::endl;
}
