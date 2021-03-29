#ifndef SCORE_H
#define SCORE_H

#include "shared.h"

typedef union dice_table
{
    byte dices[DICE_COUNT]; // 6 bytes
    uint64_t dices_state; // 8 bytes
} dtable_t; // so size of memory is 8 bytes

dtable_t* init_dtable();
int is_empty(dtable_t* table);
void free_dtable(dtable_t* table);

int add_dice(dtable_t* dtable, byte dice_value);
int remove_dice(dtable_t* dtable, byte dice_value);

int evaluate_score(dtable_t* dtable);

#endif
