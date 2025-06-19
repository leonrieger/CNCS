#pragma once

namespace CNCS::settings::interpreter {
    struct user_environment_settings {

    };

    struct global_environment_settings {

    };

    bool load_settings(user_environment_settings& settings);
    bool load_settings(global_environment_settings& settings);
}
