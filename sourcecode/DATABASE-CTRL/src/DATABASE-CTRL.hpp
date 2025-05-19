#pragma once

#ifdef DLLEXPORT
#define DLLMODE __declspec(dllexport)
#else
#define DLLMODE __declspec(dllimport)
#endif

#include <stdint.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <pugixml.hpp>

using namespace std;
using namespace pugi;

namespace sqlite_database {
	class DLLMODE database_file {
	public:
		//database_file();
		 database_file(string filename);
		//__declspec(dllexport) ~database_file();
		//void open(string filename);
		void close();
		//friend class database_template;
		friend class database;
	private:
		string db_file_name;
		string xml_file_name;
		xml_document xml_file_parsed;
		sqlite3* database_file_pointer;
	};
	//-----------------------------------------------------
	class __declspec(dllexport) database {// : public database_file {
	public:
		database(database_file& in_database_file);
		void open(char name[]);
		void insert();
		void get();
		void search();
	private:
		sqlite3* database_file_pointer;
	};
	//-----------------------------------------------------
	/*
	class __declspec(dllexport) database_template {
	public:
		database_template(database_file& current_database_file);
		void charField(char name[], uint32_t max_lenght);
		void integerField(char name[]);
		void floatingField(char name[]);
		void textField(char name[]);
		void booleanField(char name[], bool defaulting_to = false);
		void binaryField(char name[]);
		void emailField(char name[]);
		database save_with_open();
		void save(string database_name);
	private:
		void savexml();
		class fields {
		public:
			int type;
			string name;
			auto defaulting_to();
			uint32_t max_lenght;
		};
		vector<fields> sql_data_fields;
		string sql_data_fields_toSave;
		sqlite3* database_file_ptr;
	};
	*/
}
