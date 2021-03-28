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

static int internal_add_dice(dtable_t* t, byte d) { return ++t->dices[d]; }

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

static int different_matches(dtable_t* t)
{
    // 1, 2, 3, 4, 5, 6 = 1500;
    if (t->dices_state == 1103823438081)
        return 1500;

    // todo: check 2 3 4 5 6 = 750
    // todo: check 1 2 3 4 5 = 500

    return 0;
}

static dice_t* alloc_dice_t() { return (dice_t*) malloc(sizeof(dice_t)); }
static dice_t** alloc_dice_t_array(byte size) { return (dice_t**) malloc(size * sizeof(dice_t*)); }

void set_score_finction(int (* get_score)(), byte dice_value, byte times_occurred)
{

}

static dice_t** internal_from_dtable(dtable_t* t)
{
    dice_t** dices = alloc_dice_t_array(DICE_COUNT);

    int dice_t_size = sizeof(dice_t*);
    int id = 0;
    byte it = 0;
    byte times_occurred;
    while (it < DICE_COUNT)
    {
        times_occurred = t->dices[it];
        dices[id]->times_occurred = times_occurred;
        set_score_finction(dices[id]->get_score, it + 1, times_occurred);
        id += dice_t_size;
        ++it;
    }

    return dices;
}

static void internal_free_dice_t(dice_t* d)
{
    free(d);
    d = NULL;
}

static int internal_evaluate_score(dtable_t* t)
{
    // todo: check 1 2 3 4 5 6

    //    int different_matches_value = different_matches(t);
    //    if (different_matches_value)
    //        return different_matches_value;

    // 1 = 100;
    // 5 = 50;
    // 3 * 1 = 1000;
    // 3 * n = 100 * n, n = {2, 3, 4, 5, 6}; // 3 3 3 = 100 * 3 = 300
    // k * n = (100 * n) << (k - 3), k = {4, 5, 6}, n = {1, 2, 3, 4, 5, 6}; // 3 3 3 3 = 600, 3 3 3 3 3 = 1200, 3 3 3 3 3 3 = 2400

    int result = 0;

    dice_t** dices = internal_from_dtable(t);

    // todo: perform calculations

    free(dices);
    return result;
}

int evaluate_score(dtable_t* dtable)
{
    if (!dtable || !dtable->dices_state)
        return 0;

    return internal_evaluate_score(dtable);
}
