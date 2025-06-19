#include "../OS.hpp" // for operating system specific properties
#include "settings.hpp"

// reqired for pugixml
#include <pugiconfig.hpp>
#include <pugixml.hpp>

bool CNCS::settings::interpreter::load_settings(
    USER_ENVIRONMENT_SETTINGS& settings) {

    pugi::xml_document settings_file;
    settings_file.load_file(std::string(USER_SETTINGS_PATH + "settings.xml").c_str());
    return 0;
}

// bool CNCS::settings::interpreter::load_settings(
//     SYSTEM_ENVIRONMENT_SETTINGS& settings) {}
