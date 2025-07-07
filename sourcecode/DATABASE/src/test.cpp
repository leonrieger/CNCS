#include <iostream>
#include <sqlite3.h>

// Callback function to handle the results of a SELECT query
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL")
                  << "\n";
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* errMsg = nullptr;

    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << "\n";
        return 1;
    } else {
        std::cout << "Opened database successfully.\n";
    }

    // SQL statement to create a table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS users ("
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "name TEXT NOT NULL, "
                                 "age INTEGER);";

    // Execute the SQL command
    rc = sqlite3_exec(db, createTableSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully.\n";
    }

    // Insert data
    const char* insertSQL =
        "INSERT INTO users (name, age) VALUES ('Alice', 30);"
        "INSERT INTO users (name, age) VALUES ('Bob', 25);";

    rc = sqlite3_exec(db, insertSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    } else {
        std::cout << "Records inserted successfully.\n";
    }

    // Select data
    const char* selectSQL = "SELECT * FROM users;";
    rc = sqlite3_exec(db, selectSQL, callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }

    // Close the database
    sqlite3_close(db);
    return 0;
}
