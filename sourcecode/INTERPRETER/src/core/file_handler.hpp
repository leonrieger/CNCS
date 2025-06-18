#pragma once

#include <fstream>

namespace CNCS::filesys {
    int32_t lines_to_load_while_interpreting = 100;
    int32_t getNumberOfLines(std::fstream& filehandle);
}
