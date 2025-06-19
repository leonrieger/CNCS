#pragma once
#include <string>

// clang-format off
#if defined(_WIN32)
#   define GLOBAL_SETTINGS_PATH std::string("")
#   define USER_SETTINGS_PATH(username) std::string("C:\\Users\\"+username+"\\AppData\\Local\\CNCS\\")
#elif defined(__linux__)

#endif
// clang-format on
