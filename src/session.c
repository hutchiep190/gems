#include <stdlib.h>

#include "game.h"

void
session_start (game_t *game)
{
  srand (time (NULL));
  game->state = SESSION_STATE;
  game->n_rows = 8;
  game->n_cols = 8;
  game->n_gem_types = 4;
  game->board = (int**)malloc (sizeof (int*) * game->n_cols);
  int i;
  for (i = 0; i < game->n_cols; ++i)
    {
      game->board[i] = (int*)malloc (sizeof (int) * game->n_rows);
    }
  int match_list[2];
  int j;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          match_list[0] = match_list[1] = -1;
          if (j >= 2 && game->board[j-2][i] == game->board[j-1][i])
            {
              match_list[0] = game->board[j-2][i];
            }
          if (i >= 2 && game->board[j][i-2] == game->board[j][i-1])
            {
              match_list[1] = game->board[j][i-2];
            }
          game->board[j][i] = rand () % game->n_gem_types;
          while (game->board[j][i] == match_list[0]
                 || game->board[j][i] == match_list[1])
            {
              ++(game->board[j][i]);
            }
        }
    }
}

void
session_loop (game_t *game)
{
  int i;
  int j;
  int k;
  int l;
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 3
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2]
              && game->board[j][i] == game->board[j][i-3])
            {
              game->board[j][i] = game->board[j][i] + game->n_gem_types;
              for (k = i - 1; k > 2; --k)
                {
                  game->board[j][k] = game->board[j][k-3];
                }
              game->board[j][0] = rand () % game->n_gem_types;
              game->board[j][1] = rand () % game->n_gem_types;
              game->board[j][2] = rand () % game->n_gem_types;
            }
        }
    }
  for (i = 0; i < game->n_rows; ++i)
    {
      for (j = 0; j < game->n_cols; ++j)
        {
          if (i >= 2
              && game->board[j][i] == game->board[j][i-1]
              && game->board[j][i] == game->board[j][i-2])
            {
              for (k = i; k > 2; --k)
                {
                  game->board[j][k] = game->board[j][k-3];
                }
              game->board[j][0] = rand () % game->n_gem_types;
              game->board[j][1] = rand () % game->n_gem_types;
              game->board[j][2] = rand () % game->n_gem_types;
            }
          else if (j < game->n_cols - 2
              && game->board[j][i] == game->board[j+1][i]
              && game->board[j][i] == game->board[j+2][i])
            {
              for (l = j; l < j + 3; ++l)
                {
                  for (k = i; k > 0; --k)
                    {
                      game->board[l][k] = game->board[l][k-1];
                    }
                }
              game->board[j][0] = rand () % game->n_gem_types;
              game->board[j+1][0] = rand () % game->n_gem_types;
              game->board[j+2][0] = rand () % game->n_gem_types;
            }
        }
    }
}