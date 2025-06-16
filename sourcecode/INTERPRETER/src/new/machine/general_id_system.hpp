#pragma once

#include <string>

namespace CNCS {
    namespace cnc_machine {
        namespace tools {
            struct toolID {
                uint16_t machineID;
                uint8_t toolClass;
                uint8_t toolSubClass;
                uint16_t toolIdentifier;
                uint16_t toolSubIdentifier;
            };

            std::string generateToolIdString(toolID& toolidentifier);
            toolID generateToolIdStruct(std::string& toolidentifier);

        } // namespace tools
    } // namespace cnc_machine
} // namespace CNCS