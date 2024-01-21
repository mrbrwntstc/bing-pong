#include "../game.h"

GLFWwindow* game_init() 
{
  GLFWwindow* game_window = render_init();

  return game_window;
}

void game_run(GLFWwindow* game_window)
{
  #pragma region render_begin
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  #pragma endregion

  #pragma region game_update
  #pragma endregion

  #pragma region game_draw
  render_quad(
    (vec2){640, 480},
    (vec2){10,10},
    (vec4){0, 1, 0, 1}
  );
  #pragma endregion

  #pragma region render_end
  glfwPollEvents();
  glfwSwapBuffers(game_window);
  #pragma endregion
}
