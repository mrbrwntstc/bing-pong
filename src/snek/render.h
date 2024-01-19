#ifndef __SNEK_RENDER_H__
#define __SNEK_RENDER_H__

#include <GLFW/glfw3.h>

GLFWwindow* render_init();
void render_begin();
void render_end(GLFWwindow* game_window);

#endif // __SNEK_RENDER_H__