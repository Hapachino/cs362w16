/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for Smithy card.
 * Requirements
 *      - player draws 3 new cards
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

    printf("TESTING - SMITHY CARD\n");
    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    //give Smithy card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("SUCCESS - Smithy card given to player.\n");
    else
        printf("ERROR - Smithy card not given.\n");

    //play Smithy
    //line below adjusted for testing on teammate1 code
    playSmithy(&testG, 0, thisPlayer);
    //playSmithy(thisPlayer, &testG, 0);
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
        printf("SUCCESS - Player gained 3 new cards, discarded 1.\n");
    else
        printf("ERROR - Player did not gain/discard correct # of cards.\n");

    //test game state to verify same number of Victory cards
    if (G.supplyCount[estate] == testG.supplyCount[estate])
       printf("SUCCESS - Count of estate cards unchanged.\n");
    else
       printf("ERROR - Count of estate cards has changed.\n");
    if (G.supplyCount[duchy] == testG.supplyCount[duchy])
       printf("SUCCESS - Count of duchy cards unchanged.\n");
    else
       printf("ERROR - Count of duchy cards has changed.\n");
    if (G.supplyCount[province] == testG.supplyCount[province])
       printf("SUCCESS - Count of province cards unchanged.\n");
    else
       printf("ERROR - Count of province cards has changed.\n");

    printf("TEST COMPLETE\n\n");

    return 0;
}
