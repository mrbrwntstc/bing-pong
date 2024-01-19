#include "snek/game.h"

int main()
{
  game_init();
  
  game_run();

  game_cleanup();

  return 0;
}
