#include "database.hpp"

template <typename... Args>
CNCS::database::DATABASE_TABLE::DATABASE_TABLE(DATABASE_FILE& database,
    std::string table_name,
    Args... args) {
    // handling the database stuff
    db_file_pointer = database.db_file_pointer;
    is_db_connected = &database.connected;
}
