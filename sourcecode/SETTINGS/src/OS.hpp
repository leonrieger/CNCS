#pragma once
#include <string>

// clang-format off
#if defined(_WIN32)
#   define GLOBAL_SETTINGS_PATH std::string("")
#   define USER_SETTINGS_PATH std::string("C:\\Users\\" + CNCS::settings::os::getCurrentUserName() + "\\AppData\\Local\\CNCS\\")
#   include "OS/win32/username.hpp"
#elif defined(__linux__)

#endif
// clang-format on
