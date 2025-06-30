#pragma once
#include <any>
#include <map>
#include <string>

namespace CNCS::database::fields {
    class FIELD {
    public:
        virtual std::string convert_to_sql();
        template <typename T> T interpret_sql_response(std::string input_text);

    private:
        std::map<std::string, std::any> properties;
        virtual bool validate_response();
    };
} // namespace CNCS::database::fields
