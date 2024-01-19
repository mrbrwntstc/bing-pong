#include "../game.h"
#include "../render.h"

static GLFWwindow* game_window;

void game_init() 
{
  game_window = render_init();
}

void game_run()
{
  while(!glfwWindowShouldClose(game_window))
  {
    render_begin();

    render_end(game_window);
  }
}

void game_cleanup()
{
  glfwDestroyWindow(game_window);
  glfwTerminate();
}
