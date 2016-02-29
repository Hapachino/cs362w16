#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int compare(const void*, const void*);

int setUp(struct gameState* state)
{
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

    return 0;
}

void testGreatHall()
{
    printf("Beginning random tests for Great Hall:\n");

    int i;
    int j;
    int passed = 0;
    int numTests = 1000;
    int player;

    for (i = 0; i < numTests; i++)
    {
        struct gameState state;
        if (setUp(&state) < 0)
        {
            printf("ERROR: setup failed\n");
            continue;
        }
        struct gameState expected;
        memcpy(&expected, &state, sizeof(struct gameState));

        // Add great_hall as last card in hand and play it.
        player = state.whoseTurn;
        int handPos = state.handCount[player];
        state.hand[player][handPos] = great_hall;
        state.handCount[player]++;
        if (playGreat_Hall(&state, handPos) != 0)
        {
            printf("Failed: playGreat_Hall() failed.\n");
            continue;
        }

        // Setup expected state.
        expected.hand[player][expected.handCount[player]] = expected.deck[player][expected.deckCount[player]];
        expected.handCount[player]++;
        expected.deckCount[player]--;

        expected.playedCards[expected.playedCardCount] = great_hall;
        expected.playedCardCount++;

        // Compare states
        if (state.handCount[(player + 1) % 2] != expected.handCount[(player + 1) % 2])
        {
            printf("Non-active player's hand changed.\n");
            passed += 0;
            continue;
        }
        else if (state.deckCount[(player + 1) % 2] != expected.deckCount[(player + 1) % 2])
        {
            printf("Non-active player's deck changed.\n");
            passed += 0;
            continue;
        }
        else if (state.discardCount[(player + 1) % 2] != expected.discardCount[(player + 1) % 2])
        {
            printf("Non-active player's discard pile changed.\n");
            passed += 0;
            continue;
        }
        else if (state.handCount[player] != expected.handCount[player])
        {
            // Remove print statement since we intentionally introduced this bug
            // printf("Player's hand count not as expected.\n");
            passed += 0;
            continue;
        }
        else if (state.playedCardCount != expected.playedCardCount)
        {
            printf("Player's played card count not as expected.\n");
            passed += 0;
            continue;
        }
        else if (state.discardCount[player] != expected.discardCount[player])
        {
            printf("Player's discard card count not as expected.\n");
            passed += 0;
            continue;
        }
        else if (state.deckCount[player] != expected.deckCount[player])
        {
            printf("Player's deck card count not as expected.\n");
            passed += 0;
            continue;
        }
        // Compare expected to actual hands
        else
        {
            qsort(state.hand[player], state.handCount[player], sizeof(int), compare);
            qsort(expected.hand[player], expected.handCount[player], sizeof(int), compare);
            for (j = 0; j < expected.handCount[player]; j++)
            {
                if (state.hand[player][j] != expected.hand[player][j])
                {
                    printf("Failed: hands do not match.\n");
                    passed += 0;
                    continue;
                }
            }
        }
        
        passed += 1;
    }

    printf("End of test. %d out of %d tests passed.\n\n", passed, i);

}

int main()
{
    testGreatHall();
    return 0;
}
