#include "MATH.hpp"

namespace CNCS::math::unit_conversions {
    double MATH_DLLMODE inch_to_mm(double inches_to_be_converted) {
        return inches_to_be_converted * 25.4;
    }
    double MATH_DLLMODE inch_to_mm(int inches_to_be_converted) {
        return inches_to_be_converted * 25.4;
    }
} // namespace CNCS::math::unit_conversions
