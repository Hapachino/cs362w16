/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for Village card.
 * Requirements
 *      - player draws 1 card
 *      - player gains 2 actions
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

    printf("TESTING - VILLAGE CARD\n");
    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    //give Village card to first player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("SUCCESS - Village card given to player.\n");
    else
        printf("ERROR - Village card not given.\n");

    //play Village card
    cardEffect(village, 0, 0, 0, &testG, 
            testG.hand[thisPlayer][testG.handCount[thisPlayer]-1], 0);
    
    //test that player gained 1 card
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("SUCCESS - Player gained 1 new card, discarded 1.\n");
    else
        printf("ERROR - Player did not gain/discard correct # of cards.\n");

    //test that player gained 2 actions
    if (G.numActions + 2 == testG.numActions)
        printf("SUCCESS - Player gained 2 actions.\n");
    else
        printf("ERROR - Player did not gain 2 actions.\n");


    printf("TEST COMPLETE\n\n");

    return 0;
}
