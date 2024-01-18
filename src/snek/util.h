#ifndef __SNEK_UTIL_H__
#define __SNEK_UTIL_H__

#include <stdio.h>

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }

#define WHITE (vec4){1, 1, 1, 1}
#define GREEN (vec4){0, 1, 0, 1}


#endif // __SNEK_UTIL_H__