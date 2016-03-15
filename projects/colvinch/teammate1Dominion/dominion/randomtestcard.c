//Author: colvinch
//Filename: randomtestcard.c

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TESTS 10000
#define RANDOMTEST "Smithy"

void randomTestSmithy(int *success, int *failure);

int main()
{
    int i;
    int success = 0, failure = 0;

    srand(time(NULL));

    // run test NUM_TESTS times, track number of success and failures
    for (i = 0; i < NUM_TESTS; i++)
    {
        randomTestSmithy(&success, &failure);
    }
    printf("Total tests: %d\n", NUM_TESTS);
    printf("Successful tests: %d\n", success);
    printf("Failed tests: %d\n", failure);

    return 0;
}

void randomTestSmithy(int *success, int *failure)
{
    int outcome;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    // create random number for seed and number of players
    seed = rand() % 1000 + 1;
    // allow for players between 1 and 5 to catch corner cases
    numPlayers = rand() % 5 + 1;

    printf("Testing - seed = %d, numPlayers = %d\n", seed, numPlayers);
    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
    {
        printf("ERROR - Game initialization failed.\n");
        (*failure)++;
        return;
    }
    memcpy(&testG, &G, sizeof(struct gameState));

    //give card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = smithy;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
    {
        //printf("%s given to player.\n", RANDOMTEST);
    }
    else
    {
        printf("ERROR - %s card not given.\n", RANDOMTEST);
        (*failure)++;
        return;
    }

    //play card
    cSmithy(thisPlayer, &testG, 0);
    if (G.handCount[thisPlayer] + 3 == testG.handCount[thisPlayer])
    {
        //printf(" Player gained 3 new cards, discarded 1.\n");
    }
    else
    {
        printf("ERROR - Player did not gain/discard correct # of cards.\n");
        (*failure)++;
        return;
    }

    //test game state to verify same number of Victory cards
    if (G.supplyCount[estate] == testG.supplyCount[estate])
    {
       //printf("Count of estate cards unchanged.\n");
    }
    else
    {
       printf("ERROR - Count of estate cards has changed.\n");
       (*failure)++;
       return;
    }
    if (G.supplyCount[duchy] == testG.supplyCount[duchy])
    {
       //printf("Count of duchy cards unchanged.\n");
    }
    else
    {
       printf("ERROR - Count of duchy cards has changed.\n");
       (*failure)++;
       return;
    }
    if (G.supplyCount[province] == testG.supplyCount[province])
    {
       //printf("Count of province cards unchanged.\n");
    }
    else
    {
       printf("ERROR - Count of province cards has changed.\n");
       (*failure)++;
       return;
    }

    printf("randomtestcard test has passed successfully\n\n");

    (*success)++;
    return;
}