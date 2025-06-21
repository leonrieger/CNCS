#pragma once

#include "../Core.hpp"
#include <string>

namespace CNCS::settings::interpreter {
    struct DLLMODE USER_ENVIRONMENT_SETTINGS {
        bool allow_lowercase_characters_in_comments;
        bool force_percent_symbol_as_file_begin_and_end;
        bool force_line_numbers_declared_with_N;
    };

    struct DLLMODE SYSTEM_ENVIRONMENT_SETTINGS {

    };

    bool DLLMODE load_settings(USER_ENVIRONMENT_SETTINGS& settings) noexcept;
    //bool load_settings(SYSTEM_ENVIRONMENT_SETTINGS& settings);

    //bool save_settings(USER_ENVIRONMENT_SETTINGS& settings);
    //bool save_settings(SYSTEM_ENVIRONMENT_SETTINGS& settings);
}
