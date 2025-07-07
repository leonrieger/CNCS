#include "db_table_and_file.hpp"

#include <format>
#include <iostream>

int CNCS::database::DATABASE_TABLE::getter_callback(void* this_class_ptr,
                                                    int argc, char** argv,
                                                    char** columnName) {
    auto self = static_cast<DATABASE_TABLE*>(this_class_ptr);

    if (self->list_of_fields.size() != argc) {
        return SQLITE_ERROR;
    }

    std::map<std::string, DB_RETURN_TYPES> temp_return = {};

    for (int32_t i = 0; i < argc; ++i) {
        if (!(self->list_of_fields[i]->is_name_compatible(
                std::string(columnName[i])))) {
            return SQLITE_ERROR;
        } else {
            temp_return.insert({
                {

                 std::string(columnName[i]),
                 self->list_of_fields[i]->create_data(
                        std::string(argv[i]))}
            });
        }
    }

    for (auto& [name, value] : temp_return) {
        std::cout << name << " : " << std::get<int64_t>(value) << "\n";
    }

    self->db_content.push_back(temp_return);

    return SQLITE_OK;
}

void CNCS::database::DATABASE_TABLE::tmp() {
    sqlite3_exec(db_file_pointer,
                 std::format("select * from {}", db_table_name).c_str(),
                 getter_callback, this, nullptr);
}
