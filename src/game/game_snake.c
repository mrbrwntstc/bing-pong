#include "../game.h"

static const vec4 snake_head_color = {0.0f, 1.0f, 0.0f, 1.0f};
static const vec4 snake_body_color = {1.0f, 1.0f, 1.0f, 1.0f};

array_list* game_snake_init()
{
  array_list* new_snake = array_list_create(sizeof(game_snake_segment), 1);

  game_snake_segment snake_head = {
    .board_col_row = {0, 0},
    .direction_col_row = {1, 0},
    .color = {snake_head_color[0], snake_head_color[1], snake_head_color[2], snake_head_color[3]},
  };

  if(array_list_append(new_snake, &snake_head) == (usize)-1) {
    free(new_snake);
    ERROR_EXIT("Failed to append snake head\n");
  }

  return new_snake;
}

void game_snake_grow(array_list *snake)
{
  game_snake_segment new_body = {
    .board_col_row = {0, 0},
    .direction_col_row = {0, 0},
    .color = {snake_body_color[0], snake_body_color[1], snake_body_color[2], snake_body_color[3]},
  };

  if(array_list_append(snake, &new_body) == (usize)-1) {
    free(snake);
    ERROR_EXIT("Failed to append snake body\n");
  }
}

void game_snake_move(array_list* snake, vec2 direction)
{
  for(usize i = snake->len - 1; i > 0; --i) {
    game_snake_segment* segment_current = (game_snake_segment*)array_list_get(snake, i);
    game_snake_segment* segment_prev = (game_snake_segment*)array_list_get(snake, i - 1); 

    segment_current->board_col_row[0] = segment_prev->board_col_row[0];
    segment_current->board_col_row[1] = segment_prev->board_col_row[1];
  }

  game_snake_segment* head = (game_snake_segment*)array_list_get(snake, 0);
  head->board_col_row[0] += direction[0];
  if(head->board_col_row[0] >= game_board_cols)
    head->board_col_row[0] = 0;
  if(head->board_col_row[0] < 0)
    head->board_col_row[0] = game_board_cols - 1;
  head->board_col_row[1] += direction[1];
  if(head->board_col_row[1] >= game_board_rows)
    head->board_col_row[1] = 0;
  if(head->board_col_row[1] < 0)
    head->board_col_row[1] = game_board_rows - 1;
}

void game_snake_draw(array_list* snake)
{
  for(usize i = 0; i < snake->len; ++i) {
    game_snake_segment* segment = (game_snake_segment*)array_list_get(snake, i);
    render_quad(
      (vec2) {segment->board_col_row[0] * game_board_dimension, segment->board_col_row[1] * game_board_dimension},
      (vec2) {game_board_dimension, game_board_dimension},
      segment->color
    );
  }
}
