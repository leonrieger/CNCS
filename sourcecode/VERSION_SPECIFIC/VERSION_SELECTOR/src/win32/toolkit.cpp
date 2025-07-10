#include "toolkit_selector.hpp"

#include <names.hpp>

bool CNCS::toolkit::TOOLKIT::set(const CNCS::settings::VERSION& version) {
    if (CNCS::settings::is_version_allowed(version)) {
        internal_toolkit_version = version;
        return true;
    }
    return false;
}

std::string CNCS::toolkit::TOOLKIT::get() const {
    if (internal_toolkit_version != NULL) {
        return TOOLKIT_STD_NAME + CNCS::settings::generate_version_str(internal_toolkit_version,
                                                    true) +
               ".dll";
    }
}
