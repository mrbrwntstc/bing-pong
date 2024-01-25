#include <stdio.h>

#include "engine.h"

int main()
{
  time_init(60);
  GLFWwindow* game_window = engine_init();

  vec2 pos = {0, 12};
  vec2 direction = {1, 0};
  const u32 dimension = 40;
  const u32 board_cols = 32; // 32 * 40 = 1280
  const u32 board_rows = 24; // 24 * 40 = 960

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

    // the snake does not update every frame
    move_counter++;
    if(move_counter >= move_period) {
      move_counter = 0;
      pos[0] += direction[0];
      pos[1] += direction[1];
      if(pos[0] >= board_cols)
        pos[0] = 0;
    }

    // draw
    render_begin();
    render_quad(
      (vec2){pos[0] * dimension, pos[1] * dimension},
      (vec2) {dimension, dimension},
      (vec4) {1, 0, 0, 1}
    );
    render_end(game_window);

    time_update_late();
  }

  engine_cleanup(game_window);

  return 0;
}
