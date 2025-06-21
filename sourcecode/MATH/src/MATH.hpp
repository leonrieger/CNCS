#pragma once
#include <stdint.h>

#ifdef DLLEXPORT
#define DLLMODE __declspec(dllexport)
#else
#define DLLMODE __declspec(dllimport)
#endif

namespace CNCS::math {
    namespace unit_conversions {
        double DLLMODE inch_to_mm(int inches_to_be_converted);
        double DLLMODE inch_to_mm(double inches_to_be_converted);
    }

    namespace percentages {
        float DLLMODE calculate_percent(int64_t current_value, int64_t full_value);
    }
}
