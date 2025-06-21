#include "math.hpp"

template <typename T>
float CNCS::math::percentages::calculate_percent(T current_value,
                                                 T full_value) {
    return static_cast<float>((current_value / full_value) * 100f)
}
