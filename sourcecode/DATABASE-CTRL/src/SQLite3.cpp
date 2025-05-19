#include "DATABASE-CTRL.hpp"
#include "Core.hpp"

#ifdef DEBUG_MODE
#	include <iostream>
#endif

using namespace std;
using namespace sqlite_database;
using namespace pugi;

database_file::database_file(string filename) {//void open
	xml_document configuration;
	configuration.load_file("config.xml");
	xml_node root = configuration.child("CONFIGURATION");
	xml_node paths = root.child("PATHS");
	string path_gotten_by_xml;
	for (xml_node path = paths.first_child(); path; ) {
		xml_node next_path = path.next_sibling();
		string usage = path.attribute("usage").value();
		if (usage == string("database_file_storage")) {
			path_gotten_by_xml = path.child_value();
			break;
		}
		path = next_path;
	}
	string fileposition = path_gotten_by_xml + filename;
	sqlite3_open(fileposition.c_str(), &(this->database_file_pointer));
}

void database_file::close() {
	sqlite3_close(database_file::database_file_pointer);
}

//**************************************************************************************
/*
void database_template::save(string database_name) {
	string sql_data_in_string_format = "CREATE TABLE "+database_name+"(";
	char* errorMessage;
	for (fields sql_data_field : sql_data_fields) {

	}

	sqlite3_exec(database_file_ptr, sql_data_in_string_format.c_str(), NULL, 0, &errorMessage);
}

database_template::database_template(database_file& current_database_file) {
	database_file_ptr = current_database_file.database_file_pointer;
}
*/
//***************************************************************************************

database::database(database_file& in_database_file) {
	//Copies the database reference
	this->database_file_pointer = in_database_file.database_file_pointer;
}

//***************************************************************************************
//int main(int argc, char* argv[]) <- benutzt für argumente beim aufrufen der cmd z.b programm.exe argument1 ardument2 ...
