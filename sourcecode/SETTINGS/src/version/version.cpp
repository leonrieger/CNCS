#include "version.hpp"

#include <sstream>

CNCS::settings::VERSION
CNCS::settings::generate_version(std::string input_version_str) {

    if (input_version_str.at(0) == 'v') {
        input_version_str.erase(0, 1);
    }

    int16_t v_major = 0;
    int8_t v_minor = 0, v_patch = 0;
    char ignored;

    std::stringstream v_string(input_version_str);

    v_string >> v_major >> ignored >> v_minor >> ignored >> v_patch;

    return VERSION(v_major, v_minor, v_patch);
}

CNCS::settings::VERSION
CNCS::settings::generate_version(uint32_t input_version_id) {
    uint16_t v_major = (input_version_id >> 16) & 0xFFFF;
    uint8_t v_minor = (input_version_id >> 8) & 0xFF;
    uint8_t v_patch = input_version_id & 0xFF;

    return VERSION(v_major, v_minor, v_patch);
}

uint32_t CNCS::settings::generate_version_int(VERSION& version) {
    uint32_t output = 0;
    output |= (static_cast<uint32_t>(version.major) << 16);
    // output |= (version.major << 16);
    output |= (static_cast<uint32_t>(version.minor) << 8);
    output |= (static_cast<uint32_t>(version.patch));

    return output;
}

std::string
CNCS::settings::generate_version_str(VERSION& version,
                                     bool output_with_v_prefix) {
    std::stringstream output;

    if (output_with_v_prefix) {
        output << "v";
    }

    output << version.major << "." << version.minor << "." << version.patch;

    return output.str();
}
