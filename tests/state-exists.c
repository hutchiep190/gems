#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();
  fail_if (game->state != SPLASH_STATE);
  game_destroy (game);
  return 0;
}
