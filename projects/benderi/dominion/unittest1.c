/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for numHandCards() function.
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
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    //test player 1
    printf("# Cards in Hand: %d\n", numHandCards(&G));
    drawCard(whoseTurn(&G), &G);
    drawCard(whoseTurn(&G), &G);
    printf("# Cards in Hand: %d\n", numHandCards(&G));

    //test player 2
    endTurn(&G);
    printf("# Cards in Hand: %d\n", numHandCards(&G));
    drawCard(whoseTurn(&G), &G);
    drawCard(whoseTurn(&G), &G);
    drawCard(whoseTurn(&G), &G);
    printf("# Cards in Hand: %d\n", numHandCards(&G));

    return 0;
}
