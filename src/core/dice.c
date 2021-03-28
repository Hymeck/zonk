#include <time.h>
#include <stdlib.h>

#include "dice.h"

static dices_t* internal_alloc_dices(byte c)
{
    dices_t* d = (dices_t*) malloc(sizeof(dices_t));

    d->arr = (byte*) malloc(c * sizeof(byte));
    d->len = c;

    return d;
}

dices_t* alloc_dices(byte dice_count)
{
    if (!dice_count)
        return NULL;

    return internal_alloc_dices(dice_count);
}

static void internal_randomize_dices(dices_t* d)
{
    srand((size_t) time(NULL));

    for (byte i = 0; i < d->len; i++)
        d->arr[i] = rand() % 6 + 1;
}

void roll_dices(dices_t* dices)
{
    if (!dices)
        return;

    internal_randomize_dices(dices);
}

static void internal_free_dices(dices_t* d)
{
    free(d->arr);
    free(d);
    d = NULL;
}

void free_dices(dices_t* dices)
{
    if (!dices)
        return;

    internal_free_dices(dices);
}
