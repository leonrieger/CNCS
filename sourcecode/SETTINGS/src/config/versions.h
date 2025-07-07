#pragma once

#include <array>
#include <stdint.h>

namespace CNCS::settings {
    struct VERSION {
        VERSION(const uint8_t version_major, const uint8_t version_minor,
                const uint8_t version_patch)
            : major(version_major), minor(version_minor),
              patch(version_patch) {};
        const uint8_t major;
        const uint8_t minor;
        const uint8_t patch;
    };

    const static VERSION CURRENT_VERSION = VERSION(0, 1, 0);

    const static std::array<VERSION, 1> SUPPORTED_VERSIONS = {
        VERSION(0, 1, 0),
    };
} // namespace CNCS::settings
