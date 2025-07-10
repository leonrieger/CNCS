#include "username.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

std::string CNCS::settings::getCurrentUserName() {
    char username_temp[256] = {};
    DWORD buffer_length = sizeof(username_temp);
    if (GetUserNameA(username_temp, &buffer_length)) {
        return std::string(username_temp);
    } else {
        return std::string("");
    }
}
