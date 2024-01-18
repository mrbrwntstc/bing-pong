#include "snek/render.h"

int main()
{
  GLFWwindow* game_window = render_init();
  while(!glfwWindowShouldClose(game_window)) {
    glfwPollEvents();
    glfwSwapBuffers(game_window);
  }

  glfwDestroyWindow(game_window);
  glfwTerminate();

  return 0;
}
