#pragma once

#ifdef ALLOW_SETTINGS_DLLEXPORT
#define SETTINGS_DLLMODE __declspec(dllexport)
#else
#define SETTINGS_DLLMODE __declspec(dllimport)
#endif
