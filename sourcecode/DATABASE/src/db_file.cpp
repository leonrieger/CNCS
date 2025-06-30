#include "database.hpp"

CNCS::database::DATABASE_FILE::~DATABASE_FILE() {
    sqlite3_close(db_file_pointer);
}

bool CNCS::database::DATABASE_FILE::connect(const std::string filename) {

    if (sqlite3_open(filename.c_str(), &db_file_pointer) == SQLITE_OK) {
        return 1;
    }
    return 0;
}
