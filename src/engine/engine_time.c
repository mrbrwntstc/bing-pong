#ifdef _WIN32
  #include <windows.h>
  #define sleep Sleep
#endif

#include "../engine.h"

void time_init(u32 frame_rate)
{
  engine_time_state.frame_rate = frame_rate;
  engine_time_state.seconds_per_single_frame = 1.0 / frame_rate;
}

void time_update()
{
  engine_time_state.time_now_seconds = glfwGetTime();
  engine_time_state.delta_time_seconds = engine_time_state.time_now_seconds - engine_time_state.time_now_previous_seconds;
  engine_time_state.time_now_previous_seconds = engine_time_state.time_now_seconds;
  ++engine_time_state.frame_count;

  if(engine_time_state.time_now_seconds - engine_time_state.frame_start_previous_seconds >= 1.0) {
    engine_time_state.frame_rate = engine_time_state.frame_count;
    engine_time_state.frame_count = 0;
    engine_time_state.frame_start_previous_seconds = engine_time_state.time_now_seconds;
  }
}

void time_update_late()
{
  engine_time_state.frame_time_completion_seconds = glfwGetTime() - engine_time_state.time_now_seconds;
  if (engine_time_state.frame_time_completion_seconds < engine_time_state.seconds_per_single_frame) {
    sleep(engine_time_state.seconds_per_single_frame - engine_time_state.frame_time_completion_seconds);
  }
}
