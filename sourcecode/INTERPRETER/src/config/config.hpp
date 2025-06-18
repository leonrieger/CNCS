#pragma once

#include <string>

namespace CNCS::interpreter::config {
    bool allow_lowercase_characters_in_comments = false;
    bool force_percent_symbol_on_file_begin = false;
    bool force_line_numbers_declared_with_N = false;
    int32_t lines_to_load_while_interpreting = 100;

    bool generate_config_from_file(std::string filename);
}
