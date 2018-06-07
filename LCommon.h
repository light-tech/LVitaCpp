#ifndef _LVITACPP_COMMON_
#define _LVITACPP_COMMON_

#ifndef STATIC_INLINE
#define STATIC_INLINE static inline
#endif

#ifdef _DEVMAX_INTERPRETER_
// Declare the standard functions when interpreting with DevMax C++ interpreter
extern "C" void *realloc(void* ptr, int size);

// DevMax C++ interpreter API function
#ifdef __cplusplus
extern "C"
{
#endif
	void PrintString(const char*);
#ifdef __cplusplus
}
#endif

#else // _DEVMAX_INTERPRETER_ not defined, use standard library
#include <assert.h>
#include <stdlib.h>
#endif

#endif