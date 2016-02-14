/*
 * randomtestadventurer.c
 *
 * Random tester for adventurer card in Dominion.
 * Code based on random testing lecture from CS362 - Winter16
 *
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int setUp(struct gameState* state)
{
    int i;
    int r; 
    int index = -1;
    int player;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};

    // Initialize gameState
    if (initializeGame(numPlayers, cards, seed, state) != 0)
    {
        printf("Error: Default initializeGame() failed.\n");
        return -1;
    }

    // Randomly decide who goes first and randomly set their deck, discard, and hand count
    player = rand() % 2;
    state->whoseTurn = player;
    state->deckCount[player] = floor(Random() * MAX_DECK);
    state->handCount[player] = floor(Random() * MAX_HAND + 1);
    state->discardCount[player] = floor(Random() * MAX_DECK);

    // Since adventurer must draw 2 treasure cards, consider case where there are two treasure cards for interesting test results:
    for (i = 0; i < 2; i++)
    {
        r = floor(Random() * state->deckCount[player];
        if (index == r) continue;
        else index = r;
        state->deck[player][index] = copper;
    }

    return 0;
}

int checkDiff(struct StateDiff* diff)
{
    int passed = 1;
    if (diff->flags[PLAYED_CARDS] == 1)
    {
        printf("Failed: played cards pile do not match.\n");
        passed = 0;
    }
    if (diff->flags[PLAYED_CARD_COUNT] == 1)
    {
        printf("Failed: played cards count do not match.\n");
        passed = 0;
    }
    if (diff->flags[HAND] == 1)
    {
        printf("Failed: hands do not match.\n");
        passed = 0;
    }
    if (diff->flags[HAND_COUNT] == 1)
    {
        printf("Failed: hand counts do not match.\n");
        passed = 0;
    }
    if (diff->flags[DISCARD] == 1)
    {
        printf("Failed: discard piles do not match.\n");
        passed = 0;
    }
    if (diff->flags[DISCARD_COUNT] == 1)
    {
        printf("Failed: dicard counts do not match.\n");
        passed = 0;
    }
    return passed;
}

int testAdventurer()
{
    printf("Beginning random tests for adventurer:\n");

    int i;
    int tcount;
    int handCount;
    int passed = 0;
    int failed = 0;
    int numTests = 1000;

    for (i = 0; i < numTests; i++)
    {
        struct gameState state;
        if (setUp(&state) < 0)
        {
            printf("ERROR: setup failed\n");
            failed = 1;
            continue;
        }
        struct gameState expectedState;
        memcpy(&expectedState, &state, sizeof(struct gameState));

        int success = playAdventurer(&state);
        if (success != 0)
        {
            printf("playAdventurer() failed\n");
            failed = 1;
            continue;
        }

        int player = state.whoseTurn;

        // Setup expected state.
        // Add adventurer to played pile and treasure cards to hand
        expectedState.playedCards[0] = adventurer;

        for (tcount = 0; tcount < 2; tcount++)
        {
            handCount = expectedState.handCount[player];
            expectedState.hand[player][handCount] = copper;
            expectedState.handCount[player]++;
            expectedState.deckCount[player]--;
        }

        struct StateDiff diff = compareStates(&expectedState, &state);
        int passed += checkDiff(&diff);
    }

    printf("End of test. %d out of %d tests passed.\n\n", passed, i);
}

int main()
{
    testAdventurer();
    return 0;
}
