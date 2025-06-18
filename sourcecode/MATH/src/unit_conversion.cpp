#include "MATH.hpp"

namespace math::unit_conversions {
    double inch_to_mm(double inches_to_be_converted) {
        return inches_to_be_converted * 25.4;
    }
    double inch_to_mm(int inches_to_be_converted) {
        return inches_to_be_converted * 25.4;
    }
}
