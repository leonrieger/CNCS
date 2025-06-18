#pragma once

#include <fstream>

namespace CNCS::filesys {
    int32_t getNumberOfLines(std::fstream& filehandle);
}
