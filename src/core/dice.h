#ifndef DICE_H
#define DICE_H

#include "shared.h"

struct dices
{
    byte* arr;
    byte len;
};
typedef struct dices dices_t;




dices_t* alloc_dices(byte dice_count);
void roll_dices(dices_t* dices);
void free_dices(dices_t* dices);

#endif
