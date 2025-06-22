#pragma once

#ifdef ALLOW_SETTINGS_DLLEXPORT
#define DLLMODE __declspec(dllexport)
#else
#define DLLMODE __declspec(dllimport)
#endif
