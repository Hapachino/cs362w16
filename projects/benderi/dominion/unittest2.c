/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for endTurn() function.
 * Business Requirements
 *      - End current player turn
 *      - Advance to next player
 *      - Do not advance if game is over
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
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    //initialize game state
    outcome = initializeGame(MAX_PLAYERS, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("TESTING - ENDING TURNS\n");
    //multiple tests to verify last player turn loops back to first player
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < MAX_PLAYERS; j++)
        {
            // test that current player is who we expect
            if (whoseTurn(&G) != j)
                printf("ERROR - Current player: %d, Expected player: %d\n",
                        whoseTurn(&G), j);
            else
                printf("SUCCESS - Current player: %d, Expected player: %d\n",
                        whoseTurn(&G), j);
            endTurn(&G);    //end current player turn
        }
    }
    printf("TEST COMPLETE\n");

    return 0;
}
