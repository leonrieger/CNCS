#include <cctype>
#include <iostream>
#include <map>
#include <memory>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

class DB {
public:
    static sqlite3* connect(const std::string& db_name) {
        sqlite3* db;
        if (sqlite3_open(db_name.c_str(), &db)) {
            std::cerr << "Can't open DB: " << sqlite3_errmsg(db) << std::endl;
            return nullptr;
        }
        return db;
    }

    static void execute(sqlite3* db, const std::string& sql) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) !=
            SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
    }
};

class Field {
public:
    virtual std::string type() const = 0;
    virtual std::string serialize(const void* value) const = 0;
};

class CharField : public Field {
public:
    std::string type() const override { return "TEXT"; }

    std::string serialize(const void* value) const override {
        return "'" + std::string(*static_cast<const std::string*>(value)) + "'";
    }
};

class IntegerField : public Field {
public:
    std::string type() const override { return "INTEGER"; }

    std::string serialize(const void* value) const override {
        return std::to_string(*static_cast<const int*>(value));
    }
};

class Model {
public:
    static sqlite3* db;

    virtual std::string table_name() const = 0;
    virtual std::map<std::string, Field*> get_fields() const = 0;

    void save() {
        auto fields = get_fields();
        std::stringstream ss;

        // Insert into statement
        ss << "INSERT INTO " << table_name() << " (";
        bool first = true;
        for (const auto& [key, _] : fields) {
            if (!first)
                ss << ", ";
            ss << key;
            first = false;
        }

        ss << ") VALUES (";
        first = true;
        for (const auto& [key, field] : fields) {
            if (!first)
                ss << ", ";
            ss << field->serialize(get_value(key));
            first = false;
        }
        ss << ");";

        DB::execute(db, ss.str());
    }

    static void set_db(sqlite3* database) { db = database; }

protected:
    template <typename T>
    void set_value(const std::string& field_name, T value) {
        values[field_name] = new T(value);
    }

    void* get_value(const std::string& field_name) const {
        return values.at(field_name);
    }

private:
    std::map<std::string, void*> values; // Field values
};

sqlite3* Model::db = nullptr;

class User : public Model {
public:
    int id;
    std::string name;
    std::string email;

    User() {
        // Default constructor
    }

    User(std::string name, std::string email) {
        set_value("name", name);
        set_value("email", email);
    }

    std::string table_name() const override { return "user"; }

    std::map<std::string, Field*> get_fields() const override {
        return {
            {"name",  new CharField()},
            {"email", new CharField()}
        };
    }

    static void create_table() {
        std::string sql = R"(
            CREATE TABLE IF NOT EXISTS user (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                email TEXT NOT NULL
            );
        )";
        DB::execute(db, sql);
    }

    static std::vector<User> all() {
        std::vector<User> users;
        std::string sql = "SELECT id, name, email FROM user;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) ==
            SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                User user;
                user.id = sqlite3_column_int(stmt, 0);
                user.name =
                    reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                user.email =
                    reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                users.push_back(user);
            }
            sqlite3_finalize(stmt);
        }
        return users;
    }

    static std::vector<User> filter(const std::string& key,
                                    const std::string& value) {
        std::vector<User> users;
        std::stringstream sql;
        sql << "SELECT id, name, email FROM user WHERE " << key << " = '"
            << value << "';";

        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.str().c_str(), -1, &stmt, nullptr) ==
            SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                User user;
                user.id = sqlite3_column_int(stmt, 0);
                user.name =
                    reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                user.email =
                    reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
                users.push_back(user);
            }
            sqlite3_finalize(stmt);
        }
        return users;
    }
};

// Main Function
int main() {
    sqlite3* db = DB::connect("test.db");
    if (!db)
        return 1;

    Model::set_db(db);
    User::create_table();

    // Creating a user (similar to User.objects.create(...))
    User user1("Alice", "alice@example.com");
    user1.save();

    // Getting all users
    std::vector<User> users = User::all();
    std::cout << "All users:\n";
    for (const auto& u : users) {
        std::cout << u.name << " - " << u.email << "\n";
    }

    // Filtering users
    auto filtered = User::filter("name", "Alice");
    std::cout << "Filtered users:\n";
    for (const auto& u : filtered) {
        std::cout << u.name << " - " << u.email << "\n";
    }

    sqlite3_close(db);
    return 0;
}
