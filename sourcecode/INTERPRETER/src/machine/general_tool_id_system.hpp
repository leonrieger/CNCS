#pragma once

#include <string>

namespace CNCS::cnc_machine::tools {
    struct toolID {
        uint16_t machineID;
        uint8_t toolClass;
        uint8_t toolSubClass;
        uint16_t toolIdentifier;
        uint16_t toolSubIdentifier;
    };

    std::string generateToolIdString(toolID& toolidentifier);
    toolID generateToolIdStruct(std::string& toolidentifier);

} // namespace CNCS::cnc_machine::tools
