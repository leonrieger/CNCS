#pragma once
#include <memory>
#include <string>
#include <variant>

namespace CNCS::database::fields {
    using _DB_RETURN_ALLOWED_TYPES = std::variant<std::string, int64_t>;

    class FIELD {
    protected:
        virtual std::string convert_to_sql() const = 0;
        virtual _DB_RETURN_ALLOWED_TYPES
        interpret_sql_response(std::string input_text) = 0;
        //---
        virtual std::unique_ptr<FIELD> copy() const = 0;

    public:
        virtual ~FIELD() = default;
    };
} // namespace CNCS::database::fields
