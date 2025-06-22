#include "core_interpreter.hpp"
#include "core_interpreter_functions/core_interpreter_functions.hpp"
#include <interpreter/settings.hpp>

int8_t INTERPRETER_DLLMODE CNCS::interpreter::gcode_line_parser(
    INTERPRETER_STATUS& currentstate,
    CNCS::settings::interpreter::USER_ENVIRONMENT_SETTINGS user_env_settings,
    std::string line_content, pugi::xml_node& root_gcode_node) {
    //------------------------------

    if (line_content[0] == '%') {
        if (!currentstate.programstartsymbol_exists_already) {
            currentstate.programstartsymbol_exists_already = true;
        } else if (!currentstate.programstopsymbol_exists_already) {
            currentstate.programstopsymbol_exists_already = true;
        }
        return 1;
    }

    if (user_env_settings.force_percent_symbol_as_file_begin_and_end) {
        if (!currentstate.programstartsymbol_exists_already ||
            currentstate.programstopsymbol_exists_already) {
            return -1;
        }
    }

    pugi::xml_node current_command_node = root_gcode_node.append_child("EXEC");
    currentstate.prevCommandID++;
    current_command_node.append_attribute("ID").set_value(
        std::to_string(currentstate.prevCommandID));

    if (line_content[0] == ';') {
        std::string msg = line_content.substr(1);
        current_command_node.append_child("EXCLUDED").text().set(msg);
        return 1;
    }

    std::vector<std::string> comments, command_parts;

    CNCS::interpreter::internal_functions::extractComments(line_content,
                                                           comments);

    CNCS::interpreter::internal_functions::splitbyWhitespace(line_content,
                                                             command_parts);

    int16_t commandExists = 0;
    for (std::string com : command_parts) {
        if (CNCS::interpreter::internal_functions::isValidCommand(com)) {
            commandExists++;
        }
    }

    return 0;
}
