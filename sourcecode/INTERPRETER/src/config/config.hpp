#pragma once

#include <string>

namespace CNCS::interpreter {
    union config {
        bool allow_lowercase_characters_in_comments;
        bool force_percent_symbol_on_file_begin;
        bool force_line_numbers_declared_with_N;
        int32_t lines_to_load_while_interpreting;
    };
    namespace settings {
        bool generate_config_from_file(std::string filename);
    }
} // namespace CNCS::interpreter
