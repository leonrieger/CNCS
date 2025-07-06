#pragma once

#include "../fields/fields.hpp"

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace CNCS::database {
    enum COMPARISON_TYPES {
        IS_EQUAL_TO = 1,
        IS_LARGER_AS = 2,
        IS_SMALLER_AS = 3,
        IS_EQUAL_TO_OR_LARGER = 4,
        IS_EQUAL_TO_OR_SMALLER = 5
    };

    class DATABASE_CONTENT {
    public:
        DATABASE_CONTENT(
            std::string table_name,
            std::vector<std::unique_ptr<fields::FIELD>>& list_of_all_fields,
            std::vector<std::map<std::string, DB_RETURN_TYPES>>
                database_return);

        // all filtering methods
        void filter(const std::string& fieldname,
                    const COMPARISON_TYPES& comp_type,
                    const DB_RETURN_TYPES value);

    private:
        std::vector<std::map<std::string, DB_RETURN_TYPES>> database_params;
        std::vector<std::unique_ptr<fields::FIELD>>& all_fields;
        std::string name = "";
    };
} // namespace CNCS::database
