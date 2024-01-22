#include "snek/game.h"

int main()
{
  game_init();
  
  game_loop();

  game_cleanup();

  return 0;
}
