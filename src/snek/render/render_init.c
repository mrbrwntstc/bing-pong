#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

#include "render_internal.h"
#include "../types.h"
#include "../util.h"


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

GLFWwindow* render_init_window(i32 width, i32 height)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
      ERROR_EXIT("Failed to initialize GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* game_window = glfwCreateWindow(width, height, "Snek", NULL, NULL);
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

    return game_window;
}