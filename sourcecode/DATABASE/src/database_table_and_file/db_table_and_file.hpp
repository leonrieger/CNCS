#pragma once

#include "../database_content/db_content.hpp"
#include "../fields/fields.hpp"
#include <format>
#include <sqlite3.h>
#include <string>
#include <type_traits>
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

    class DATABASE_TABLE {
    public:
        template <typename... Args>
        DATABASE_TABLE::DATABASE_TABLE(DATABASE_FILE& database,
                                       std::string table_name,
                                       const Args&... args) {
            static_assert((std::is_base_of<fields::FIELD, Args>::value && ...),
                          "DATABASE_TABLE init error: not all classes are "
                          "derived from FIELD!");

            db_file_pointer = database.db_file_pointer;
            is_db_connected = &database.connected;
            db_table_name = table_name;

            std::string initial_sql_message =
                std::format("CREATE TABLE IF NOT EXISTS {0} (", table_name);

            (list_of_fields.push_back(args.copy()), ...);

            for (const auto& field : list_of_fields) {
                initial_sql_message += field->convert_to_sql();
            }

            initial_sql_message += ");";
            sqlite3_exec(db_file_pointer, initial_sql_message.c_str(),
                         getter_callback, nullptr, &sql_errorMessage);
        }

        DATABASE_CONTENT all_elements();

    private:
        std::vector<std::map<std::string, DB_RETURN_TYPES>> db_content = {};

        sqlite3* db_file_pointer = nullptr;
        int8_t* is_db_connected = nullptr;
        std::vector<std::unique_ptr<fields::FIELD>> list_of_fields = {};
        std::string db_table_name = "";
        char* sql_errorMessage = nullptr;
        void getter_callback(void* NotUsed, int argc, char** argv,
                             char** columnName);
    };
} // namespace CNCS::database
