#pragma once

// may be better to switch to std::filesystem::path
#include <string>

#ifndef _DEBUG
#    ifdef _WIN32
#        include "OS/win32/username.hpp"
#    elif defined(__linux__)
#        include "OS/linux/username.hpp"
#    endif
#endif

#if defined(_WIN32)
#    if defined(_DEBUG)
#        define USER_SETTINGS_PATH std::string("AppData\\Local\\")
#        define GLOBAL_SETTINGS_PATH std::string("AppData\\Global\\")
#        define TOOLKIT_PATH std::string("toolkits\\")
#    else
#        define GLOBAL_SETTINGS_PATH std::string("")
#        define USER_SETTINGS_PATH                                             \
            std::string("C:\\Users\\" +                                        \
                        CNCS::settings::os::getCurrentUserName() +             \
                        "\\AppData\\Local\\CNCS\\")
#        define TOOLKIT_PATH std::string("C:\\CNCS\\toolkits")
#    endif
#elif defined(__linux__)

#endif
