#pragma once

#include <string>
#include <unordered_map>
#include <version/version.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace CNCS::toolkit {
    class TOOLKIT_LOADER {
    public:
        bool load(const CNCS::settings::version::VERSION& version);

    private:
        static std::unordered_map<CNCS::settings::version::VERSION, HMODULE>
            dlls_loaded;
    };
} // namespace CNCS::toolkit
