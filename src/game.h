#ifndef __SNEK_GAME_H__
#define __SNEK_GAME_H__

#include "engine.h"

#pragma region game_board

const u32 game_board_cell_dimension = 40; // 40x40
const u32 game_board_columns = 32; // 32 * 40 = 1280
const u32 game_board_rows = 24;;   // 24 * 40 = 960

#pragma endregion

#pragma region game_snake

typedef struct game_snake_segment_t {
  vec2 board_cell_coordinate;
  vec2 direction;
  vec4 color;
} game_snake_segment;

void game_snake_init(array_list *snake);
void game_snake_draw(array_list* snake);

#pragma endregion

#pragma region game

void game_init();
void game_loop();
void game_cleanup();

#pragma endregion

#endif // __SNEK_GAME_H__