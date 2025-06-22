#pragma once

#ifdef ALLOW_INTERPRETER_DLLEXPORT
#define INTERPRETER_DLLMODE __declspec(dllexport)
#else
#define INTERPRETER_DLLMODE __declspec(dllimport)
#endif
