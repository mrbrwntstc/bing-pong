#include <glad/glad.h>

#include "../render.h"
#include "render_internal.h"

static const game_window_width = 1280;
static const game_window_height = 960;

GLFWwindow* render_init() {
  GLFWwindow* game_window = render_init_window(game_window_width, game_window_height);

  return game_window;
}

void render_begin()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(GLFWwindow* game_window)
{
  glfwSwapBuffers(game_window);
  glfwPollEvents();
}
