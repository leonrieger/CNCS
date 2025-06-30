#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <vector>

// DB Connection and Execution Utility
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

    static std::vector<std::vector<std::string>> query(sqlite3* db,
                                                       const std::string& sql) {
        sqlite3_stmt* stmt;
        std::vector<std::vector<std::string>> result;

        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) ==
            SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::vector<std::string> row;
                for (int i = 0; i < sqlite3_column_count(stmt); i++) {
                    row.push_back(reinterpret_cast<const char*>(
                        sqlite3_column_text(stmt, i)));
                }
                result.push_back(row);
            }
            sqlite3_finalize(stmt);
        }
        return result;
    }
};

// Field Types for Model (like Django's field classes)
class Field {
public:
    virtual std::string type() const = 0;
    virtual std::string serialize(const void* value) const = 0;
    virtual ~Field() = default;
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

class DateField : public Field {
public:
    std::string type() const override {
        return "TEXT"; // SQLite stores dates as text in the format "YYYY-MM-DD"
    }

    std::string serialize(const void* value) const override {
        // Assuming value is a string in date format
        return "'" + std::string(*static_cast<const std::string*>(value)) + "'";
    }
};

class ForeignKey : public Field {
public:
    ForeignKey(const std::string& related_model)
        : related_model_(related_model) {}

    std::string type() const override {
        return "INTEGER"; // Foreign Key is an INTEGER (ID)
    }

    std::string serialize(const void* value) const override {
        return std::to_string(
            *static_cast<const int*>(value)); // ID of the related model
    }

private:
    std::string related_model_;
};

// Base Model Class (like Django's Model)
class Model {
public:
    static sqlite3* db;

    virtual std::string table_name() const = 0;
    virtual std::map<std::string, Field*> get_fields() const = 0;

    void save() {
        auto fields = get_fields();
        std::stringstream ss;

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

    void update(const std::map<std::string, void*>& updated_fields) {
        std::stringstream ss;
        ss << "UPDATE " << table_name() << " SET ";
        bool first = true;

        for (const auto& [field_name, field_value] : updated_fields) {
            if (!first)
                ss << ", ";
            auto field = get_fields().at(field_name);
            ss << field_name << " = " << field->serialize(field_value);
            first = false;
        }

        ss << " WHERE id = " << get_value("id") << ";";
        DB::execute(db, ss.str());
    }

    void delete_object() {
        std::stringstream ss;
        ss << "DELETE FROM " << table_name()
           << " WHERE id = " << get_value("id") << ";";
        DB::execute(db, ss.str());
    }

    static void set_db(sqlite3* database) { db = database; }

    template <typename T>
    void set_value(const std::string& field_name, T value) {
        values[field_name] = new T(value);
    }

protected:
    void* get_value(const std::string& field_name) const {
        return values.at(field_name);
    }

private:
    std::map<std::string, void*> values; // Field values
};

sqlite3* Model::db = nullptr;

// ==============================
// User Model (Example of Django-like Model)
// ==============================
class User : public Model {
public:
    int id;
    std::string name;
    std::string email;
    std::string created_at;

    User() {}

    User(std::string name, std::string email, std::string created_at)
        : name(name), email(email), created_at(created_at) {}

    std::string table_name() const override { return "user"; }

    std::map<std::string, Field*> get_fields() const override {
        return {
            {"name",       new CharField()},
            {"email",      new CharField()},
            {"created_at", new DateField()}
        };
    }

    static void create_table() {
        std::string sql = R"(
            CREATE TABLE IF NOT EXISTS user (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                email TEXT NOT NULL,
                created_at TEXT NOT NULL
            );
        )";
        DB::execute(db, sql);
    }

    static std::vector<User> all() {
        std::vector<User> users;
        std::string sql = "SELECT id, name, email, created_at FROM user;";
        auto rows = DB::query(db, sql);
        for (const auto& row : rows) {
            User user;
            user.id = std::stoi(row[0]);
            user.name = row[1];
            user.email = row[2];
            user.created_at = row[3];
            users.push_back(user);
        }
        return users;
    }

    static std::vector<User> filter(const std::string& key,
                                    const std::string& value) {
        std::vector<User> users;
        std::stringstream sql;
        sql << "SELECT id, name, email, created_at FROM user WHERE " << key
            << "='" << value << "';";
        auto rows = DB::query(db, sql.str());
        for (const auto& row : rows) {
            User user;
            user.id = std::stoi(row[0]);
            user.name = row[1];
            user.email = row[2];
            user.created_at = row[3];
            users.push_back(user);
        }
        return users;
    }
};

int main() {
    sqlite3* db = DB::connect("test.db");
    if (!db)
        return 1;

    Model::set_db(db);
    User::create_table();

    // Create a new user
    User user1("Alice", "alice@example.com", "2025-06-30");
    user1.save();

    // Retrieve all users
    std::vector<User> users = User::all();
    std::cout << "All users:\n";
    for (const auto& u : users) {
        std::cout << u.name << " - " << u.email << " - " << u.created_at
                  << "\n";
    }

    // Update user
    user1.set_value("name", std::string("Alice Updated"));
    user1.update({
        {"name",  &user1.name },
        {"email", &user1.email}
    });

    // Delete user
    user1.delete_object();

    sqlite3_close(db);
    return 0;
}
