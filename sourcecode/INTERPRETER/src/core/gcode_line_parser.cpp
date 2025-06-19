#include "core_interpreter.hpp"

bool CNCS::interpreter::gcode_line_parser(
    current_interpreter_status& currentstate, std::string line_content,
    pugi::xml_node& root_gcode_node) {
    //------------------------------
    if (line_content[0] == ';') {
        std::string msg = line_content.substr(1);
        pugi::xml_node current_command_node = root_gcode_node.append_child("EXEC");
        current_command_node.append_attribute("ID").set_value("");
    }
}
