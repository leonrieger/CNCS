#pragma once

#include "../fields/fields.hpp"

#include <map>
#include <string>
#include <vector>
#include <memory>

namespace CNCS::database {
    class DATABASE_CONTENT {
    public:
        DATABASE_CONTENT(
            std::string name,
            std::vector<std::unique_ptr<fields::FIELD>>& list_of_all_fields,
            std::map<std::string, DB_RETURN_TYPES> database_return);

    private:
        std::map<std::string, DB_RETURN_TYPES> database_params;
    };
} // namespace CNCS::database
