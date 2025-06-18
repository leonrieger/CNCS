#include "config.hpp"

/*
namespace CNCS::interpreter::config {
    bool allow_lowercase_characters_in_comments = false;
    bool force_percent_symbol_on_file_begin = false;
    bool force_line_numbers_declared_with_N = false;
    int32_t lines_to_load_while_interpreting = 100;
} // namespace CNCS::interpreter::config
*/
bool CNCS::interpreter::settings::generate_config_from_file(std::string filename) {
    if (filename.empty()) {
        return false;
    }
    return true;
}
