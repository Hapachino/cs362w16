//Author: colvinch
//Filename: cardtest4.c
//Card: Council Room
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Feast"

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
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = council_room;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
        printf("%s card given to player.\n", TESTCARD);
    else
        printf("ERROR - %d card not given.\n", TESTCARD);

    //play card, +4 cards
    cCouncil_Room(thisPlayer, &testG, 0);
    if (G.handCount[thisPlayer] + 4 == testG.handCount[thisPlayer])
        printf("Player 1 drew 4 new cards, discarded 1.\n");
    else
        printf("ERROR - Player 1 did not draw/discard correct # of cards.\n");

    //check for +1 buy to first player
    if (G.numBuys + 1 == testG.numBuys)
        printf("Player 1 gained +1 buy.\n");
    else
        printf("ERROR - Player 1 did not get +1 buy.\n");

    //check other players to verify +1 card
    for (i = 1; i < numPlayers; i++)
    {
        if (G.handCount[i] + 1 == testG.handCount[i])
            printf("Player %d drew 1 card.\n", (i + 1));
        else
            printf("ERROR - Player %d did not draw 1 card.\n", (i + 1));
    }

    printf("cardtest4 [%s] is complete \n", TESTCARD);

    return 0;
}
