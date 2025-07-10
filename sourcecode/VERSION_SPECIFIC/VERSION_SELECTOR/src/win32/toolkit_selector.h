#pragma once

#include <string>
#include <unordered_map>
#include <version/version.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace CNCS::toolkit {
    class TOOLKIT {
    public:
        bool set(const CNCS::settings::version::VERSION& version);
        //bool set(std::string toolkit_name);

    private:
        CNCS::settings::version::VERSION internal_toolkit_version;
        // std::string user_toolkit; // user toolkits are currently not
        // supported --- will be added in the future
    };

    class TOOLKIT_INTERFACE {
    public:
        bool load(TOOLKIT& toolkit);

    private:
        static std::unordered_map<TOOLKIT, HMODULE>
            toolkits_loaded;
    };
} // namespace CNCS::toolkit
