/* Name: Thomas "Adam" Pippert
   Due Date: 2-February-2016
   File: unittest2.c
   Purpose: Unit test for gainCard function
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
  int result;                  /* Return result of test */


  printf("*** TESTING FUNCTION: gainCard ***\n\n");
  
  for(i = 0; i < numTests; i++)
    {
      /* Set hand basics for each game so the function can be called */
    pos = -1;
    p = 0;
    p2 = 1;


    /* Test 1: Testing to see if pile is empty */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    testState.supplyCount[feast] = 0;
    /* Give feast to testState, discard for current player */
    result = gainCard(feast, &testState, 0, p);
    printf("Test 1: Cannot gain a card which is out of stock: \n");
    if(result == -1)
      {
        printf("Passed. Expected %d, Returned %d\n", -1, result);
      }
    else
      {
        printf("FAILED. Expected %d, Returned %d\n", -1, result);
      }

    /* Test 2: Checking if the requested card is not in game */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = gainCard(sea_hag, &testState, 0, p); /* Not in this game */
    printf("\nTest 2: Cannot gain a card which is not in current game: \n");
    if(result == -1)
      {
        printf("Passed. Expected %d, Returned %d\n", -1, result);
      }
    else
      {
        printf("FAILED. Expected %d, Returned %d\n", -1, result);
      }

    /* Test 3a: Testing if card was added to the deck */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = gainCard(feast, &testState, 1, p); /* give feast to testState */
    printf("\nTest 3a: Card is added to players deck: \n");
    if(testState.deckCount[p] == initState.deckCount[p] +1)
      {
        printf("Passed. Expected %d, Returned %d\n", initState.deckCount[p] +1, testState.deckCount[p]);
      }
    else
      { /* ERROR: Card not added */
        printf("FAILED. Expected %d, Returned %d\n", initState.deckCount[p] +1, testState.deckCount[p]);
      }

    /* Test 3b: Make sure it didn't go to the opponent's deck */
    printf("\nTest 3b: Card is not in opponent's deck: \n");
    if(testState.deckCount[p2] != initState.deckCount[p2])
      {
      printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.deckCount[p2], testState.deckCount[p2]);
      }

    /* Test 4b: Make sure it's added to hand */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = gainCard(feast, &testState, 2, p);   /* Give feast to testState, discard set for current player */
    printf("\nTest 4a: Card is added to players hand: \n");
    if(testState.handCount[p] == initState.handCount[p] +1)
      {
      printf("Passed. Expected %d, Returned %d\n", initState.handCount[p] +1, testState.handCount[p]);
      }
    else
      {
      printf("FAILED. Expected %d, Returned %d\n", initState.handCount[p] +1, testState.handCount[p]);
      }

    /* Test 4b: Make sure it didn't go to the other user's hand */
    printf("\nTest 4b: Card is not in opponent's hand: \n");
    if(testState.handCount[p2] != initState.handCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.handCount[p2], testState.handCount[p2]);
      }

    /* Test 5: Make sure the card is discarded */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = gainCard(feast, &testState, 0, p);
    printf("\nTest 5: Card is discarded: \n");
    if(testState.discardCount[p] == initState.discardCount[p] +1)
      {
        printf("Passed. Expected %d, Returned %d\n", initState.discardCount[p] +1, testState.discardCount[p]);
      }
    else
      {
      printf("FAILED. Expected %d, Returned %d\n", initState.discardCount[p] +1, testState.discardCount[p]);
      }

    /* Test 5b: Make sure it didn't go to the opponent's deck */
    printf("\nTest 5b: Ensure card didn't go in opponent's deck\n");
    if(testState.discardCount[p2] != initState.discardCount[p2])
      {
        printf("FAILED. Expected other user's deck to remain %d, is now: %d\n", initState.discardCount[p2], testState.discardCount[p2]);
      }


    /* Test 6: Make supply count decreases */
    initializeGame(numPlayers, k, 1000, &initState);
    memcpy(&testState, &initState, sizeof(struct gameState));
    result = gainCard(feast, &testState, 0, p);
    printf("\nTest 6: Supply count is decreased: \n");
    if(testState.supplyCount[feast] == initState.supplyCount[feast] -1)
      {
        printf("Passed. Expected %d, Returned %d\n", initState.supplyCount[feast] -1, testState.supplyCount[feast]);
      }
    else
      {
        printf("FAILED. Expected %d, Returned %d\n", initState.supplyCount[feast] -1, testState.supplyCount[feast]);
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
    if(initState.supplyCount[silver] != testState.supplyCount[silver])
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

    /* ALL TESTS COMPLETE */
    
  }
  return 0;
}
