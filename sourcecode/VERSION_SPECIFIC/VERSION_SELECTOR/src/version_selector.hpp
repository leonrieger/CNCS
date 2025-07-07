#pragma once

#if defined(_WIN32)
#include "win32/v_selector_win32.hpp"
#elif defined(__linux__)
#include "linux/v_selector_linux.hpp"
#endif
