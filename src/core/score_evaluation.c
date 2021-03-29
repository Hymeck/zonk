#include "score_evaluation.h"

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

static int internal_calculate(byte dice_value, byte dice_count)
{
    // 1 = 100;
    // 5 = 50;
    // 3 * 1 = 1000;
    // 3 * n = 100 * n, n = {2, 3, 4, 5, 6}; // 3 3 3 = 100 * 3 = 300
    // k * n = (100 * n) << (k - 3), k = {4, 5, 6}, n = {1, 2, 3, 4, 5, 6}; // 3 3 3 3 = 600, 3 3 3 3 3 = 1200, 3 3 3 3 3 3 = 2400

    if (dice_count <= 2)
    {
        if (dice_value == 1)
            return ONE * dice_count;
        if (dice_value == 5)
            return FIVE * dice_count;
        else
            return 0;
    }

    if (dice_count == 3)
        return triple(dice_value);

    return power(dice_value, dice_count);
}

int calculate(byte dice_value, byte dice_count)
{
    // todo: checks?
    return internal_calculate(dice_value, dice_count);
}
