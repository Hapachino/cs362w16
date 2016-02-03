/* Name: Thomas "Adam" Pippert
   Due Date: 2-February-2016
   File: unittest4.c
   Purpose: Unit test for discardCard function
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

  int i, j;                       /* Counter */
  int p, p2;                   /* Indicating which player */
  int pos;                     /* Current position */
  int numPlayers = 2;          /* Players for valid gamestate */
  int numTests = 1;            /* Testing spread */
  struct gameState initState;  /* Original Gamestate */
  struct gameState testState;  /* Gamestate under test */
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, village};
  int result;                  /* Return result of test */

  
  printf("*** TESTING FUNCTION: discardCard ***\n\n");
  
  for(i = 0; i < numTests; i++)
    {
    
      /* Set hand basics for each game so the function can be called */
      pos = -1;
      p = 0;
      p2 = 1;


      /* Test 1: Card is added if not trashed */
      initializeGame(numPlayers, k, 1000, &initState);
      initState.hand[p][0] = steward;
      initState.hand[p][1] = estate;
      initState.hand[p][2] = duchy;
      initState.hand[p][3] = province;
      initState.hand[p][4] = great_hall;
      memcpy(&testState, &initState, sizeof(struct gameState));
      result = discardCard(province, p, &testState, 0);  /* Trash flag set to false */
      printf("\nTest 1: Card added to played pile if w/trash flag 0: \n");
      if(testState.playedCardCount == initState.playedCardCount + 1)
        {
          printf("Passed. Expected %d, Returned %d\n", initState.playedCardCount + 1, testState.playedCardCount);
        }
      else
        {
          printf("FAILED. Expected %d, Returned %d\n", initState.playedCardCount + 1, testState.playedCardCount);
        }

      /*Test 1b: Opponent's hand not impacted */   
    printf("Test 1b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's hand to remain %d is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
   
        /* Test 4c, Opponent's deck not impacted */
    printf("Test 1c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 2: Make sure it's added if not trashed */
    initializeGame(numPlayers, k, 1000, &initState);
    initState.hand[p][0] = steward;
    initState.hand[p][1] = estate;
    initState.hand[p][2] = duchy;
    initState.hand[p][3] = province;
    initState.hand[p][4] = great_hall;
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 1);  /* Trash flag set to false */
    printf("\nTest 2: Card not added to played pile if trash flag set: \n");
      if(testState.playedCardCount == initState.playedCardCount)
        {
          printf("Passed. Expected %d, Returned %d\n", initState.playedCardCount, testState.playedCardCount);
        }
      else
        {
          printf("FAILED. Expected %d, Returned %d\n", initState.playedCardCount, testState.playedCardCount);
        }
      /* Test 2b: Opponent's hand not impacted */
    printf("Test 2b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
   
    /* Test 2c: Opponent's deck not impacted */
    printf("Test 2c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
    else
       printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);


    /* Test 3a: Making sure it's removed from hand */
    initializeGame(numPlayers, k, 1000, &initState);
    initState.hand[p][0] = steward;
    initState.hand[p][1] = estate;
    initState.hand[p][2] = duchy;
    initState.hand[p][3] = province;
    initState.hand[p][4] = great_hall;
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 0); 
    int gone = 0; 
    printf("\nTest 3a: Card is removed from hand when discarded: \n");
    for(j = 0; j < testState.handCount[p]; j++)
      {
        if(testState.hand[p][j] == province)
          {
            gone = 1;
          }
      }
    if(gone != 1)
      {
        printf("Passed. Card not found in hand.\n");
      }
    else
      {
      printf("Failed. Card found in hand.\n");
      }

    /* Test 3b: Make sure it didn't go to the other user's hand */  
    printf("Test 3b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
   
    /* Test 3c: Make sure it didn't go to the other user's deck */
    printf("Test 3c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
       printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 4a: Making sure it's removed from hand when trashed */
    initializeGame(numPlayers, k, 1000, &initState);
    initState.hand[p][0] = steward;
    initState.hand[p][1] = estate;
    initState.hand[p][2] = duchy;
    initState.hand[p][3] = province;
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 1);   /* Gain feast in testState, discard set for current player */
    printf("\nTest 4a: Card is removed from hand when trashed: \n");
    if(testState.handCount[p] == initState.handCount[p] -1)
      {
        printf("Passed. Expected %d, Returned %d\n", initState.handCount[p] -1, testState.handCount[p]);
      }
    else
      {
        printf("FAILED. Expected %d, Returned %d\n", initState.handCount[p] -1, testState.handCount[p]);
      }
    
    /* Test 4b: No impact to opponent's hand */
    printf("Test 4b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
      printf("FAILED. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      {
      printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
   
    /* Test 4c: No impact to opponent's deck */
    printf("Test 4c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
       printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 5a: Check if discard reduces to 0 */
    initializeGame(numPlayers, k, 1000, &initState);
    initState.hand[p][0] = province;
    initState.handCount[p] = 1;
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.handCount[p] = 1;
    result = discardCard(province, p, &testState, 0); 
    printf("\nTest 5: One card in hand, will reduce to 0: \n");
    if(testState.handCount[p] == initState.handCount[p] -1)
      {
        printf("Passed. Expected %d, Returned %d\n", initState.handCount[p] -1, testState.handCount[p]);
      }
    else
      {
        printf("FAILED. Expected %d, Returned %d\n", initState.handCount[p] -1, testState.handCount[p]);
      }
 
    /* Test 5b: No impact to opponent's hand */
    printf("Test 5b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    
   
    /* Text 5c: No impact to opponent's deck */
    printf("Test 4c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }


    /* Test 6a: Last card set, if an option */
    initializeGame(numPlayers, k, 1000, &initState);
    initState.hand[p][0] = steward;
    initState.hand[p][1] = estate;
    initState.hand[p][2] = duchy;
    initState.hand[p][3] = province;
    initState.hand[p][4] = great_hall;
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = discardCard(province, p, &testState, 0);
    printf("\nTest 6a: Makes sure if more cards available, last card set: \n");
    if( testState.hand[p][testState.handCount[p]] == -1) 
      {
        printf("Passed. Expected %d, Returned %d\n", -1, testState.hand[p][testState.handCount[p]]);
      }
    else
      {
      printf("FAILED. Expected %d, Returned %d\n", -1, testState.hand[p][testState.handCount[p]]);
      }
  
    /* Test 6b: No impact to opponent's hand */
    printf("Test 6b: Other player didn't gain card in hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's hand to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }
   
    /* Test 6c: No impact to opponent's deck */
    printf("Test 6c: Other player didn't gain card in deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }
    else
      {
        printf("Passed. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

   /* Test 7: Victory Points */
    printf("\nTest 7: Ensure Victory Points do not change: \n ");
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
    
      /* Test 8: Treasure counts should remain the same */
    printf("\nTest 8: Test supply counts for treasure that should have been distributed: \n");
    if(initState.supplyCount[copper] != testState.supplyCount[copper])
      {
        printf("FAILED. Copper Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[copper], testState.supplyCount[copper]);
      }
    if(1 != testState.supplyCount[silver])
      {
      printf("FAILED. Silver Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[silver], testState.supplyCount[silver]);
      }
    if(initState.supplyCount[gold] != testState.supplyCount[gold])
      {
        printf("FAILED. Gold Count Mismatch. Expected: %d, Received: %d\n", initState.supplyCount[gold], testState.supplyCount[gold]);
      }
    else
      {
      printf("Passed. Supply counts for treasure cards are the same\n");
      }

  }
  return 0;
}
