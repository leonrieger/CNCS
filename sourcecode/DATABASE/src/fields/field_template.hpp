#pragma once
#include <memory>
#include <string>
#include <variant>

#define DB_RETURN_TYPES std::variant<std::string, int64_t>

#define CREATE_COPY_FUNCTION(namespace_name, class_name)                       \
    std::unique_ptr<CNCS::database::fields::FIELD>                             \
    namespace_name::class_name::copy() const {                                 \
        return std::make_unique<class_name>(*this);                            \
    }

namespace CNCS::database::fields {
    class FIELD {
    public:
        virtual std::string convert_to_sql() const = 0;

        virtual DB_RETURN_TYPES create_data(std::string input_text) = 0;

        virtual bool is_name_compatible(std::string input_name) = 0;
        //---
        virtual std::unique_ptr<FIELD> copy() const = 0;

        virtual ~FIELD() = default;
    };
} // namespace CNCS::database::fields
