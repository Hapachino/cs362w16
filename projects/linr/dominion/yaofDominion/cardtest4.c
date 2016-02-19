/*
*Author: Robyn Lin
*This tests the Great Hall card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testGH(struct gameState *, int); //function declaration

int main() {
   int seed = 1000;
   int numPlayer = 3;
   int r, result;
   int handPos = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

   struct gameState G;

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

   result = testGH(&G, handPos);

   if(result == 0)
      printf("All tests passed!\n");
   else
      printf("Great Hall did not pass test!\n");

   return 0;
}

int testGH(struct gameState *prestate, int handPos)
{
   int result, preGHcards, preGHActions;
   bool correctNumCards;
   int currentPlayer = whoseTurn(prestate);
   
   preGHcards = prestate->handCount[currentPlayer]; //hand count before playing Great Hall
   printf("Number of cards in hand before playing Great Hall: %d\n", preGHcards);

   preGHActions = prestate->numActions;
   printf("Number of actions before playing Great Hall: %d\n", preGHActions);

   result = cardEffect(great_hall, 0, 0, 0, prestate, handPos, 0);
   printf("\nActual number of cards in hand after playing Great Hall: %d\n", prestate->handCount[currentPlayer]);
   printf("Expected number of cards in hand (Great Hall is discarded): %d\n", preGHcards);

   printf("Actual number of actions after playing Great Hall: %d\n", prestate->numActions);
   printf("Expected number of actions after playing Great Hall: %d\n", preGHActions);

   if(preGHcards == prestate->handCount[currentPlayer]) //Great Hall worked correctly, should have same hand count
      correctNumCards = 0;
   else
      correctNumCards = 1;

   if((preGHActions == prestate->numActions) && (correctNumCards == 0))  //GH worked correctly
      return 0;
     
   return 1; 
}

