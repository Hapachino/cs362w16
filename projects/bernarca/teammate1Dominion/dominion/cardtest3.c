//Author: colvinch
//Filename: cardtest3.c
//Card: Village
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Village"

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

    //give card to first player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = village;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("%s card given to player.\n", TESTCARD);
    else
        printf("ERROR - %s card not given.\n", TESTCARD);

    //play card
    cVillage(thisPlayer, &testG, 0);

    //test that player gained 1 card
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("Player gained 1 new card, discarded 1.\n");
    else
        printf("ERROR - Player did not gain/discard correct # of cards.\n");

    //test that player gained 2 actions
    if (G.numActions + 2 == testG.numActions)
        printf("Player gained 2 actions.\n");
    else
        printf("ERROR - Player did not gain 2 actions.\n");

    printf("cardtest3 [%s] is complete \n", TESTCARD);

    return 0;
}
