#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class idField : public FIELD {
    public:
        std::string convert_to_sql() const override;

        DB_RETURN_TYPES
        create_data(std::string input_text) override;

        bool is_name_compatible(std::string input_name) override;

        std::unique_ptr<FIELD> copy() const override;
    };
} // namespace CNCS::database::fields
