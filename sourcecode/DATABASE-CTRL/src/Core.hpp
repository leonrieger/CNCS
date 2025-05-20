#pragma once

#ifndef DEBUG_MODE
#	define DEBUG_MODE
#endif

#ifdef NDEBUG
#	undef DEBUG_MODE
#endif

#ifndef DEBUG_USING_TERMINAL
#	ifdef _DEBUG
#		define DEBUG_USING_TERMINAL
#	endif
#endif

#ifndef __cplusplus
#	error A C++ compiler is required!
#endif 
