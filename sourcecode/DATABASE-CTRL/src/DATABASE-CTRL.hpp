#pragma once
//DO NOT USE, HAS ERRORS
#include "errors/errors.hpp"
#include "Core.hpp"

#include <stdint.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <pugixml/src/pugixml.hpp>

using namespace std;
using namespace pugi;

namespace sqlite_database {

    class DLLMODE database_file {
    public:
        database_file(string filename);
        ~database_file();
        //void open(string filename);
        void close();

        //needed to get the database_file_pointer for the database class
        friend class database;
    private:
        string db_file_name;
        string xml_file_name;
        xml_document xml_file_parsed;
        sqlite3* database_file_pointer;
    };



    //-----------------------------------------------------
    class DLLMODE database {
    public:
        database(database_file& in_database_file);
        //bool open(char name[]);
        
        template<typename ... ARGS>
        void create(string name, ARGS ... args);
        //void insert();
        //void get();
        //void search();
    private:
        sqlite3* database_file_pointer;
    };

    //-----------------------------------------------------

    struct database_configuration_options {
        //a textfield but with limited characters
        string DLLMODE charField(char name[], uint16_t max_lenght, bool null_allowed = false);
        //a field to store integers
        string DLLMODE integerField(char name[], bool null_allowed = false);
        //a string to store floating point values
        string DLLMODE floatingField(char name[], bool null_allowed = false);
        //a field that can store text
        string DLLMODE textField(char name[], bool null_allowed = false);
        //a field to store boolean values
        string DLLMODE booleanField(char name[], bool defaulting_to = false, bool null_allowed = false);
        //a field to store a binary array
        string DLLMODE binaryField(char name[], bool null_allowed = false);
        //a field to store email-addresses
        string DLLMODE emailField(char name[], bool null_allowed = false);
        //a field to store telephone numbers (with autocorrection)
        string DLLMODE telephoneField(char name[], bool null_allowed = false);
    } models;

    class DLLMODE FieldTemplate {
    public:
        FieldTemplate(string name, bool null_allow, string defaulting);
        string get_string();
        uint8_t get_type();
        bool NullAllowed();
        auto defaultingTo();
    private:
        string name_of_object;
        string text_for_sql;
        bool null_acceptable = false;
        string defaulting_to_value;
    };
}
