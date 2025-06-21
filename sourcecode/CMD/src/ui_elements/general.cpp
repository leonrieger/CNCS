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

float CNCS::cmd::general::calculate_percent(uint32_t amount_of_current_steps,
                                            uint32_t amount_of_all_steps) {
    return ((float)amount_of_current_steps / (float)amount_of_all_steps) * 100;
}
