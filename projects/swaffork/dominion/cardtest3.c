/* -----------------------------------------------------------------------
 * playTribute()
 *
 * The playTribute() function works as follows:
 *  -player gets two coins if either of top two cards of the deck are treasures
 *  -if either of top two cards are victory cards, current player draws two cards
 *  -if either of top two cards are action cards, player gets two more actions in numActions
 *
 * Things to check:
 *  -player gets two coins if a top card is a treasure
 *  -player gets two cards in hand if a top card is a victory card, two cards removed from deck
 *  -player gets two extra actions if a top card is an action card
 *  -each effect happens only once
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

int testTribute()
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

    return failed;
}

int main()
{
    printf("--------\nTesting tribute card\n");
    int failed = testTribute();
    if (failed)
    {
        printf("Tribute card failed %d tests!\n\n", failed);
    }
    else
    {
        printf("Tribute card passed all tests!\n\n");
    }
    return 0;
}
