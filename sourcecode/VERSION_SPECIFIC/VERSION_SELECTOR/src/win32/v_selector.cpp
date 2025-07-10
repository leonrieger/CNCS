#include "v_selector_win32.hpp"
#include <iostream>
#include <sstream>

namespace CNCS::toolkit {

    TOOLKIT_ACCESS::TOOLKIT_ACCESS(settings::version::VERSION& toolkit_version)
        : m_version(toolkit_version) {
        load_dll();
    }

    void TOOLKIT_ACCESS::load_dll() {
        // 1. Build DLL name from version
        std::ostringstream oss;
        oss << "toolkits\\TOOLKIT_" << settings::version::generate_version_str(m_version, true) << ".dll";
        std::string dllName = oss.str();

        // 2. Load the DLL
        m_dllHandle = LoadLibraryA(dllName.c_str());
        if (!m_dllHandle) {
            std::cerr << "Failed to load DLL: " << dllName << std::endl;
            return;
        }

        // 3. Get function pointer
        typedef void (*ToolkitEntryFunc)(const char*);
        ToolkitEntryFunc toolkit_entry = reinterpret_cast<ToolkitEntryFunc>(
            GetProcAddress(m_dllHandle, "test"));
        if (!toolkit_entry) {
            std::cerr << "Failed to find function 'test' in " << dllName << std::endl;
            FreeLibrary(m_dllHandle);
            m_dllHandle = nullptr;
            return;
        }

        // 4. Call the function
        const char* temp = "abcdefg";
        toolkit_entry(temp);
    }

    TOOLKIT_ACCESS::~TOOLKIT_ACCESS() {
        if (m_dllHandle) {
            FreeLibrary(m_dllHandle);
            m_dllHandle = nullptr;
        }
    }

} // namespace CNCS::toolkit
