#pragma once

#include <array>
#include <stdint.h>
#include <string>

namespace CNCS::settings {
    struct VERSION {
        VERSION(const uint16_t version_major, const uint8_t version_minor,
                const uint8_t version_patch)
            : major(version_major), minor(version_minor),
              patch(version_patch) {};

        const uint8_t major;
        const uint8_t minor;
        const uint8_t patch;
    };

    VERSION generate_version(std::string input_version_str);
    VERSION generate_version(uint32_t input_version_id);
    uint32_t generate_version_int(VERSION& version);
    std::string generate_version_str(VERSION& version,
                                     bool output_with_v_prefix = false);

    const static VERSION CURRENT_VERSION = VERSION(0, 1, 0);

    const static std::array<VERSION, 1> SUPPORTED_VERSIONS = {
        VERSION(0, 1, 0),
    };
} // namespace CNCS::settings
