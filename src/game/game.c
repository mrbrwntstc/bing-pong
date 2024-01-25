#include "../game.h"

GLFWwindow *game_window;

static array_list *snake;

void game_init()
{
  game_window = engine_init();
  snake = game_snake_init();
}

void game_loop()
{
  vec2 direction = {1, 0};
  u32 move_period = 20;
  u32 move_counter = 0;

  while(!glfwWindowShouldClose(game_window)) {
    time_update();

    // update
    if(engine_input_state.left) {
      direction[0] = -1;
      direction[1] = 0;
    } else if(engine_input_state.right) {
      direction[0] = 1;
      direction[1] = 0;
    } else if(engine_input_state.up) {
      direction[0] = 0;
      direction[1] = -1;
    } else if(engine_input_state.down) {
      direction[0] = 0;
      direction[1] = 1;
    } 

    // the snake needs to look like it's traveling in a grid
    move_counter++;
    if(move_counter >= move_period) {
      move_counter = 0;
      game_board_col_row snake_head_next_col_row = game_snake_head_next_col_row(snake, direction);
    }
    
    // draw
    render_begin();
    game_snake_draw(snake);
    render_end(game_window);

    time_update_late();
  }
}

void game_cleanup()
{
  free(snake);
  engine_cleanup(game_window);
}
