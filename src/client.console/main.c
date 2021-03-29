#include <stdio.h>
#include <stdlib.h>

#include "core/zonk.h"
#include "presenter.h"

void print_help();
void print_help_and_exit_failure();

int main(int argc, char* argv[])
{
    if (argc < 2)
        print_help_and_exit_failure();

    byte size = argc - 1;

    dtable_t* dice_state = init_dtable();
    dices_t* dices = alloc_dices(size);
    for (int i = 0; i < size; i++)
    {
        int dice_value = atoi(argv[i + 1]);

        if (add_dice(dice_state, dice_value) > 0)
            dices->arr[i] = dice_value;
    }

    if (is_empty(dice_state))
        print_help_and_exit_failure();

    print_dices(dices);

    int score = evaluate_score(dice_state);
    printf("SCORE: %d\n", score);

    free_dtable(dice_state);
    free_dices(dices);

    return EXIT_SUCCESS;
}

void print_help()
{
    printf("Usage:\nzonk dice...\n\tdice - integer from 1 to 6\n");
}

void print_help_and_exit_failure()
{
    print_help();
    exit(EXIT_FAILURE);
}
