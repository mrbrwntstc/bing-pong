#ifndef __SNEK_RENDER_H__
#define __SNEK_RENDER_H__

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h/linmath.h>

GLFWwindow* render_init();
void render_begin();
void render_end(GLFWwindow* game_window);
void render_quad(vec2 pos, vec2 size, vec4 color);

void render_cleanup(GLFWwindow* game_window);

#endif // __SNEK_RENDER_H__