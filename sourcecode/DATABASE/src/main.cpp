#include "database.hpp"

int main() {
    CNCS::database::DATABASE_FILE db_file;
    db_file.connect("test.db");


    return 0;
}
