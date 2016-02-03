/* -----------------------------------------------------------------------
 * playSmithy()
 *
 * The playSmithy() function works as follows:
 *  -draw 3 cards into player's hand
 *  -put smithy into player's played cards pile
 *
 * Things to check:
 *  -player has 3 more cards in hand
 *  -player has 3 less cards in deck
 *  -player has same amount of cards in played cards pile
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void*, const void*);

int testSmithy()
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
    for (i = 0; i < 3; i++)
    {
        expected.hand[player][expected.handCount[player]] = expected.deck[player][expected.deckCount[player]];
        expected.handCount[player]++;
        expected.deckCount[player]--;
    }
    expected.handCount[player] += 3;
    expected.playedCards[expected.playedCardCount] = smithy;
    expected.playedCardCount++;
    
    // Add smithy as last card in hand and play it.
    int handPos = state.handCount[player];
    state.hand[player][handPos] = smithy;
    state.handCount[player]++;
    if (playSmithy(&state, handPos) != 0)
    {
        printf("Failed: playSmithy() failed.\n");
        failed++;
    }

    // Compare hands
    if (state.handCount[player] != expected.handCount[player])
    {
        printf("Failed: hand counts do not match.\n");
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

    // Compare played card piles
    if (state.playedCardCount != expected.playedCardCount)
    {
        printf("Failed: played card counts do not match.\n");
        failed++;
    }
    qsort(state.playedCards, state.playedCardCount, sizeof(int), compare);
    qsort(expected.playedCards, expected.playedCardCount, sizeof(int), compare);
    for (i = 0; i < expected.playedCardCount; i++)
    {
        if (state.playedCards[i] != expected.playedCards[i])
        {
            printf("Failed: played cards do not match.\n");
            failed++;
            break;
        }
    }
    return failed;
}

int main()
{
    printf("--------\nTesting smithy card\n");
    int failed = testSmithy();
    if (failed)
    {
        printf("Smithy card failed %d tests!\n\n", failed);
    }
    else
    {
        printf("Smithy card passed all tests!\n\n");
    }
    return 0;
}
