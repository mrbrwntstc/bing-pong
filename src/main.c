#include <stdio.h>

#include "game.h"

int main()
{
  game_init();

  game_loop();

  game_cleanup();

  return 0;
}
