#ifndef __SNEK_ENGINE_H__
#define __SNEK_ENGINE_H__

#pragma region includes_native

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#pragma endregion

#pragma region includes_third_party

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <linmath.h/linmath.h>

#pragma endregion

#pragma region standardized_types

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float   f32;
typedef double  f64;
typedef size_t usize;

#pragma endregion

#pragma region error_handling

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }

#pragma endregion

#pragma region array_list

typedef struct array_list_t {
  usize len;
  usize capacity;
  usize item_size;
  void* data;
} array_list;

array_list *array_list_create(usize item_size, usize initial_capacity);
usize array_list_append(array_list *list, void *item);
void *array_list_get(array_list *list, usize index);
bool array_list_remove(array_list *list, usize index);

#pragma endregion

#pragma region input

typedef struct input_state_t
{
  bool left;
  bool right;
  bool up;
  bool down;
  bool grow;
} input_state;

extern input_state engine_input_state;
#pragma endregion

#pragma region io

typedef struct snek_file_t {
  char* data;
  usize len;
  bool is_valid;
} snek_file;

snek_file io_file_read(const char* path);

#pragma endregion

#pragma region render

extern i32 game_window_width;
extern i32 game_window_height;

GLFWwindow* render_init();
void render_begin();
void render_end(GLFWwindow* game_window);
void render_quad(vec2 pos, vec2 size, vec4 color);
void render_line_segment(vec2 start, vec2 end, vec4 color);
void render_quad_line(vec2 pos, vec2 size, vec4 color);
void render_cleanup(GLFWwindow* game_window);

#pragma endregion

#pragma region time

typedef struct time_state_t
{
  f64 delta_time_seconds;
  f64 time_now_seconds;
  f64 time_now_previous_seconds;

  f64 frame_start_previous_seconds;
  f64 seconds_per_single_frame;
  f32 frame_time_completion_seconds;

  u32 frame_count;
  u32 frame_rate;
} time_state;

extern time_state engine_time_state;

void time_init(u32 frame_rate);
void time_update();
void time_update_late();

#pragma endregion

#pragma region engine

GLFWwindow* engine_init();
void engine_cleanup(GLFWwindow* game_window);

#pragma endregion

#endif // __SNEK_ENGINE_H__
