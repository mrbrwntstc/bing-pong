#ifndef __SNEK_GLOBAL_VARIABLES_H__
#define __SNEK_GLOBAL_VARIABLES_H__

#include "input.h"
#include "time.h"
#include "types.h"

typedef struct global_variables_t
{
  input_state input;
  time_state time;
  i32 game_window_width;
  i32 game_window_height;
} global_variables;

extern global_variables global_vars;

#endif // __SNEK_GLOBAL_VARIABLES_H__