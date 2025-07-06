#include "idField.hpp"
#include <format>

CREATE_COPY_FUNCTION(CNCS::database::fields, idField)

std::string CNCS::database::fields::idField::convert_to_sql() const {
    return "id INTEGER PRIMARY KEY AUTOINCREMENT";
}

DB_RETURN_TYPES
CNCS::database::fields::idField::create_data(std::string input_text) {
    return std::stoi(input_text);
}

bool CNCS::database::fields::idField::is_name_compatible(
    std::string input_name) {
    return input_name == "id";
}
