#pragma once
#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

namespace ui_elements {

    uint16_t get_console_width();

    class progress_bar {
    public:
        progress_bar(string name, uint32_t steps_until_finished);
        void step();
        void step_multiple(uint32_t amaunt);
        void goto_value(uint32_t value);
        void goto_percent(uint8_t percent);
        void finish();
    private:
        uint32_t all_steps = 0;
        uint32_t current_steps = 0;
        uint8_t calculate_percent(uint32_t amaunt_of_all_steps, uint32_t amaunt_of_current_steps);
    };
    // https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

}
