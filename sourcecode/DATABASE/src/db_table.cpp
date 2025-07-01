#include "database.hpp"
#include <iostream>

template <typename... Args>
CNCS::database::DATABASE_TABLE::DATABASE_TABLE(DATABASE_FILE& database,
                                               std::string table_name,
                                               const Args&... args) {

    static_assert(
        (std::is_base_of<fields::FIELD, args>::value && ...),
        "DATABASE_TABLE init error: not all classes are derived from FIELD!");

    // handling the database stuff
    db_file_pointer = database.db_file_pointer;
    is_db_connected = &database.connected;
    db_table_name = table_name;
    //---------
    std::string initial_sql_message = "CREATE TABLE IF NOT EXISTS " +
                                      table_name +
                                      "(id INTEGER PRIMARY KEY AUTOINCREMENT";
    //----------
    (list_of_fields.push_back(args.copy()), ...);

    for (const auto& field : list_of_fields) {
        initial_sql_message += field->convert_to_sql();
    }

    initial_sql_message += ");";
    std::cout << initial_sql_message << std::endl;
}
