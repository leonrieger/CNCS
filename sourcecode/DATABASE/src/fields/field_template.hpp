#pragma once
#include <any>
#include <map>
#include <string>
#include <variant>

namespace CNCS::database::fields {
    using DB_RETURN_ALLOWED_TYPES = std::variant<std::string>;

    class FIELD {
    public:
        virtual std::string convert_to_sql();
        virtual DB_RETURN_ALLOWED_TYPES interpret_sql_response(std::string input_text) {
            return "";
        };
        virtual ~FIELD() = default;
    };
} // namespace CNCS::database::fields
