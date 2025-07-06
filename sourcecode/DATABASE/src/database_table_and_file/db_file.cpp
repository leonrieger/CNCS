#include "db_table_and_file.hpp"

#include <filesystem>

CNCS::database::DATABASE_FILE::~DATABASE_FILE() {
    sqlite3_close(db_file_pointer);
}

bool CNCS::database::DATABASE_FILE::connect(const std::string filename) {
    if (sqlite3_open(filename.c_str(), &db_file_pointer) == SQLITE_OK) {
        connected = 1;
        return 1;
    }
    connected = -1;
    return 0;
}

sqlite3* CNCS::database::DATABASE_FILE::get_raw_sqlite3_pointer() {
    return db_file_pointer;
}
