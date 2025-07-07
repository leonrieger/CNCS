#pragma once

#include <version/version.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>

namespace CNCS::toolkit {
    class TOOLKIT_ACCESS {
    public:
        TOOLKIT_ACCESS(settings::version::VERSION& toolkit_version);

        void test(std::string& temp);

        ~TOOLKIT_ACCESS();

    private:
        void load_dll();

        settings::version::VERSION& m_version;
        HMODULE m_dllHandle = nullptr;
    };
} // namespace CNCS::toolkit
