#include "../game.h"

static const vec4 snake_color_head = {0.0f, 1.0f, 0.0f, 1.0f};
static const vec4 snake_color_body = {1.0f, 1.0f, 1.0f, 1.0f};

void game_snake_init(array_list *snake)
{
  snake = array_list_create(sizeof(game_snake_segment), 1);
  if(!snake)
    ERROR_EXIT("Not enough memory to create snake\n");

  game_snake_segment snake_head = {
    .board_cell_coordinate = {random_u64(0) % game_board_columns, random_u64(0) % game_board_rows},
    .direction = {1.0f, 0.0f},
    .color = {snake_color_head[0], snake_color_head[1], snake_color_head[2], snake_color_head[3]},
  };

  if(!array_list_append(snake, &snake_head)) {
    array_list_free(snake);
    ERROR_EXIT("Not enough memory to append snake segment\n");
  }
}

void game_snake_draw(array_list* snake)
{
  for(usize i = 0; i < array_list_len(snake); i++) {
    game_snake_segment *segment = array_list_get(snake, i);
    game_board_draw_cell(segment->board_cell_coordinate, segment->color);
  }
}
