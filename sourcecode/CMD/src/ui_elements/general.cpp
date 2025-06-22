#include "definitions.hpp"
#include "ui_elements.hpp"
#include <string>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#elif defined(__linux__)
#include <sys/ioctl.h>
#endif

void CNCS::cmd::general::get_terminal_size(int16_t& width, int16_t& height) {
#if defined(_WIN32) || defined(_WIN64)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = static_cast<int16_t>(csbi.srWindow.Right - csbi.srWindow.Left + 1);
    height = static_cast<int16_t>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__)
    winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = static_cast<int16_t>(w.ws_col);
    height = static_cast<int16_t>(w.ws_row);
#endif
}

void CNCS::cmd::general::clear_terminal() { system(CONSOLE_CLEAR_COMMAND); }
