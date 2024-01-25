#include "../engine.h"

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
  engine_input_state.left = (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT));
  engine_input_state.right = (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT));
  engine_input_state.up = (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT));
  engine_input_state.down = (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT));

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
  // window not resizable
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
    0, 1, 0, 0, 1,
    1, 0, 0, 1, 0,
    0, 0, 0, 0, 0,
    1, 1, 0, 1, 1,
  };

  u32 indices[] = {
      0, 1, 2,
      0, 1, 3
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

  #pragma region render_init_texture_color
  glGenTextures(1, &texture_color);
  glBindTexture(GL_TEXTURE_2D, texture_color);

  u8 solid_white[4] = {255, 255, 255, 255};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

  glBindTexture(GL_TEXTURE_2D, 0);
  #pragma endregion

  #pragma region render_init_shaders

  i32 success;
  char log[512];
  #pragma region create_vertex_shader
  snek_file file_vertex = io_file_read("shaders/default.vert");
  if(!file_vertex.is_valid)
    ERROR_EXIT("Failed to read shaders/default.vert\n");
  u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(shader_vertex, 1, (const char**)&file_vertex.data, NULL);
  glCompileShader(shader_vertex);
  glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
  if(!success) {
    free(file_vertex.data);
    glGetShaderInfoLog(shader_vertex, 512, NULL, log);
    ERROR_EXIT("Failed to compile vertex shader: %s\n", log);
  }
  free(file_vertex.data);
  #pragma endregion

  #pragma region create_fragment_shader
  snek_file file_fragment = io_file_read("shaders/default.frag");
  if(!file_fragment.is_valid)
    ERROR_EXIT("Failed to read shaders/default.frag\n");
  u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(shader_fragment, 1, (const char**)&file_fragment.data, NULL);
  glCompileShader(shader_fragment);
  glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
  if(!success) {
    free(file_fragment.data);
    glGetShaderInfoLog(shader_fragment, 512, NULL, log);
    ERROR_EXIT("Failed to compile fragment shader: %s\n", log);
  }
  free(file_fragment.data);
  #pragma endregion

  #pragma region link_vertex_fragment
  shader_default = glCreateProgram();
  glAttachShader(shader_default, shader_vertex);
  glAttachShader(shader_default, shader_fragment);
  glLinkProgram(shader_default);
  glGetProgramiv(shader_default, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shader_default, 512, NULL, log);
    ERROR_EXIT("Failed to link shader program: %s\n", log);
  }
  glDeleteShader(shader_vertex);
  glDeleteShader(shader_fragment);
  #pragma endregion
  
  #pragma region initialization_projection_matrix

  mat4x4 projection;
  mat4x4_ortho(projection, 0.0f, game_window_width, game_window_height, 0.0f, -1.0f, 1.0f);

  glUseProgram(shader_default);
  glUniformMatrix4fv(glGetUniformLocation(shader_default, "projection"), 1, GL_FALSE, &projection[0][0]);
  
  #pragma endregion

  #pragma endregion

  return game_window;
}

void render_quad(vec2 pos, vec2 size, vec4 color)
{
  glUseProgram(shader_default);

  mat4x4 model;
  mat4x4_identity(model);
  mat4x4_translate(model, pos[0], pos[1], 0.0f);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1.0f);

  glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
  glUniform4fv(glGetUniformLocation(shader_default, "color"), 1, &color[0]);

  glBindVertexArray(vao_quad);
  
  glBindTexture(GL_TEXTURE_2D, texture_color);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}

void render_begin()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(GLFWwindow* game_window)
{
  glfwPollEvents();
  glfwSwapBuffers(game_window);
}

void render_cleanup(GLFWwindow* game_window)
{
  glfwDestroyWindow(game_window);
  glfwTerminate();
}
