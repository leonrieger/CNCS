#include "integerField.hpp"
#include <format>

CNCS::database::fields::integerField::integerField(const std::string name)
    : field_name(name) {}

CREATE_COPY_FUNCTION(CNCS::database::fields, integerField)

std::string CNCS::database::fields::integerField::convert_to_sql() const {
    return std::format(", {} INTEGER NOT NULL", field_name);
}

DB_RETURN_TYPES CNCS::database::fields::integerField::create_data(
    std::string input_text) {
    return std::stoi(input_text);
}

bool CNCS::database::fields::integerField::is_name_compatible(
    std::string input_name) {
    return input_name == field_name;
}
