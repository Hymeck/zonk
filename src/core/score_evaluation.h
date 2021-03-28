#ifndef SCORE_EVALUATION_H
#define SCORE_EVALUATION_H

#include "shared.h"

#define ONE 100
#define FIVE 50
#define THREE_ONES 1000

int triple(byte dice_value);
int power(byte dice_value, byte dice_count);
int calculate(byte dice_value, byte dice_count);

#endif
