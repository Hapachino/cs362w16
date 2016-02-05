/* Name: Thomas "Adam" Pippert
   Due Date: 2-February-2016
   File: unittest1.c
   Purpose: Unit test for isGameOver function
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


  printf("*** TESTING FUNCTION: isGameOver ***\n\n");
  
  for(i = 0; i < numTests; i++)
    {
      /* Set hand basics for each game so the function can be called */
      pos = -1;
      p = 0;
      p2 = 1;


      /* Test 1: Testing to see if the Province pile is empty */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.supplyCount[province] = 0;  
      result = isGameOver(&testState);   
      printf("Test 1: Province is empty, should the be game over?: \n");
      if(result == 1)
        {
          printf("Passed. Expected %d, Returned %d\n", 1, result);
        }
      else
        {
      printf("FAILED. Expected %d, Returned %d\n", 1, result);
        }

      /* Test 2: Testing if game ends when three of the supply piles are at 0 */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.supplyCount[silver] = 0;  
      testState.supplyCount[duchy] = 0;
      testState.supplyCount[estate] = 0;
      result = isGameOver(&testState);
      printf("\nTest 2: Three empty supply decks end the game: \n");
      if(result == 1)
        {
          printf("Passed. Expected %d, Returned %d\n", 1, result);
        }
      else
        {
          printf("FAILED. Expected %d, Returned %d\n", 1, result);
        }

      /* Test 3: Make sure game does not end with only two empty supply decks */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.supplyCount[duchy] = 0;
      testState.supplyCount[estate] = 0;
      result = isGameOver(&testState);
      printf("\nTest 3: Two empty supply decks should not end game: \n");
      if(result == 0)
        {
          printf("Passed. Expected %d, Returned %d\n", 0, result);
        }
      else
        {
          printf("FAILED. Expected %d, Returned %d\n", 0, result);
        }

      /* Test 4: Make sure game does not end with cards still on a pile */
      initializeGame(numPlayers, k, 1000, &initState);
      memcpy(&testState, &initState, sizeof(struct gameState));
      testState.supplyCount[silver] = 1;  
      testState.supplyCount[duchy] = 1;
      testState.supplyCount[estate] = 1;
      result = isGameOver(&testState);
      printf("\nTest 4: Three non-empty supply decks should not end game: \n");
      if(result == 0)
        {
        printf("Passed. Expected %d, Returned %d\n", 0, result);
        }
      else
        {
        printf("FAILED. Expected %d, Returned %d\n", 0, result);
        }

      /* Test 5: Treasure counts should remain the same */
    printf("\nTest 5: Test supply counts for treasure that should have been distributed: \n");
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

    /* ALL TESTS COMPLETE */
    
    }
  return 0;
}
