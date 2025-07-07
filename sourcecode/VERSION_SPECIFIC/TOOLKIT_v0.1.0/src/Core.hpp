#pragma once

#ifdef TOOLKIT_DLLEXPORT
#    define TOOLKIT_DLLMODE __declspec(dllexport)
#else
#    define TOOLKIT_DLLMODE __declspec(dllimport)
#endif
