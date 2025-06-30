#include "database.hpp"

#include <filesystem>

CNCS::database::DATABASE_FILE::~DATABASE_FILE() {
    sqlite3_close(db_file_pointer);
}

bool CNCS::database::DATABASE_FILE::create(const std::string parent_dir,
    const std::string database_name) {

    std::filesystem::path db_file_path = parent_dir + database_name;

    if (std::filesystem::exists(db_file_path)) {
        
    }

    return 0;
}

bool CNCS::database::DATABASE_FILE::connect(const std::string filename) {

    if (sqlite3_open(filename.c_str(), &db_file_pointer) == SQLITE_OK) {
        return 1;
    }
    return 0;
}
