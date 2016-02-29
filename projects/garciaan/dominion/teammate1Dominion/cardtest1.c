/* -----------------------------------------------------------------------
 * playAdventurer()
 *
 * The playAdventurer() function works as follows:
 *  -discards cards until player draws 2 treasure cards
 *  -discards all cards drawn that were not treasure cards
 *  -adventurer card goes to played deck
 *
 * Things to check:
 *  -player has drawn 2 treasure cards into hand
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int compare(const void* a, const void* b);

int setUp(struct gameState* state)
{
    int player = 0;
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
    
    state->whoseTurn = player;
    return 0;
}

int drawCardHelper(struct gameState* state, int player)
{
    int card = state->deck[player][state->deckCount[player] - 1];
    state->deckCount[player]--;
    state->hand[player][state->handCount[player]] = card;
    state->handCount[player]++;
    return card;
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

// Test with deck of only treasure cards
int testAdventurer1()
{
    printf("Testing adventurer card with only treasure cards in deck\n");
    struct gameState state;
    if (setUp(&state) == -1) return 0;
    int player = state.whoseTurn;

    // Replace player's deck with treasure cards.
    int i;
    for (i = 0; i < state.deckCount[player]; i++)
    {
        int treasure = copper;
        if (i % 3 == 0) treasure = gold;
        else if (i % 2 == 0) treasure = silver;
        state.deck[player][i] = treasure;
    }

    // Make copy of initial state.
    struct gameState expectedState;
    memcpy(&expectedState, &state, sizeof(struct gameState));

    int success = playAdventurer(&state);
    if (success != 0)
    {
        printf("playAdventurer() failed\n");
        return 0;
    }

    // Setup expected state.
    // Add adventurer to played pile.
    expectedState.playedCards[0] = adventurer;
    // Draw top two cards from deck and add them to hand.
    drawCardHelper(&expectedState, player);
    drawCardHelper(&expectedState, player);

    struct StateDiff diff = compareStates(&expectedState, &state);
    int passed = checkDiff(&diff);
    printf("End of test\n\n");
    return passed;
}

// Test with only two treasure cards mixed in.
int testAdventurer2()
{
    printf("Test adventurer card with only two treasure cards mixed in.\n");
    struct gameState state;
    if (setUp(&state) == -1) return 0;
    int player = state.whoseTurn;

    // Replace deck with estates.
    int i;
    for (i = 0; i < state.deckCount[player]; i++)
    {
        state.deck[player][i] = estate;
    }
    // Add two treasure cards
    state.deck[player][0] = copper;
    state.deck[player][5] = copper;

    // Make copy of initial state.
    struct gameState expectedState;
    memcpy(&expectedState, &state, sizeof(struct gameState));

    int success = playAdventurer(&state);
    if (success != 0)
    {
        printf("playAdventurer() failed\n");
        return 0;
    }

    // Setup expected state.
    expectedState.playedCards[0] = adventurer;
    expectedState.hand[player][0] = copper;
    expectedState.hand[player][1] = copper;
    for (i = 0; i < 8; i++)
    {
        expectedState.discard[player][i] = estate;
        expectedState.discardCount[player]++;
    }
    expectedState.deckCount[player] = 0;

    // Compare states
    struct StateDiff diff = compareStates(&expectedState, &state);
    int passed = checkDiff(&diff);
    printf("End of test\n\n");
    return passed;
}

int runAllTests()
{
    int failed = 0;
    failed += 1 - testAdventurer1();
    failed += 1 - testAdventurer2();
    return failed;
}

int main()
{
    int failed = runAllTests();
    if (failed)
    {
        printf("%d tests failed!\n", failed);
    }
    else
    {
        printf("All tests passed!\n");
    }
    return 0;
}
