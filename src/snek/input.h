#ifndef __SNEK_INPUT_H__
#define __SNEK_INPUT_H__

#include <stdbool.h>

typedef struct input_state_t
{
  bool left;
  bool right;
  bool up;
  bool down;
} input_state;

#endif // __SNEK_INPUT_H__