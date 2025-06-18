#pragma once

#include <fstream>

namespace CNCS::filesys {
    int32_t lines_loaded_while_interpreting = 100;
    int32_t getNumberOfLines(std::fstream& filehandle);
}
