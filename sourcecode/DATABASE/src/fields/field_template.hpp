#pragma once
#include <any>
#include <map>
#include <pugixml.hpp>
#include <string>

namespace CNCS::database::fields {
    class FIELD {
    public:
        virtual std::string convert_to_sql();
        template<typename T>
        T interpret_sql_response(std::string input_text);
        virtual void add_db_xml_information(pugi::xml_node& root_to_append_to);

    private:
        std::map<std::string, std::any> properties;
    };
} // namespace CNCS::database::fields
