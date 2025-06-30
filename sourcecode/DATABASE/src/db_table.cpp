#include "database.hpp"

void CNCS::database::DATABASE_TABLE::operator=(DATABASE_FILE& db_file) {
    is_db_connected = &db_file.connected;
    db_file_pointer = db_file.db_file_pointer;
    database_information = &db_file.database_info;
}
