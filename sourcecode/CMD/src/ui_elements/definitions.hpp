#pragma once

#if defined(_WIN32)
#define CONSOLE_CLEAR_COMMAND "cls"
#elif defined(__linux__)
#define CONSOLE_CLEAR_COMMAND "clear"
#endif
