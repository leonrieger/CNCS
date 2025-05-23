#include <iostream>
#include <string>
using namespace std;

#include <DATABASE-CTRL/src/DATABASE-CTRL.hpp>
using namespace sqlite_database;

#include <tracy/public/tracy/Tracy.hpp>

int main() {
    
    cout << "sucess" << endl;
    




    char x[10];
    cin >> x;
    return 0;
}

/*
try {
    test_throw_error();
}
catch (databaseError& e) {
    // Catch and handle our custom exception
    cout << e.what() << endl;
}
*/

/*
    database_file db_file("test.database");
    database test_db(db_file);

    FieldTemplate test1(string("test1"), false, string(""));
    FieldTemplate test2(string("test2"), false, string(""));
    FieldTemplate test3(string("test3"), false, string(""));
    FieldTemplate test4(string("test4"), false, string(""));

    test_db.create("Test_name",
        test1,
        test2,
        test3,
        test4);
        */
