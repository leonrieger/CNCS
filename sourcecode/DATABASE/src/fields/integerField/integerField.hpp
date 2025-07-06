#pragma once
#include "../field_template.hpp"

namespace CNCS::database::fields {
    class integerField : public FIELD {
    public:
        integerField(std::string name);

        std::string convert_to_sql() const override;

        bool is_name_compatible(std::string input_name) override;

        DB_RETURN_TYPES
        create_data(std::string input_text) override;

        std::unique_ptr<FIELD> copy() const override;

    private:
        const std::string field_name;
    };
} // namespace CNCS::database::fields
