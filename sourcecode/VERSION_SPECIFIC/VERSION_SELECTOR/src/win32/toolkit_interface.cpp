#include "toolkit_selector.hpp"

#include <paths.hpp>

#include <filesystem>

bool CNCS::toolkit::TOOLKIT_INTERFACE::load(const TOOLKIT& toolkit) {
    std::string path = TOOLKIT_PATH + toolkit.get();

    if (!std::filesystem::exists(path)) {
        return false;
    }

    if (loaded_toolkits.count(path)) {
        active_toolkit = path;
        return true;
    }

    HMODULE reference = LoadLibraryA(path.c_str());

    if (!reference) {
        return false;
    }

    loaded_toolkits.emplace(path, reference);
    active_toolkit = path;
    return true;
}

void CNCS::toolkit::TOOLKIT_INTERFACE::get_functions(
    std::unordered_map<std::string, void*>& function_list) const {
    for (auto& [name, reference] : function_list) {
        reference =
            GetProcAddress(loaded_toolkits.at(active_toolkit), name.c_str());
        if (!reference) {
            reference = nullptr;
        }
    }
}

CNCS::toolkit::TOOLKIT_INTERFACE::~TOOLKIT_INTERFACE() {
    for (const auto& [_, lib] : loaded_toolkits) {
        if (lib != nullptr) {
            FreeLibrary(lib);
        }
    }
}
