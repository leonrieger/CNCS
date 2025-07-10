#include "toolkit_selector.hpp"

#include <paths.hpp>

bool CNCS::toolkit::TOOLKIT_INTERFACE::load(const TOOLKIT& toolkit) {
    if (loaded_toolkits.count(toolkit.get()))
}

CNCS::toolkit::TOOLKIT_INTERFACE::~TOOLKIT_INTERFACE() {
    for (const auto& [_, lib] : loaded_toolkits) {
        if (lib != nullptr) {
            FreeLibrary(lib);
        }
    }
}
