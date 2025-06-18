#include "file_handler.hpp"

#include <string>

int32_t CNCS::filesys::getNumberOfLines(std::fstream& filehandle) {
    int32_t number_of_lines = 0;
    std::string last_line;

    while (std::getline(filehandle, last_line)) {
        number_of_lines++;
    }

    if (number_of_lines <= 0) {
        return -1;
    } else {
        return number_of_lines;
    }
}
