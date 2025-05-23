#include "DATABASE-CTRL.hpp"
#include "Core.hpp"

#ifdef DEBUG_MODE
#	include <iostream>
#endif

using namespace std;
//needed for selecting the database
using namespace sqlite_database;
//needed for pugixml
using namespace pugi;

database_file::database_file(string filename) {
    //get the path where the db is stored
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

database_file::~database_file() {
    sqlite3_close(database_file_pointer);
    delete(this);
}

void database_file::close() {
    sqlite3_close(this->database_file_pointer);
}

//**************************************************************************************

database::database(database_file& in_database_file) {
    //Copies the database reference
    this->database_file_pointer = in_database_file.database_file_pointer;
}

template<typename ... ARGS>
void database::create(string name, ARGS ... args) {
    //add all db-arguments
    //string arguments = ("" + ... + args);
    //string argChain = "CREATE TABLE " + name + "(ID INT PRIMARY KEY NOT NULL, " + arguments + ");";
    int status = 0;
    //int status = sqlite3_exec();
    if (status != SQLITE_OK) {
        throw databaseError(1021, "Database creation failed due to an SQLite3 error");
    }
    int i = 0;
    for (FieldTemplate type : args) {
        cout << type.get_string << endl;
        cout << "Iteration: " << i << endl;
    }
}

//**************************************************************************************

string FieldTemplate::get_string() {
    return text_for_sql;
}

FieldTemplate::FieldTemplate(string name, bool null_allow, string defaulting) {
    text_for_sql = "Name: " + name;
    null_acceptable = null_allow;
    defaulting_to_value = defaulting;
    name_of_object = name;
}
