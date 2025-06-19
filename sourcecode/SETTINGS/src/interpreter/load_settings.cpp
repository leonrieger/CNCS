#include "../OS.hpp" // for operating system specific properties
#include "settings.hpp"

// reqired for pugixml
#include <pugiconfig.hpp>
#include <pugixml.hpp>

bool CNCS::settings::interpreter::load_settings(
    USER_ENVIRONMENT_SETTINGS& settings) {
    // load file
    pugi::xml_document settings_file;
    settings_file.load_file(
        std::string(USER_SETTINGS_PATH + "settings.xml").c_str());
    // move to correct child
    pugi::xml_node interpreter_settings =
        settings_file.child("settings").child("interpreter");
    settings.allow_lowercase_characters_in_comments =
        interpreter_settings.child("allow_lowercase_characters_in_comments")
            .value() == "true";

    return 0;
}

// bool CNCS::settings::interpreter::load_settings(
//     SYSTEM_ENVIRONMENT_SETTINGS& settings) {}
