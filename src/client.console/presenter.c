#include <stdio.h>
#include "presenter.h"

void print_dices(dices_t* dices)
{
    if (!dices)
        return;

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
