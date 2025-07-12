#pragma once

#if defined(_WIN32)
#include "win32/toolkit_selector.hpp"
#elif defined(__linux__)
#include "linux/v_selector_linux.hpp"
#endif
