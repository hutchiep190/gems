#include "game.h"

#include "test.h"

int
main (int argc, char *argv[])
{
  game_t *game = game_create ();

  game->board = (int**)malloc (sizeof (int*) * 8);
  int i, j;
  for (i = 0; i < 8; ++i)
    {
      game->board[i] = (int*)malloc (sizeof (int) * 8);
      for (j = 0; j < 8; ++j)
        {
          game->board[i][j] = -1;
        }
    }

  game->n_gem_types = 4;

  gem_t *gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = 0;
  gem->y = 0;
  gem->type = 0;
  gem->level = 0;
  game_add_gem (game, gem);
  fail_if (game->n_gems != 1);

  gem = (gem_t*)malloc (sizeof (gem_t));
  gem->x = 24;
  gem->y = 48;
  gem->type = 2;
  gem->level = 3;
  game_add_gem (game, gem);
  fail_if (game->n_gems != 2);

  game_swap_gems (game, 0, 0, 1, 2);
  fail_if (game->board[0][0] != 14);
  fail_if (game->board[1][2] != 0);
  for (i = 0; i < game->n_gems; ++i)
    {
      gem_t *gem = game->gems[i];
      if (gem->x / 24 == 0 && gem->y / 24 == 0)
        {
          fail_if (gem->type != 2 || gem->level != 3);
        }
      if (gem->x / 24 == 1 && gem->y / 24 == 2)
        {
          fail_if (gem->type != 0 || gem->level != 0);
        }
    }

  game_destroy (game);
  return 0;
}
