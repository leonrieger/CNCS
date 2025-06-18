#pragma once

#include <string>

namespace CNCS::interpreter::config {
    bool allow_lowercase_characters_in_comments = false;
    bool force_percent_symbol_on_file_begin = false;
    bool force_line_numbers_declared_with_N = false;

    bool generate_config_from_file(std::string filename);
}
