/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for endTurn() function.
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

    /*
    printf("----------Shuffling Deck------------\n");
    for (i = 0; i < G.deckCount[thisPlayer]; i++)
    {
        printf("%d ", G.deck[thisPlayer][i]);
    }
    printf("\n");
    printf("Player 1 - Deck Count: %d\n", G.deckCount[thisPlayer]);

    shuffle(thisPlayer, &testG);
    printf("Player 1 - Shuffled Count: %d\n", testG.deckCount[thisPlayer]); 

    for (i = 0; i < testG.deckCount[thisPlayer]; i++)
    {
        printf("%d ", testG.deck[thisPlayer][i]);
    }
    printf("\n");
    */

    return 0;
}
