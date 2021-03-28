#include <stdio.h>
#include <stdlib.h>

#include "core/zonk.h"
#include "presenter.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Usage:\nzonk dice...\n\tdice - integer from 1 to 6\n");
        exit(EXIT_FAILURE);
    }
    byte size = argc - 1;

    dices_t* dices = alloc_dices(size);
    dtable_t* dice_state = init_dtable();
    for (int i = 0; i < size; i++)
    {
        int dice_value = atoi(argv[i + 1]);
        dices->arr[i] = dice_value;
        add_dice(dice_state, dice_value);
    }

    print_dices(dices);

    int score = evaluate_score(dice_state);
    printf("SCORE: %d\n", score);

    free_dtable(dice_state);
    free_dices(dices);

    return EXIT_SUCCESS;
}
