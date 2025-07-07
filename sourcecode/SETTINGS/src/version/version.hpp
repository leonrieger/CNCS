#pragma once

#include "../Core.hpp"
#include <array>
#include <stdint.h>
#include <string>

namespace CNCS::settings {
    struct SETTINGS_DLLMODE VERSION {
        VERSION(const uint16_t version_major, const uint8_t version_minor,
                const uint8_t version_patch)
            : major(version_major), minor(version_minor),
              patch(version_patch) {};

        const uint16_t major;
        const uint8_t minor;
        const uint8_t patch;
    };

    VERSION SETTINGS_DLLMODE generate_version(const std::string input_version_str);
    VERSION SETTINGS_DLLMODE generate_version(const uint32_t input_version_id);
    uint32_t SETTINGS_DLLMODE generate_version_int(const VERSION& version);
    std::string SETTINGS_DLLMODE
    generate_version_str(const VERSION& version, bool output_with_v_prefix = false);

    const static VERSION CURRENT_VERSION = VERSION(0, 1, 0);

    const static std::array<VERSION, 1> SUPPORTED_VERSIONS = {
        VERSION(0, 1, 0),
    };
} // namespace CNCS::settings
