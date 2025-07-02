#include "database.hpp"

int main() {
    CNCS::database::DATABASE_FILE db_file;
    db_file.connect("test.db");

    CNCS::database::DATABASE_TABLE test_table(
        db_file, "test0", CNCS::database::fields::idField(),
        CNCS::database::fields::integerField("test1"),
        CNCS::database::fields::integerField("test2"),
        CNCS::database::fields::integerField("test3"),
        CNCS::database::fields::integerField("allajaklak"));

    return 0;
}
