#include "../OS.hpp" // for operating system specific properties
#include "settings.hpp"

// reqired for pugixml
#include <pugiconfig.hpp>
#include <pugixml.hpp>

// definition for ease of creating properties
#define SETTINGS_CONDITION_BOOLEAN(condition_name)                             \
    std::string(interpreter_settings.child(condition_name)                     \
                    .attribute("value")                                        \
                    .value()) == "true"

bool SETTINGS_DLLMODE CNCS::settings::interpreter::load_settings(
    USER_ENVIRONMENT_SETTINGS& settings) noexcept {
    // load file
    pugi::xml_document settings_file;
    settings_file.load_file(
        std::string(USER_SETTINGS_PATH + "settings.xml").c_str());
    // move to correct child
    pugi::xml_node interpreter_settings =
        settings_file.child("settings").child("interpreter");

    settings.allow_lowercase_characters_in_comments =
        SETTINGS_CONDITION_BOOLEAN("allow_lowercase_characters_in_comments");
    settings.force_line_numbers_declared_with_N =
        SETTINGS_CONDITION_BOOLEAN("force_line_numbers_declared_with_N");
    settings.force_percent_symbol_as_file_begin_and_end =
        SETTINGS_CONDITION_BOOLEAN(
            "force_percent_symbol_as_file_begin_and_end");

    return true;
}

// bool CNCS::settings::interpreter::load_settings(
//     SYSTEM_ENVIRONMENT_SETTINGS& settings) {}
