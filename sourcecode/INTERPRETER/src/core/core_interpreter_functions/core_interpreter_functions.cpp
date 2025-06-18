#include "core_interpreter_functions.hpp"

void CNCS::interpreter::internal_functions::extractComments(
    std::string& command, std::vector<std::string>& comments) {
    size_t startposition, stopposition;

    while ((startposition = command.find('(')) != std::string::npos &&
           (stopposition = command.find(')', startposition)) !=
               std::string::npos) {
        std::string extracted_comment =
            command.substr(startposition + 1, stopposition - startposition - 1);
        comments.push_back(extracted_comment);
        command.erase(startposition, stopposition - startposition + 1);
    }
}
