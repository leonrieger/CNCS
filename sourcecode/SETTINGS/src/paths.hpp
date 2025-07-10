#pragma once

// may be better to switch to std::filesystem::path in the future
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
// #        define TOOLKIT_USER_PATH std::string("toolkits\\user\\")
#    else
#        define GLOBAL_SETTINGS_PATH std::string("")
#        define USER_SETTINGS_PATH                                             \
            std::string("C:\\Users\\" + CNCS::settings::getCurrentUserName() + \
                        "\\AppData\\Local\\CNCS\\")
#        define TOOLKIT_PATH std::string("C:\\CNCS\\toolkits\\")
// #        define TOOLKIT_USER_PATH std::string("C:\\CNCS\\toolkits\\user\\")
#    endif
#elif defined(__linux__)

#endif
