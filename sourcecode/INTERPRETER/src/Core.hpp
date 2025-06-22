#pragma once

#ifdef ALLOW_INTERPRETER_DLLEXPORT
#define DLLMODE __declspec(dllexport)
#else
#define DLLMODE __declspec(dllimport)
#endif
