#include <iostream>
using namespace std;

#include <DATABASE-CTRL.hpp>
using namespace sqlite_database;

int main(/*int argc, char* argv[] */) {
	database_file db_file("test.database");
	database test_db(db_file);
	cout << "sucess" << endl;
	char x[10];
	cin >> x;
}
