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
    // lowercase characters in comments
    settings.allow_lowercase_characters_in_comments =
        interpreter_settings.child("allow_lowercase_characters_in_comments")
            .value() == "true";

    return 0;
}

std::string CNCS::settings::interpreter::test() {
    // load file
    pugi::xml_document settings_file;
    settings_file.load_file(
        std::string(USER_SETTINGS_PATH + "settings.xml").c_str());
    // move to correct child
    pugi::xml_node interpreter_settings =
        settings_file.child("settings").child("interpreter");
    // lowercase characters in comments
    return std::string(interpreter_settings.child("allow_lowercase_characters_in_comments")
            .value() +
        std::string("\t\t") + USER_SETTINGS_PATH);
}

// bool CNCS::settings::interpreter::load_settings(
//     SYSTEM_ENVIRONMENT_SETTINGS& settings) {}
