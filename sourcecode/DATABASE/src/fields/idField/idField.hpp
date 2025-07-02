#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class idField : public FIELD {
    public:
        std::string convert_to_sql() const override;

        DB_RETURN_TYPES
        interpret_sql_response(std::string input_text) override;

        std::unique_ptr<FIELD> copy() const override;
    };
} // namespace CNCS::database::fields
