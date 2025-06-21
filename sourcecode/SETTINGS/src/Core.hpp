#pragma once

#ifdef ALLOW_DLL_EXPORT
#define DLLMODE __declspec(dllexport)
#else
#define DLLMODE __declspec(dllimport)
#endif
