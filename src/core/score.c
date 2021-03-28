#include <malloc.h>

#include "score.h"

dtable_t* init_dtable()
{
    dtable_t* dtable = (dtable_t*) malloc(sizeof(dtable_t));
    dtable->dices_state = 0;
    return dtable;
}

static void internal_free_dtable(dtable_t* table)
{
    free(table);
    table = NULL;
}

void free_dtable(dtable_t* table)
{
    if (!table)
        return;

    internal_free_dtable(table);
}

static int internal_add_dice(dtable_t* t, byte d)
{
    return ++t->dices[d];
}

int add_dice(dtable_t* dtable, byte dice_value)
{
    if (!dtable || dice_value < 1 || dice_value > 6)
        return -1;

    return internal_add_dice(dtable, dice_value - 1);
}

static int internal_remove_dice(dtable_t* t, byte d)
{
    if (t->dices[d] == 0)
        return 0;

    return --t->dices[d];
}

int remove_dice(dtable_t* dtable, byte dice_value)
{
    if (!dtable || dice_value < 1 || dice_value > 6)
        return -1;

    return internal_remove_dice(dtable, dice_value - 1);
}

static int internal_evaluate_score(dtable_t* t)
{
    // todo: check 1 2 3 4 5 6
    // todo: check 2 3 4 5 6
    // todo: check 1 2 3 4 5
    // 1, 2, 3, 4, 5 = 500;
    // 2, 3, 4, 5, 6 = 750;
    // 1, 2, 3, 4, 5, 6 = 1500;

    if (t->dices_state == 1103823438081)
        return 1500;

    // 1 = 100;
    // 5 = 50;
    // 3 * 1 = 1000;
    // 3 * n = 100 * n, n = {2, 3, 4, 5, 6}; // 3 3 3 = 100 * 3 = 300
    // k * n = (3 * n) << (k - 3), k = {4, 5, 6}, n = {1, 2, 3, 4, 5, 6}; // 3 3 3 3 = 600, 3 3 3 3 3 = 1200, 3 3 3 3 3 3 = 2400




    return 0;
}

int evaluate_score(dtable_t* dtable)
{
    if (!dtable || !dtable->dices_state)
        return 0;

    return internal_evaluate_score(dtable);
}
