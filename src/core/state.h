#ifndef STATE_H
#define STATE_H

#include <stdint.h>


#define DICE_COUNT 6

typedef uint8_t byte;
typedef uint16_t ushort;

struct game
{
    ushort score_threshold; // score limit (1 - 65 535)
    byte player_count; // how many players are able to play the one game simultaneously (2 - 255)
};

typedef struct game game_t;

game_t init_game(ushort score_threshold, byte player_count);

#endif
