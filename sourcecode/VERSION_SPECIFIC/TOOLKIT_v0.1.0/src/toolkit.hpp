#pragma once

#include "Core.hpp"
#include <iostream>
#include <string>

extern "C" {
void TOOLKIT_DLLMODE test(std::string& name) {
    std::cout << "Hello, test sucess: " + name;
}
}
