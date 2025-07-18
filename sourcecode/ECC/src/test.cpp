#include "reed_solomon.hpp"

#include <iostream>

int main() {
    char message[] = "Some very important message ought to be delivered";
    constexpr int msglen = sizeof(message);
    const int ecclen = 8;

    char repaired[msglen];
    char encoded[msglen + ecclen];

    CNCS::ecc::ReedSolomon rs(msglen, ecclen);

    rs.Encode(message, encoded);

    for (uint32_t i = 0; i < ecclen / 2 +1; ++i) {
        encoded[i] = 'E';
    }

    rs.Decode(encoded, repaired);

    std::cout << "Original:  " << message << std::endl;
    std::cout << "Corrupted: " << encoded << std::endl;
    std::cout << "Repaired:  " << repaired << std::endl;
}
