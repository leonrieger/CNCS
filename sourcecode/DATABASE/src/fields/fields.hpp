#pragma once
#include <any>
#include <map>
#include <string>
#include <pugixml.hpp>

namespace CNCS::database::fields {
    class FIELD {
    public:
        virtual std::string convert_to_sql();

    private:
        std::map<std::string, std::any> properties;
    };
} // namespace CNCS::database::fields
