#include "../engine.h"

input_state engine_input_state = {0};
time_state engine_time_state = {0};

i32 game_window_width = 1280;
i32 game_window_height = 960;

GLFWwindow* engine_init()
{
  time_init(60);
  GLFWwindow* game_window = render_init();

  return game_window;
}

void engine_cleanup(GLFWwindow* game_window)
{
  render_cleanup(game_window);
}
