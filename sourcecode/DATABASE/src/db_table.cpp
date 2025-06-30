#include "database.hpp"
#include <iostream>

template <typename... Args>
CNCS::database::DATABASE_TABLE::DATABASE_TABLE(DATABASE_FILE& database,
                                               std::string table_name,
                                               Args&... args) {
    // handling the database stuff
    db_file_pointer = database.db_file_pointer;
    is_db_connected = &database.connected;
    db_table_name = table_name;
    //---------
    std::string initial_sql_message = "CREATE TABLE IF NOT EXISTS " +
                                      table_name +
                                      "(id INTEGER PRIMARY KEY AUTOINCREMENT";
    //----------
    // needs optimisation!
    std::vector<fields::FIELD> field_objects = {std::forward<Args>(args)...};
    for (const fields::FIELD& field_object : field_objects) {
        table_properties.push_back(field_object);
        initial_sql_message += ",\n" + field_object.convert_to_sql();
    }
    initial_sql_message += ");";
    std::cout << initial_sql_message << std::endl;
}
