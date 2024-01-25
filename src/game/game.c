#include "../game.h"

static GLFWwindow *game_window;
static array_list *snake;

void game_init()
{
  game_window = engine_init();
  game_snake_init(snake);
}

void game_loop()
{
  while(!glfwWindowShouldClose(game_window)) {
    time_update();

    // update

    // draw
    render_begin();
    game_snake_draw(snake);
    render_end(game_window);

    time_update_late();
  }
}

void game_cleanup()
{
  free(snake->data);

  engine_cleanup(game_window);
}
