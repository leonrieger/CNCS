#include "integerField.hpp"
#include <format>

CNCS::database::fields::integerField::integerField(const std::string name)
    : field_name(name) {}

std::unique_ptr<CNCS::database::fields::FIELD>
CNCS::database::fields::integerField::copy() const {
    return std::make_unique<integerField>(*this);
}

std::string CNCS::database::fields::integerField::convert_to_sql() const {
    return std::format(",\n {} INTEGER NOT NULL", field_name);
}

using _DB_RETURN_ALLOWED_TYPES = std::variant<std::string, int64_t>;
_DB_RETURN_ALLOWED_TYPES
CNCS::database::fields::integerField::interpret_sql_response(
    std::string input_text) {
    // Ensure the return type matches the expected _DB_RETURN_ALLOWED_TYPES
    return 0;
}
