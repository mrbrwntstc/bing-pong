#ifdef _WIN32
  #include <windows.h>
  #define sleep Sleep
#endif

#include <GLFW/glfw3.h>

#include "../time.h"
#include "../global_variables.h"

void time_init(u32 frame_rate)
{
  global_vars.time.frame_rate = frame_rate;
  global_vars.time.seconds_per_single_frame = 1.0 / frame_rate;
}

void time_update()
{
  global_vars.time.time_now_seconds = glfwGetTime();
  global_vars.time.delta_time_seconds = global_vars.time.time_now_seconds - global_vars.time.time_now_previous_seconds;
  global_vars.time.time_now_previous_seconds = global_vars.time.time_now_seconds;
  ++global_vars.time.frame_count;

  if(global_vars.time.time_now_seconds - global_vars.time.frame_start_previous_seconds >= 1.0) {
    global_vars.time.frame_rate = global_vars.time.frame_count;
    global_vars.time.frame_count = 0;
    global_vars.time.frame_start_previous_seconds = global_vars.time.time_now_seconds;
  }
}

void time_update_late()
{
  global_vars.time.frame_time_completion_seconds = glfwGetTime() - global_vars.time.time_now_seconds;
  if (global_vars.time.frame_time_completion_seconds < global_vars.time.seconds_per_single_frame) {
    sleep(global_vars.time.seconds_per_single_frame - global_vars.time.frame_time_completion_seconds);
  }
}
