#pragma once
#include "Core.hpp"
#include <stdint.h>

namespace CNCS::math {
    namespace unit_conversions {
        double MATH_DLLMODE inch_to_mm(int inches_to_be_converted);
        double MATH_DLLMODE inch_to_mm(double inches_to_be_converted);
    } // namespace unit_conversions

    namespace percentages {
        float MATH_DLLMODE calculate_percent(int64_t current_value,
                                             int64_t full_value);
    }
} // namespace CNCS::math
