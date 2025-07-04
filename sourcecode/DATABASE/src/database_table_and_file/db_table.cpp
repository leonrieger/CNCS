#include "db_table_and_file.hpp"

int CNCS::database::DATABASE_TABLE::getter_callback(void* this_class_ptr,
                                                    int argc, char** argv,
                                                    char** columnName) {
    auto self = static_cast<DATABASE_TABLE*>(this_class_ptr);
    
    return 0;
}
