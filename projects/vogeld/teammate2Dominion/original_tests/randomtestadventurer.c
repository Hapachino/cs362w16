/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/14/2016
 * Description: Random test for Adventurer card.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"

#define NUM_TESTS 10000

void randomTestAdventurer(int *success, int *failure);

int main() 
{
    int i;
    int success = 0, failure = 0;

    srand(time(NULL));

    // run test NUM_TESTS times, track number of success and failures
    for (i = 0; i < NUM_TESTS; i++)
    {
        randomTestAdventurer(&success, &failure);
    }
    printf("Total tests: %d\n", NUM_TESTS);
    printf("Successful tests: %d\n", success);
    printf("Failed tests: %d\n", failure);

    return 0;
}

void randomTestAdventurer(int *success, int *failure)
{
    int i, j;
    int outcome;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int cardDrawn1, cardDrawn2;
    int treasureCnt1 = 0, treasureCnt2 = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    // create random number for seed and number of players
    seed = rand() % 1000 + 1;
    // allow for players between 1 and 5 to catch corner cases
    numPlayers = rand() % 5 + 1;
    // causes 'stack smashing detected' error?
    //thisPlayer = rand() % numPlayers;

    printf("TESTING: seed = %d, numPlayers = %d, thisPlayer = %d\n", 
                seed, numPlayers, thisPlayer);

    //initialize game state
    outcome = initializeGame(numPlayers, k, seed, &G);
    if (outcome == -1)
    {
        printf("ERROR - Game initialization failed.\n");
        (*failure)++;
        return;
    }
    memcpy(&testG, &G, sizeof(struct gameState));

    //give Adventurer card to player
    testG.hand[thisPlayer][testG.handCount[thisPlayer]] = adventurer;
    testG.handCount[thisPlayer]++;
    if (G.handCount[thisPlayer] + 1 == testG.handCount[thisPlayer])
    {
        //printf("SUCCESS - Adventurer card given to player.\n");
    }
    else
    {
        printf("ERROR - Adventurer card not given.\n");
        (*failure)++;
        return;
    }

    //play Adventurer card
    playAdventurer(thisPlayer, &testG);

    //verify that at least 2 new treasure cards were added to hand
    for (i = 0; i < testG.handCount[thisPlayer]; i++) 
    {
       cardDrawn1 = testG.hand[thisPlayer][i];
       if (cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold)
          treasureCnt1++;
    }
    for (i = 0; i < G.handCount[thisPlayer]; i++) 
    {
       cardDrawn2 = G.hand[thisPlayer][i];
       if (cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold)
          treasureCnt2++;
    }
    if ((treasureCnt1 - treasureCnt2) > 0 || (treasureCnt1 - treasureCnt2) < 3 )
    {
       //printf("SUCCESS - %d additional treasure cards drawn.\n", 
       //           (treasureCnt1 - treasureCnt2));
    }
    else
    {
       printf("ERROR - Less than 1 or more than 3 treasure cards drawn.\n");
       (*failure)++;
       return;
    }


    //verify more cards in test state hand than original hand
    if (G.handCount[thisPlayer] < testG.handCount[thisPlayer])
    {
       //printf("SUCCESS - Additional cards added to test hand.\n");
    }
    else
    {
       printf("ERROR - No additional cards added to test hand.\n");
        (*failure)++;
        return;
    }

    printf("TEST COMPLETE - PASSED SUCCESSFULLY\n\n");
    (*success)++;
    return;
}
