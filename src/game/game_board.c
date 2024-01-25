#include "../game.h"
#include "game_internal.h"

void game_board_draw_cell(vec2 board_cell_coordinate, vec4 color)
{
  render_quad(
    (vec2) {board_cell_coordinate[0] * game_board_cell_dimension, board_cell_coordinate[1] * game_board_cell_dimension},
    (vec2) {game_board_cell_dimension, game_board_cell_dimension},
    color
  );
}
