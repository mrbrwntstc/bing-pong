#ifndef __SNEK_TIME_H__
#define __SNEK_TIME_H__

#include "types.h"

typedef struct time_state_t
{
  f64 delta_time_seconds;
  f64 time_now_seconds;
  f64 time_now_previous_seconds;

  f64 frame_start_previous_seconds;
  f64 seconds_per_single_frame;
  f32 frame_time_completion_seconds;

  u32 frame_count;
  u32 frame_rate;
} time_state;

void time_init(u32 frame_rate);
void time_update();
void time_update_late();

#endif // __SNEK_TIME_H__