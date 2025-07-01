#include "integerField.hpp"
#include <format>

CNCS::database::fields::integerField::integerField(const std::string name)
    : field_name(name) {}

std::unique_ptr<CNCS::database::fields::FIELD>
CNCS::database::fields::integerField::copy() const {
    return std::make_unique<integerField>(*this);
}

std::string CNCS::database::fields::integerField::convert_to_sql() const {
    return std::format("");
}
