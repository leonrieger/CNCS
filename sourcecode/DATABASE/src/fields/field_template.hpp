#pragma once
#include <any>
#include <map>
#include <string>

namespace CNCS::database::fields {
    class FIELD {
    public:
        virtual std::string convert_to_sql() { return ""; };
        virtual std::any interpret_sql_response(std::string input_text) {
            return "";
        };

    private:
        std::map<std::string, std::string> properties;
        virtual bool validate_response() { return true; };
    };
} // namespace CNCS::database::fields
