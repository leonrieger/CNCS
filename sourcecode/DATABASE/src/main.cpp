#include "database.hpp"

int main() {
    CNCS::database::DATABASE_FILE db_file;
    db_file.connect("test.db");

    CNCS::database::DATABASE_TABLE test_table(
        db_file, "Test", CNCS::database::fields::idField(),
        CNCS::database::fields::integerField("test1"),
        CNCS::database::fields::integerField("test2"),
        CNCS::database::fields::integerField("test3"),
        CNCS::database::fields::integerField("test4"));

    CNCS::database::DATABASE_TABLE test_table2(
        db_file, "Test", CNCS::database::fields::idField(),
        CNCS::database::fields::integerField("a"),
        CNCS::database::fields::integerField("b"),
        CNCS::database::fields::integerField("c"),
        CNCS::database::fields::integerField("d"));

    return 0;
}
