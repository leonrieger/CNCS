#include "database.hpp"
#include <iostream>
#include <version/version.hpp>

int main() {
    /*
    CNCS::database::DATABASE_FILE db_file;
    db_file.connect("test.db");

    CNCS::database::DATABASE_TABLE test_table(
        db_file, "Test", CNCS::database::fields::idField(),
        CNCS::database::fields::integerField("test1"),
        CNCS::database::fields::integerField("test2"),
        CNCS::database::fields::integerField("test3"),
        CNCS::database::fields::integerField("test4"));

    CNCS::database::DATABASE_TABLE test_table2(
        db_file, "Test12", CNCS::database::fields::idField(),
        CNCS::database::fields::integerField("a"),
        CNCS::database::fields::integerField("b"),
        CNCS::database::fields::integerField("c"),
        CNCS::database::fields::integerField("d"),
        CNCS::database::fields::integerField("e"));

    test_table.tmp();
    */

    auto test = CNCS::settings::generate_version("v1.2.3");
    auto test2 = CNCS::settings::generate_version("40.50.60");

    std::cout << CNCS::settings::generate_version_str(test, true) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test, false) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test2, true) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test2, false)
              << std::endl;
    std::cout << CNCS::settings::generate_version_str(test) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test2) << std::endl;

    uint32_t temp = CNCS::settings::generate_version_int(test);
    uint32_t temp2 = CNCS::settings::generate_version_int(test2);

    std::cout << temp << " | " << temp2 << std::endl;

    auto test3 = CNCS::settings::generate_version(temp);
    auto test4 = CNCS::settings::generate_version(temp2);

    std::cout << CNCS::settings::generate_version_str(test3, true) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test3, false)
              << std::endl;
    std::cout << CNCS::settings::generate_version_str(test4, true) << std::endl;
    std::cout << CNCS::settings::generate_version_str(test4, false)
              << std::endl;

    return 0;
}
