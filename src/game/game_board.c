#include "../game.h"

u32 game_board_dimension = 40;
u32 game_board_cols = 32; // 32 * 40 = 1280
u32 game_board_rows = 24; // 24 * 40 = 960

void game_board_draw()
{
  for(u32 col = 1; col < game_board_cols; ++col) {
    render_line_segment(
      (vec2){ col * game_board_dimension, 0 },
      (vec2) {col * game_board_dimension, game_window_height},
      (vec4) {1, 1, 1, 1}
    );
  }

  for(u32 row = 1; row < game_board_rows; ++row) {
    render_line_segment(
      (vec2){ 0, row * game_board_dimension },
      (vec2) {game_window_width, row * game_board_dimension},
      (vec4) {1, 1, 1, 1}
    );
  }
}
