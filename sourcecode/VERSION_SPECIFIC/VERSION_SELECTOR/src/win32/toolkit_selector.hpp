#pragma once

#include <string>
#include <unordered_map>
#include <version.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace CNCS::toolkit {
    class TOOLKIT {
    public:
        bool set(const CNCS::settings::VERSION& version);
        // bool set(std::string toolkit_name);

        std::string get() const;

    private:
        CNCS::settings::VERSION internal_toolkit_version =
            CNCS::settings::VERSION(0, 0, 0);
        // std::string user_toolkit; // user toolkits are currently not
        // supported --- will be added in the future
    };

    class TOOLKIT_INTERFACE {
    public:
        bool load(const TOOLKIT& toolkit);

        void get_functions(std::unordered_map<std::string, void*>& function_list) const;

        ~TOOLKIT_INTERFACE();

    private:
        static std::unordered_map<std::string, HMODULE> loaded_toolkits;
        std::string active_toolkit;
    };
} // namespace CNCS::toolkit
