#pragma once

#ifdef DLLEXPORT
#	define DLLMODE __declspec(dllexport)
#else
#	define DLLMODE __declspec(dllimport)
#endif

namespace math::unit_conversions {
    double DLLMODE inch_to_mm(int inches_to_be_converted);
    double DLLMODE inch_to_mm(double inches_to_be_converted);
}
