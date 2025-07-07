#pragma once

#include <version/version.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace CNCS::version_selector {
    class COMPATIBILITY {
    public:
        COMPATIBILITY(settings::version::VERSION& toolkit_version);

    private:
    };
} // namespace CNCS::version_selector
