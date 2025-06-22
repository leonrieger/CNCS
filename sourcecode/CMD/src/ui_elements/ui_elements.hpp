#pragma once
#include <stdint.h>
#include <string>

namespace CNCS::cmd {
    static struct color_table {
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

    namespace general {
        void get_terminal_size(int16_t& width, int16_t& height);
        void clear_terminal();
    } // namespace general

    namespace ui_elements {
        class progress_bar {
        public:
            progress_bar(std::string name, uint32_t steps_until_finished,
                         std::string color);
            void step();
            void step_multiple(int64_t amount);
            void goto_value(uint32_t value);
            void finish();

        private:
            void refresh();
            uint32_t all_steps = 0;
            uint32_t current_steps = 0;
            std::string color_selected;
        };

        std::string input();
        std::string input(std::string message);
    } // namespace ui_elements
} // namespace CNCS::cmd
