#include "math.hpp"

float DLLMODE CNCS::math::percentages::calculate_percent(int64_t current_value,
                                                 int64_t full_value) {
    return static_cast<float>((current_value / full_value) * 100);
}
