#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class integerField : public FIELD {
    public:
        integerField(std::string name);

        std::string convert_to_sql() const override;

        _DB_RETURN_ALLOWED_TYPES
        interpret_sql_response(std::string input_text) override;

        std::unique_ptr<FIELD> copy() const override;

    private:
        const std::string field_name;
    };
} // namespace CNCS::database::fields
