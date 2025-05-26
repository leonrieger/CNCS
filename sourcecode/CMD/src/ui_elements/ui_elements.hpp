#pragma once
#include <iostream>
#include <string>
#include <stdint.h>

using namespace std;

namespace ui_elements {
    struct color_table {
        string NONE = "";
        string HEADER = "\033[95m";
        string OKBLUE = "\033[94m";
        string OKCYAN = "\033[96m";
        string OKGREEN = "\033[92m";
        string WARNING = "\033[93m";
        string FAIL = "\033[91m";
        string ENDC = "\033[0m";
        string BOLD = "\033[1m";
        string UNDERLINE = "\033[4m";
    };
    
    namespace common {
        float calculate_percent(uint32_t amount_of_current_steps, uint32_t amount_of_all_steps);
        void get_terminal_size(int& width, int& height);
    }

    class progress_bar {
    public:
        progress_bar(uint32_t steps_until_finished, string color);
        void step();
        void step_multiple(uint32_t amount);
        void goto_value(uint32_t value);
        void goto_percent(uint8_t percent);
        void finish();
    private:
        void refresh();
        uint32_t all_steps = 0;
        uint32_t current_steps = 0;
        string color_selected;
    };
}
