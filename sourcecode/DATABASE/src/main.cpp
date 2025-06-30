#include "database.hpp"

int main() {
    CNCS::database::DATABASE_FILE db_file;
    db_file.connect("test.db");

    CNCS::database::DATABASE_TABLE test_table(db_file, "test0");

    return 0;
}
