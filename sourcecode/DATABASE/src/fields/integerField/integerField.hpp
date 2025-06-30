#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class integerField : FIELD {
    public:
        integerField(std::string name);
        std::string convert_to_sql();
        int64_t interpret_sql_response(std::string input_text);
    private:
        std::map<std::string, std::string> properties;
    };
} // namespace CNCS::database::fields
