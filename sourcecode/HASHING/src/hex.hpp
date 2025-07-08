#pragma once

#include <iomanip>
#include <sstream>

namespace CNCS::cryptography {
    inline std::string to_hex(const unsigned char* data, size_t len) {
        std::ostringstream oss;
        for (size_t i = 0; i < len; ++i)
            oss << std::hex << std::setw(2) << std::setfill('0')
                << (int)data[i];
        return oss.str();
    }
} // namespace CNCS::cryptography
