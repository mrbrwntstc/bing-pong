#ifndef __SNEK_GAME_H__
#define __SNEK_GAME_H__

#include <time.h>
#include <stdlib.h>

#include "engine.h"

#pragma region game_board

typedef struct game_board_col_row_t {
  u32 col;
  u32 row;
} game_board_col_row;

extern u32 game_board_dimension;
extern u32 game_board_cols;
extern u32 game_board_rows;

void game_board_draw();

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
game_board_col_row game_snake_peek(array_list* snake, vec2 direction);
void game_snake_draw(array_list* snake);

#pragma endregion

#pragma region game_apple

game_board_col_row game_apple_respawn(array_list* snake);
void game_apple_draw(vec2 pos_apple, vec4 color);

#pragma endregion

#pragma region game

void game_init();
void game_loop();
void game_cleanup();

#pragma endregion

#endif // __SNEK_GAME_H__