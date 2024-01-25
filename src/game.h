#ifndef __SNEK_GAME_H__
#define __SNEK_GAME_H__

#include "engine.h"

#pragma region game_board

typedef struct game_board_col_row_t {
  u32 col;
  u32 row;
} game_board_col_row;

extern u32 game_board_dimension;
extern u32 game_board_cols;
extern u32 game_board_rows;

#pragma endregion

#pragma region game_snake

typedef struct game_snake_segment_t {
  vec2 board_col_row;
  vec2 direction_col_row;
  vec4 color;
} game_snake_segment;

array_list* game_snake_init();
void game_snake_grow(array_list* snake);
void game_snake_move(array_list* snake, vec2 direction);
void game_snake_draw(array_list* snake);

#pragma endregion

#pragma region game

void game_init();
void game_loop();
void game_cleanup();

#pragma endregion

#endif // __SNEK_GAME_H__