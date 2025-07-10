#include "../version.hpp"

#include <array>
#include <format>
#include <sstream>

CNCS::settings::VERSION
CNCS::settings::generate_version(const std::string input_version_str) {
    std::string input_string = input_version_str;

    if (input_string.at(0) == 'v') {
        input_string.erase(0, 1);
    }

    std::stringstream input_stream(input_string);

    std::string tmp;
    std::array<std::string, 3> seglist;

    for (int8_t i = 0; i < 3; ++i) {
        std::getline(input_stream, tmp, '.');
        seglist[i] = tmp;
    }

    uint16_t v_major = std::stoi(seglist[0]);
    uint8_t v_minor = std::stoi(seglist[1]);
    uint8_t v_patch = std::stoi(seglist[2]);

    return VERSION(v_major, v_minor, v_patch);
}

CNCS::settings::VERSION
CNCS::settings::generate_version(const uint32_t input_version_id) {
    uint16_t v_major = (input_version_id >> 16) & 0xFFFF;
    uint8_t v_minor = (input_version_id >> 8) & 0xFF;
    uint8_t v_patch = input_version_id & 0xFF;

    return VERSION(v_major, v_minor, v_patch);
}

uint32_t CNCS::settings::generate_version_int(const VERSION& version) {
    uint32_t output = 0;
    output |= (static_cast<uint32_t>(version.major) << 16);
    // output |= (version.major << 16);
    output |= (static_cast<uint32_t>(version.minor) << 8);
    output |= (static_cast<uint32_t>(version.patch));

    return output;
}

std::string
CNCS::settings::generate_version_str(const VERSION& version,
                                              bool output_with_v_prefix) {

    if (output_with_v_prefix) {
        return std::format("v{0}.{1}.{2}", version.major, version.minor,
                           version.patch);
    } else {
        return std::format("{0}.{1}.{2}", version.major, version.minor,
                           version.patch);
    }
}
