/* Name: Thomas "Adam" Pippert
   Due Date: 2-February-2016
   File: unittest3.c
   Purpose: Unit test for updateCoins function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main()
{

  int i;                       /* Counter */
  int p, p2;                   /* Indicating which player */
  int pos;                     /* Current position */
  int numPlayers = 2;          /* Players for valid gamestate */
  int numTests = 1;            /* Testing spread */
  struct gameState initState;  /* Original Gamestate */
  struct gameState testState;  /* Gamestate under test */
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, village};
  int amount = 0;              /* updateCoins sets coins to 0 */

  printf("*** TESTING FUNCTION: updateCoins ***\n\n");
  
  for(i = 0; i < numTests; i++)
    {
    
      /* Set hand basics for each game so the function can be called */
    pos = -1;
    p = 0;
    p2 = 1;


    /* Test 1: Copper increases by 1 */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = copper;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 1: Copper increases coins by 1: \n");
    if(testState.coins == amount + 1)
      {
        printf("Passed. Expected %d, Returned %d\n", amount +1, testState.coins);
      }
    else
      {
      printf("FAILED.  Expected %d, Returned %d\n", amount +1, testState.coins);
      }

    /* Test 1b: Make sure opponent not impacted */
    printf("\nTest 1b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == initState.deckCount[p2])
      {
      printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 2: Silver increases coins by 2 */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = silver;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 2: Silver increases coins by 2: \n");
    if(testState.coins == amount +2)
      {
        printf("Passed. Expected %d, Returned %d\n", amount +2, testState.coins);
      }
    else
      {
        printf("FAILED.  Expected %d, Returned %d\n", amount +2, testState.coins);
      }

    /* Test 2b: No impact on opponent */
    printf("\nTest 2b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == initState.deckCount[p2])
      {
        printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
      printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }


    /* Test 3: Gold adds 3 coins */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 3: Gold increases coins by 3: \n");
    if(testState.coins == amount +3)
      {
      printf("Passed. Expected %d, Returned %d\n", amount +3, testState.coins);
      }
    else
      {
      printf("FAILED.  Expected %d, Returned %d\n", amount +3, testState.coins);
      }

    /* Test 3b: No impact to opponent */
    printf("\nTest 3b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == initState.deckCount[p2])
      {
      printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }


    /* Test 4: Bonus */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 1);
    printf("Test 4: Bonus produces incease equivalent to input (coins + 1): \n");
    if(testState.coins == amount +4)   /* bonus + gold */
      {
        printf("Passed. Expected %d, Returned %d\n", amount +4, testState.coins);
      }
    else
      {
      printf("FAILED.  Expected %d, Returned %d\n", amount +4, testState.coins);
      }

    /* Test 4b: No impact on opponent */
    printf("\nTest 4b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == initState.deckCount[p2])
      {
        printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
      printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 5: Bonus correctly calculated */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 3);
    printf("Test 5: Bonus produces increase equivalent to input (coins + 3): \n");
    if(testState.coins == amount +6)
      {
        printf("Passed. Expected %d, Returned %d\n", amount +6, testState.coins);
      }
    else
      {
        printf("FAILED.  Expected %d, Returned %d\n", amount +6, testState.coins);
      }

    /* Test 5b: No impact to opponent */
    printf("\nTest 5b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == initState.deckCount[p2])
      {
      printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }


    /* Test 6: Victory Points */
    printf("\nTest 6: : Test supply counts for points and curses that should not have been distributed: \n ");
    if(initState.supplyCount[estate] != testState.supplyCount[estate])
      {
        printf("FAILED. Estate Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[estate], testState.supplyCount[estate]);
      }
    if(initState.supplyCount[duchy] != testState.supplyCount[duchy])
      {
        printf("FAILED. Duchy Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[duchy], testState.supplyCount[duchy]);
      }
    if(initState.supplyCount[province] != testState.supplyCount[province])
      {
        printf("FAILED. Province Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[province], testState.supplyCount[province]);
      }
    if(initState.supplyCount[curse] != testState.supplyCount[curse])
      {
        printf("FAILED. Province Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[curse], testState.supplyCount[curse]);
      }
    else
      {
      printf("Passed. Supply counts for curses and victory cards are the same\n");
      }

    /* Test 7: Treasure counts */
    printf("\nTest 7: Test supply counts for treasure that should have been distributed: \n");
    if(initState.supplyCount[copper] != testState.supplyCount[copper])
      {
      printf("FAILED. Estate Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[copper], testState.supplyCount[copper]);
      }
    if(initState.supplyCount[silver] != testState.supplyCount[silver])
      {
        printf("FAILED. Duchy Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[silver], testState.supplyCount[silver]);
      }
    if(initState.supplyCount[gold] != testState.supplyCount[gold])
      {
        printf("FAILED. Duchy Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[gold], testState.supplyCount[gold]);
      }
    else
      {
        printf("Passed. Supply counts for treasure cards are the same\n");
      }
    }
  
  return 0;
}
