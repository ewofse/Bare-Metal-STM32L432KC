#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG

#define PARAMETER_ERROR() ( (void) 0U )

#ifdef DEBUG
	#define CHECK_PARAMETER(condition) ( (condition) ? ( (void) 0U ) : PARAMETER_ERROR() )
#else
	#define CHECK_PARAMETER(condition)
#endif

#endif

