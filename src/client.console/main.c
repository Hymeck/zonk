#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "core/state.h"


#define THREE_ONES 1000


void print_game(game_t* game);


struct dices
{
    byte* arr;
    byte len;
};

typedef struct dices dices_t;


typedef union dice_table
{
    byte dices[DICE_COUNT]; // 6 bytes
    uint64_t dices_state; // 8 bytes
} dtable_t; // so size of memory is 8 bytes


void free_dices(dices_t* dices);

void print_dices(dices_t* dices);

void roll_dices(dices_t* dices);

static inline int triple(byte dice_value);

static inline int power(byte dice_value, byte dice_count);

int evaluate_points(dices_t* dices);


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage:\nzonk dice...\n");
        exit(EXIT_FAILURE);
    }

    byte size = argc - 1;
    byte* src = malloc(sizeof(byte) * size);

    for (int i = 0; i < size; i++)
        src[i] = atoi(argv[i + 1]);

    dices_t* dices = malloc(sizeof(dices_t));
    dices->len = size;
    dices->arr = src;

//    game_t game = init_game(4000, 2);
//    print_game(&game);

//        roll_dices(dices);
    print_dices(dices);

    int value = evaluate_points(dices);
//    if (value < 0)
//    {
//        printf("Invalid combinations\n");
//    }
//    else
//    {
//        printf("%d points", value);
//    }

    free_dices(dices);
    return EXIT_SUCCESS;
}


void print_game(game_t* game)
{
    if (!game)
    {
        return;
    }

    printf("SCORE TO WIN: %d\n", game->score_threshold);
    printf("PLAYER COUNT: %d\n", game->player_count);
}


void free_dices(dices_t* dices)
{
    if (dices == NULL)
    {
        return;
    }

    free(dices->arr);

    dices = NULL;
}


void print_dices(dices_t* dices)
{
    if (!dices)
    {
        return;
    }

    // example
    // +---+
    // | 6 |
    // +---+

    byte len = dices->len;

    // upper part
    for (byte i = 0; i < len; i++)
    {
        printf("+---+");
        if (i != len - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }

    // middle part
    for (byte i = 0; i < len; i++)
    {
        printf("| %d |", dices->arr[i]);
        if (i != len - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }

    // lower part
    for (byte i = 0; i < len; i++)
    {
        printf("+---+");
        if (i != len - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
}


void roll_dices(dices_t* dices)
{
    if (!dices)
    {
        return;
    }

    srand((size_t) time(NULL));

    for (byte i = 0; i < dices->len; i++)
    {
        dices->arr[i] = rand() % 6 + 1;
    }
}


/// \param dice_value - [1, 6]
static inline int triple(byte dice_value)
{
    return dice_value == 1 ?
           THREE_ONES :
           100 * dice_value;
}


/// \param dice_value - [1, 6]
/// \param dice_count - [4, 6]
static inline int power(byte dice_value, byte dice_count)
{
    return triple(dice_value) << (dice_count - 3);
}


int evaluate_points(dices_t* dices)
{
    // 1 = 100;
    // 5 = 50;
    // 3 * 1 = 1000;
    // 3 * n = 100 * n, n = {2, 3, 4, 5, 6}; // 3 3 3 = 100 * 3 = 300
    // k * n = (3 * n) << (k - 3), k = {4, 5, 6}, n = {1, 2, 3, 4, 5, 6}; // 3 3 3 3 = 600, 3 3 3 3 3 = 1200, 3 3 3 3 3 3 = 2400
    // 1, 2, 3, 4, 5 = 500;
    // 2, 3, 4, 5, 6 = 750;
    // 1, 2, 3, 4, 5, 6 = 1500;

    dtable_t etable = {0};
    // fill table of each dice entrance
    for (byte i = 0; i < dices->len; i++)
    {
        etable.dices[dices->arr[i] - 1]++;
    }

    // 1103823438081 - 1 2 3 4 5 6
    // in binary 10000000 10000000 10000000 10000000 100000001
    // +---+ +---+ +---+ +---+ +---+ +---+
    // | 1 | | 1 | | 1 | | 1 | | 1 | | 1 |
    // +---+ +---+ +---+ +---+ +---+ +---+

    for (byte i = 0; i < DICE_COUNT; i++)
    {
        printf("%d ", etable.dices[i]);
    }

    printf("\n%lu\n", etable.dices_state);

    if (etable.dices_state == 1103823438081)
    {
        return 1500;
    }

    // todo: other


    return -1;
}
