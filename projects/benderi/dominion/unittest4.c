/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for isGameOver() function.
 * Business Requirements
 *      - game is over when province stack is at 0
 *      - game is over when any 3 supply stacks are at 0
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


    printf("TESTING FOR GAME OVER\n");
    //supply of province > 0, game continues
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G))
        printf("ERROR - game over but should continue.\n");
    else
        printf("SUCCESS - Game continues.\n");

    //supply of province = 0, game over 
    G.supplyCount[province] = 0;
    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (isGameOver(&G))
        printf("SUCCESS - Game over.\n");
    else
        printf("ERROR - game continues but should be over.\n");

    //reset supply count of province
    G.supplyCount[province] = 12;
    for (i = 0; i < 3; i++)
    {
        //set supply pile to 0
        G.supplyCount[i] = 0;
        printf("%d piles now have 0 cards.\n", i + 1);
        //if three supply piles are at 0, game is over
        if (isGameOver(&G) && i == 2)
            printf("SUCCESS - Game over.\n");
        else if (isGameOver(&G) && i < 2)
            printf("ERROR - game over but should continue.\n");
        else
            printf("SUCCESS - Game continues.\n");
    }

    printf("TEST COMPLETE\n");

    return 0;
}
