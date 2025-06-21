#include "ui_elements.hpp"

#include <format>
#include <iostream>

CNCS::cmd::ui_elements::progress_bar::progress_bar(std::string name, uint32_t steps_until_finished, const std::string color) {
    const std::string color_selected = color;
    all_steps = steps_until_finished;
    current_steps = 0;
    if (sizeof(name) > 0) {
        std::cout << "*** " << name << " ***" << std::endl;
    }
    refresh();
}

void CNCS::cmd::ui_elements::progress_bar::refresh() {
    int16_t width, height;
    CNCS::cmd::general::get_terminal_size(width, height);

    int32_t actual_width = width - 9;
    int full_width = int(actual_width * ((float)current_steps / (float)all_steps));

    std::cout << color_selected << "\r|";
    
    for (int i = 0; i < full_width; i++) {
        cout << "=";
    }
    for (int i = 0; i < (actual_width - full_width); i++) {
        cout << "-";
    }
    float percent = common::calculate_percent(current_steps, all_steps);
    cout << "|\033[0m " << format("{0:5.01f}%", percent);
}

void CNCS::cmd::ui_elements::progress_bar::step() {
    current_steps++;
    if (current_steps > all_steps) {
        finish();
    }
    else {
        refresh();
    }
}

void CNCS::cmd::ui_elements::progress_bar::step_multiple(int64_t amount) {
    if ((current_steps += amount) < 0) {
        current_steps = 0;
    }
    else if ((current_steps += amount) > 0) {
        finish();
    }
    else {
        current_steps += amount;
    }
    refresh();
}

void CNCS::cmd::ui_elements::progress_bar::goto_value(uint32_t value) {
    current_steps = value;
    refresh();
}

void CNCS::cmd::ui_elements::progress_bar::finish() {
    current_steps = all_steps;
    refresh();
    std::cout << std::endl;
}
