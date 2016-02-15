#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void*, const void*);

int testMine()
{
    int failed = 0;
    int i;
    struct gameState state;
    if (!testHelperSetUpState(&state))
    {
        printf("Failed: could not init state\n");
        failed++;
    }
    int player = state.whoseTurn;

    // Setup expected state
    struct gameState expected;
    memcpy(&expected, &state, sizeof(struct gameState));
    int choice1 = silver;
    int choice2 = gold;
    expected.hand[player][expected.handCount[player] - 1] = choice2;

    int handPos = state.handCount[player];
    state.hand[player][handPos] = mine;
    state.handCount[player]++;

    if (playMine(&state, handPos, choice1, choice2) != 0)
    {
        printf("Failed: playMine() failed\n");
        failed++;
    }

    // Compare states
    if (state.handCount[player] != expected.handCount[player])
    {
        printf("Failed: hand counts do not match\n");
        failed++;
    }
    qsort(state.hand[player], state.handCount[player], sizeof(int), compare);
    qsort(expected.hand[player], expected.handCount[player], sizeof(int), compare);
    for (i = 0; i < expected.handCount[player]; i++)
    {
        if (state.hand[player][i] != expected.hand[player][i])
        {
            printf("Failed: hands do not match.\n");
            failed++;
            break;
        }
    }

    return failed;
}

int main()
{
    printf("--------\nTesting mine card\n");
    int failed = testMine();
    if (failed)
    {
        printf("mine card failed %d tests!\n\n", failed);
    }
    else
    {
        printf("Tribute card passed all tests!\n\n");
    }
    return 0;
}
