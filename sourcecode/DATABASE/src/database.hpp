#pragma once
#include "fields/fields.hpp"
#include <pugixml.hpp>
#include <sqlite3.h>
#include <string>

// the database currently uses SQLite 3
namespace CNCS::database {
    class DATABASE_FILE {
    public:
        bool create(const std::string parent_dir,
                    const std::string database_name);
        bool connect(const std::string db_name);
        ~DATABASE_FILE();

        void _test();

        friend class DATABASE_TABLE;

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t connected = false;
        pugi::xml_document database_info;
    };
    //---------------------------------
    class DATABASE_TABLE {
    public:
        void operator=(DATABASE_FILE& db_file);

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t* is_db_connected = nullptr;
        pugi::xml_document* database_information = nullptr;
    };
} // namespace CNCS::database
