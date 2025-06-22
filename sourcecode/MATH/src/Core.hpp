#pragma once

#ifdef DLLEXPORT
#define MATH_DLLMODE __declspec(dllexport)
#else
#define MATH_DLLMODE __declspec(dllimport)
#endif
