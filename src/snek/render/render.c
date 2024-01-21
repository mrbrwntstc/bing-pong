#include <stdio.h>
#include <stdlib.h>

#include "../render.h"
#include "../types.h"
#include "../util.h"

#pragma region window_dimensions
static const game_window_width = 1280;
static const game_window_height = 960;
#pragma endregion

#pragma region shader_variables

static u32 vao_quad;
static u32 vbo_quad;
static u32 ebo_quad;
static u32 shader_default;
static u32 texture_color;

#pragma endregion

#pragma region glfw_callback_functions
static void glfw_error_callback(i32 error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void glfw_key_callback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, i32 width, i32 height)
{
    glViewport(0, 0, width, height);
}
#pragma endregion

GLFWwindow* render_init()
{
  #pragma region render_init_window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    ERROR_EXIT("Failed to initialize GLFW\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* game_window = glfwCreateWindow(game_window_width, game_window_height, "Snek", NULL, NULL);
  if (!game_window) {
    glfwTerminate();
    ERROR_EXIT("Failed to create game window\n");
  }
  glfwMakeContextCurrent(game_window);
  glfwSetKeyCallback(game_window, glfw_key_callback);
  glfwSetFramebufferSizeCallback(game_window, glfw_framebuffer_size_callback);
  glfwSwapInterval(1);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    ERROR_EXIT("Failed to initialize GLAD\n");
  }
  #pragma endregion

  #pragma region render_init_quad
  f32 vertices[] = {
     0.5,  0.5, 0, 0, 0,
     0.5, -0.5, 0, 0, 1,
    -0.5, -0.5, 0, 1, 1,
    -0.5,  0.5, 0, 1, 0
  };

  u32 indices[] = {
      0, 1, 3,
      1, 2, 3
  };

  glGenVertexArrays(1, &vao_quad);
  glGenBuffers(1, &vbo_quad);
  glGenBuffers(1, &ebo_quad);

  glBindVertexArray(vao_quad);
  
  glBindBuffer(GL_ARRAY_BUFFER, vbo_quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_quad);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  #pragma endregion

  return game_window;
}

void render_quad(vec2 pos, vec2 size, vec4 color)
{
  glBindVertexArray(vao_quad);
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}
