#pragma once
#include "fields/fields.hpp"
#include <pugixml.hpp>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace CNCS::database {
    class DATABASE_FILE {
    public:
        bool create(const std::string parent_dir,
                    const std::string database_name);
        bool connect(const std::string db_name);
        ~DATABASE_FILE();

        friend class DATABASE_TABLE;

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t connected = false;
        pugi::xml_document database_info;
    };
    //---------------------------------
    class DATABASE_TABLE {
    public:
        template <typename... Args>
        DATABASE_TABLE(DATABASE_FILE& database, std::string name, Args... args);

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t* is_db_connected = nullptr;
        std::vector<fields::FIELD> table_properties = {};
        pugi::xml_document* database_information = nullptr;
    };
} // namespace CNCS::database
