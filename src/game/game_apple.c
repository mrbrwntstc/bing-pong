#include <stdbool.h>

#include "../game.h"

static bool snake_is_in_tile(array_list* snake, game_board_col_row tile)
{
  bool in_tile = false;
  for(usize i = 0; i < snake->len; ++i) {
    game_snake_segment* segment = (game_snake_segment*)array_list_get(snake, i);
    in_tile = (segment->board_col_row[0] == tile.col && segment->board_col_row[1] == tile.row);
    if(in_tile)
      break;
  }

  return in_tile;
}

game_board_col_row game_apple_respawn(array_list* snake)
{
  game_board_col_row new_apple;
  do {
    new_apple.col = rand() % game_board_cols;
    new_apple.row = rand() % game_board_rows;
  } while(snake_is_in_tile(snake, new_apple));

  return new_apple;
}

void game_apple_draw(vec2 pos_apple, vec4 color)
{
  render_quad(
    (vec2){pos_apple[0] * game_board_dimension, pos_apple[1] * game_board_dimension},
    (vec2) {game_board_dimension, game_board_dimension},
    color
  );
}
