#include "../game.h"

GLFWwindow* game_init() 
{
  GLFWwindow* game_window = render_init();

  return game_window;
}

void game_run(GLFWwindow* game_window)
{
  render_begin();

  #pragma region game_update
  #pragma endregion

  #pragma region game_draw
  render_quad(
    (vec2){640, 480},
    (vec2){10,10},
    (vec4){0, 1, 0, 1}
  );
  #pragma endregion

  render_end(game_window);
}
