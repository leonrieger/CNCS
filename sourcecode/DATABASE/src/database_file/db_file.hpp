#pragma once

#include "../database_table/db_table.hpp"
#include <string>
#include <sqlite3.h>

namespace CNCS::database {
    class DATABASE_FILE {
    public:
        bool connect(const std::string database_name);
        ~DATABASE_FILE();

        friend class DATABASE_TABLE;

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t connected = 0;
    };
} // namespace CNCS::database
