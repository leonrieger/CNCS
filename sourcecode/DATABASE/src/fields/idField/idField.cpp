#include "idField.hpp"
#include <format>

CREATE_COPY_FUNCTION(CNCS::database::fields, idField)

std::string CNCS::database::fields::idField::convert_to_sql() const {
    return "id INTEGER PRIMARY KEY AUTOINCREMENT";
}

DB_RETURN_TYPES CNCS::database::fields::idField::interpret_sql_response(
    std::string input_text) {
    return 0;
}
