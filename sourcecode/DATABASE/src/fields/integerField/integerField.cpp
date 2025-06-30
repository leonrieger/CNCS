#include "integerField.hpp"
#include <format>

CNCS::database::fields::integerField::integerField(std::string name) {
    properties = {
        {"name", name},
    };
}

std::string CNCS::database::fields::integerField::convert_to_sql() {
    return properties.at("name") + "INTEGER NOT NULL";
}
