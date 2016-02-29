/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for numHandCards() function.
 * Requirements
 *      - initial hand has 5 cards
 *      - hand count is incremented after draw
 *      - hand count is decremented after discard
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
    int i, j;
    int outcome;
    int seed = 1000;
    int numPlayers = 2;
    int expCardCount;   //expected card count
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    printf("TESTING - numHandCards()\n");
    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    for (i = 0; i < numPlayers; i++)
    {
        printf("Player %d\n", i + 1);
        expCardCount = 5;
        for (j = 0; j < 5; j++)
        {
            if (numHandCards(&G) != expCardCount + j)
                printf("ERROR - Cards in hand: %d, Expected: %d\n",
                        numHandCards(&G), expCardCount + j);
            else
                printf("SUCCESS - Cards in hand: %d, Expected: %d\n",
                        numHandCards(&G), expCardCount + j);
            drawCard(whoseTurn(&G), &G);
        }
        endTurn(&G);
    }

    printf("TESTING - DISCARD CARDS\n");
    for (i = 0; i < numPlayers; i++)
    {
        printf("Player %d\n", i + 1);
        expCardCount = 5;
        for (j = 0; j < 5; j++)
        {
            if (numHandCards(&G) != expCardCount - j)
                printf("ERROR - Cards in hand: %d, Expected: %d\n",
                        numHandCards(&G), expCardCount - j);
            else
                printf("SUCCESS - Cards in hand: %d, Expected: %d\n",
                        numHandCards(&G), expCardCount - j);
            discardCard(0, i, &G, 0);
        }
        endTurn(&G);
    }

    printf("TEST COMPLETE\n\n");

    return 0;
}
