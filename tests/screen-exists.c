#include <stdlib.h>

#include "game.h"

#include "test.h"

int
main ()
{
  game_t *game = game_create ();
  fail_if (game->screen == NULL);
  fail_if (game->screen->w != 320);
  fail_if (game->screen->h != 240);
  game_destroy (game);
  return 0;
}
