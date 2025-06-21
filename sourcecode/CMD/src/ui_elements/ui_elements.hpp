#pragma once
#include <iostream>
#include <string>
#include <stdint.h>

namespace ui_elements {
    struct color_table {
        const std::string NONE = "";
        const std::string HEADER = "\033[95m";
        const std::string OKBLUE = "\033[94m";
        const std::string OKCYAN = "\033[96m";
        const std::string OKGREEN = "\033[92m";
        const std::string WARNING = "\033[93m";
        const std::string FAIL = "\033[91m";
        const std::string ENDC = "\033[0m";
        const std::string BOLD = "\033[1m";
        const std::string UNDERLINE = "\033[4m";
    };

    namespace common {
        float calculate_percent(uint32_t amount_of_current_steps, uint32_t amount_of_all_steps);
        void get_terminal_size(int& width, int& height);

        std::string input();
        std::string input(std::string message);
    }

    class progress_bar {
    public:
        progress_bar(string name, uint32_t steps_until_finished, string color);
        void step();
        void step_multiple(int64_t amount);
        void goto_value(uint32_t value);
        void finish();
    private:
        void refresh();
        uint32_t all_steps = 0;
        uint32_t current_steps = 0;
        string color_selected;
    };
}
