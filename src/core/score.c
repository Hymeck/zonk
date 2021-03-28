#include <malloc.h>

#include "score.h"
#include "score_evaluation.h"

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

static int internal_evaluate_score(dtable_t* t)
{
    int different_matches_value = different_matches(t);
    if (different_matches_value)
        return different_matches_value;

    int result = 0, tmp_score;
    for (byte i = 0; i < DICE_COUNT; i++)
    {
        byte times_occurred = t->dices[i];
        if (!times_occurred)
            continue;

        tmp_score = calculate(i + 1, times_occurred);
        if (!tmp_score)
            return tmp_score;

        result += tmp_score;
    }

    return result;
}

int evaluate_score(dtable_t* dtable)
{
    if (!dtable || !dtable->dices_state)
        return 0;

    return internal_evaluate_score(dtable);
}
