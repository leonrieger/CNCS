#pragma once

#include <string>

namespace CNCS::settings::interpreter {
    struct USER_ENVIRONMENT_SETTINGS {
        bool allow_lowercase_characters_in_comments;
        bool force_percent_symbol_as_file_begin_and_end;
        bool force_line_numbers_declared_with_N;
    };

    struct SYSTEM_ENVIRONMENT_SETTINGS {

    };

    bool load_settings(USER_ENVIRONMENT_SETTINGS& settings);
    bool load_settings(SYSTEM_ENVIRONMENT_SETTINGS& settings);

    bool save_settings(USER_ENVIRONMENT_SETTINGS& settings);
    bool save_settings(SYSTEM_ENVIRONMENT_SETTINGS& settings);

    std::string test();
}
