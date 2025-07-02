#pragma once
#include "fields/fields.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

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
    //---------------------------------
    class DATABASE_TABLE {
    public:
        template <typename... Args>
        DATABASE_TABLE(DATABASE_FILE& database, std::string table_name,
                       const Args&... args) {
            static_assert((std::is_base_of<fields::FIELD, Args>::value && ...),
                          "DATABASE_TABLE init error: not all classes are "
                          "derived from FIELD!");

            // handling the database stuff
            db_file_pointer = database.db_file_pointer;
            is_db_connected = &database.connected;
            db_table_name = table_name;
            //---------
            std::string initial_sql_message =
                "CREATE TABLE IF NOT EXISTS " + table_name +
                "(id INTEGER PRIMARY KEY AUTOINCREMENT";
            //----------
            (list_of_fields.push_back(args.copy()), ...);

            for (const auto& field : list_of_fields) {
                initial_sql_message += field->convert_to_sql();
            }

            initial_sql_message += ");";
            std::cout << initial_sql_message << std::endl;
            sqlite3_exec(db_file_pointer, initial_sql_message.c_str(), 0, 0, 0);
        }

    private:
        sqlite3* db_file_pointer = nullptr;
        int8_t* is_db_connected = nullptr;
        std::vector<std::unique_ptr<fields::FIELD>> list_of_fields = {};
        std::string db_table_name = "";
    };
} // namespace CNCS::database
