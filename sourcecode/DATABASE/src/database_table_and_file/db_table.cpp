#include "db_table_and_file.hpp"

#include <iostream>

int CNCS::database::DATABASE_TABLE::getter_callback(void* this_class_ptr,
                                                    int argc, char** argv,
                                                    char** columnName) {
    auto self = static_cast<DATABASE_TABLE*>(this_class_ptr);
    
    for (uint32_t i = 0; i < argc; ++i) {
        std::cout << columnName[i] << " : " << argv[i] << std::endl;
    }

    return 0;
}
