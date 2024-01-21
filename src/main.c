#include "snek/game.h"

int main()
{
  GLFWwindow* game_window = game_init();
  
  while(!glfwWindowShouldClose(game_window))
    game_run(game_window);

  glfwDestroyWindow(game_window);
  glfwTerminate();

  return 0;
}
