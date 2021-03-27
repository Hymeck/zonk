#include "state.h"


game_t init_game(unsigned short score_threshold, unsigned char player_count)
{
    game_t game =
            {
                    score_threshold,
                    player_count,
            };

    return game;
}

