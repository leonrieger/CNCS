#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class integerField : FIELD {
    public:
        integerField(std::string name);
        std::string convert_to_sql();
        int64_t interpret_sql_response(std::string input_text);
        void add_db_xml_information(pugi::xml_node& root_to_append_to);
    private:
        std::map<std::string, std::any> properties;
    };
} // namespace CNCS::database::fields
