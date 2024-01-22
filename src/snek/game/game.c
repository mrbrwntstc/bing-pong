#include "../game.h"
#include "../render.h"
#include "../global_variables.h"

static GLFWwindow *game_window;

static vec2 pos;
static void input_handle()
{
  if(global_vars.input.left)
    pos[0] -= 500 * global_vars.time.delta_time_seconds;
  if(global_vars.input.right)
    pos[0] += 500 * global_vars.time.delta_time_seconds;
  if(global_vars.input.up)
    pos[1] += 500 * global_vars.time.delta_time_seconds;
  if(global_vars.input.down)
    pos[1] -= 500 * global_vars.time.delta_time_seconds;
}

void game_init() 
{
  time_init(60);
  game_window = render_init();
}

void game_loop()
{
  pos[0] = global_vars.game_window_width * 0.5;
  pos[1] = global_vars.game_window_height * 0.5;

  while(!glfwWindowShouldClose(game_window)) {
    time_update();

    #pragma region game_update
    input_handle();
    #pragma endregion
    
    #pragma region game_draw
    render_begin();
    render_quad(
        pos,
      (vec2){100,100},
      (vec4){0, 1, 0, 1}
    );
    render_end(game_window);
    #pragma endregion
    
    time_update_late(); 
  }
}

void game_cleanup()
{
  render_cleanup(game_window);
}
