#pragma once

#include "Core.hpp"
#include <array>
#include <stdint.h>
#include <string>

namespace CNCS::settings {
    struct VERSION {
        VERSION(const uint16_t version_major, const uint8_t version_minor,
                const uint8_t version_patch)
            : major(version_major), minor(version_minor),
              patch(version_patch) {};

        // sometimes I hate it...

        void operator=(const VERSION& other_version) {
            major = other_version.major;
            minor = other_version.minor;
            patch = other_version.patch;
        };

        bool operator==(const VERSION& other_version) {
            return major == other_version.major &&
                   minor == other_version.minor && patch == other_version.patch;
        }

        bool operator==(const VERSION other_version) const {
            return major == other_version.major &&
                   minor == other_version.minor && patch == other_version.patch;
        }

        //bool operator==(const uint32_t comp_value) {
        //    return generate_version_int(*this) == comp_value;
        //}

        //bool operator!=(const uint32_t comp_value) const {
        //    return generate_version_int(*this) != comp_value;
        //}

        uint16_t major;
        uint8_t minor;
        uint8_t patch;
    };

    VERSION SETTINGS_DLLMODE
    generate_version(const std::string input_version_str);

    VERSION SETTINGS_DLLMODE generate_version(const uint32_t input_version_id);

    uint32_t SETTINGS_DLLMODE generate_version_int(const VERSION& version);

    std::string SETTINGS_DLLMODE generate_version_str(
        const VERSION& version, bool output_with_v_prefix = false);

    bool SETTINGS_DLLMODE is_version_allowed(const VERSION& version_to_test);

    const static VERSION CURRENT_VERSION = VERSION(0, 1, 0);

    // maybe as import from xml file?
    const static std::array<VERSION, 1> SUPPORTED_VERSIONS = {
        VERSION(0, 1, 0),
    };
} // namespace CNCS::settings
