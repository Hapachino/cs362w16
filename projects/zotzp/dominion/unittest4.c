/* Paul Zotz
 * CS 362 Winter 2016
 * unit test 4 - handCard()
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i,j;
    int seed = 1000;
    int numPlayer = 2;
    int thisCard;
    int expected;
    int currentPlayer;
    int testHand;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    initializeGame(numPlayer, k, seed, &G); // initialize a new game


    printf ("TESTING handCard():\n");
    for (i = 0; i < numPlayer; i++)
    {

        currentPlayer = whoseTurn(&G);
        testHand = G.handCount[currentPlayer];
        for (j = 0; j < testHand; j++) // check that handCard returns correct card value for each card in this player's hand
        {
            expected = G.hand[currentPlayer][j];
            thisCard = handCard(j, &G);
#if (NOISY_TEST == 1)
            printf("Test player %d, handPos %d\n", i, j);
            printf("Result: %d, Expected: %d\n", thisCard, expected);
#endif
            assert(thisCard == expected);
        }
    }

    printf("All tests passed!\n");

    return 0;
}


