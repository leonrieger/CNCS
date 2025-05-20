#pragma once

#ifndef DEBUG_MODE
#	define DEBUG_MODE
#endif

#ifndef DEBUG_USING_TERMINAL
#	ifdef _DEBUG
#		define DEBUG_USING_TERMINAL
#	endif
#endif
