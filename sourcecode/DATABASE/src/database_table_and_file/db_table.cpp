#include "db_table_and_file.hpp"

int CNCS::database::DATABASE_TABLE::getter_callback(void* NotUsed, int argc,  
                                                    char** argv,  
                                                    char** columnName) {  
    this->db_content.push_back(/* appropriate value or object */);  
    return 0;  
}
