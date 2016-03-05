//Author: colvinch
//Filename: cardtest1.c
//Card: Smithy
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Smithy"

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

    printf("Testing - %s card\n", TESTCARD);

    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    //give card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("%s card given to player.\n", TESTCARD);
    else
        printf("ERROR - %s card not given.\n", TESTCARD);

    //play card
    cSmithy(thisPlayer, &testG, 0);
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
        printf("Player gained 3 new cards, discarded 1.\n");
    else
        printf("ERROR - Player did not gain/discard correct number of cards.\n");

    //test game state to verify same number of Victory cards
    if (G.supplyCount[estate] == testG.supplyCount[estate])
       printf("Count of estate cards unchanged.\n");
    else
       printf("ERROR - Count of estate cards has changed.\n");
    if (G.supplyCount[duchy] == testG.supplyCount[duchy])
       printf("Count of duchy cards unchanged.\n");
    else
       printf("ERROR - Count of duchy cards has changed.\n");
    if (G.supplyCount[province] == testG.supplyCount[province])
       printf("Count of province cards unchanged.\n");
    else
       printf("ERROR - Count of province cards has changed.\n");

    printf("cardtest1 [%s] is complete \n", TESTCARD);

    return 0;
}

