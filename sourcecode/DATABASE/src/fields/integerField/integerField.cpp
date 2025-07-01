#include "integerField.hpp"
#include <format>

CNCS::database::fields::integerField::integerField(const std::string name)
    : field_name(name) {}
/*
std::unique_ptr<CNCS::database::fields::FIELD>
CNCS::database::fields::integerField::copy() const {
    return std::make_unique<integerField>(*this);
}
*/
CREATE_COPY(CNCS::database::fields, integerField)

std::string CNCS::database::fields::integerField::convert_to_sql() const {
    return std::format(", {} INTEGER NOT NULL", field_name);
}

using db_return = DB_RETURN_ALLOWED_TYPES;
db_return
CNCS::database::fields::integerField::interpret_sql_response(
    std::string input_text) {
    return 0;
}
