#pragma once
#include <memory>
#include <string>
#include <variant>

#define DB_RETURN_ALLOWED_TYPES std::variant<std::string, int64_t>

#define CREATE_COPY(namespace_name, class_name)                                \
    std::unique_ptr<CNCS::database::fields::FIELD>                             \
    namespace_name::class_name::copy() const {                                 \
        return std::make_unique<class_name>(*this);                            \
    }

namespace CNCS::database::fields {
    using _DB_RETURN_ALLOWED_TYPES = DB_RETURN_ALLOWED_TYPES;

    class FIELD {
    public:
        virtual std::string convert_to_sql() const = 0;
        virtual _DB_RETURN_ALLOWED_TYPES
        interpret_sql_response(std::string input_text) = 0;
        //---
        virtual std::unique_ptr<FIELD> copy() const = 0;

        virtual ~FIELD() = default;
    };
} // namespace CNCS::database::fields
