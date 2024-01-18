#include "../render.h"
#include "render_internal.h"

static const game_window_width = 1280;
static const game_window_height = 960;

GLFWwindow* render_init() {
  GLFWwindow* game_window = render_init_window(game_window_width, game_window_height);

  return game_window;
}
