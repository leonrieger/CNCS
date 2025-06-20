#include "core_interpreter.hpp"
#include "core_interpreter_functions/core_interpreter_functions.hpp"

bool CNCS::interpreter::gcode_line_parser(
    current_interpreter_status& currentstate, std::string line_content,
    pugi::xml_node& root_gcode_node) {
    //------------------------------
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



    return 0;
}
