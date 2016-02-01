/*This tests the village card*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testVillage(struct gameState *, int); //function declaration

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

   result = testVillage(&G, handPos);

   if(result == 0)
      printf("All tests passed!\n");
   else
      printf("Village did not pass test!\n");

   return 0;
}

int testVillage(struct gameState *prestate, int handPos)
{
   int result, preVillageCards, preVillageActions;
   bool correctNumCards;
   int currentPlayer = whoseTurn(prestate);
   
   preVillageCards = prestate->handCount[currentPlayer]; //hand count before playing Village
   printf("Number of cards in hand before playing Village: %d\n", preVillageCards);

   preVillageActions = prestate->numActions; //number of actions before playing Village
   printf("Number of actions before playing Village: %d\n", preVillageActions);

   result = cardEffect(village, 0, 0, 0, prestate, handPos, 0);
   printf("\nActual number of cards in hand after playing Village: %d\n", prestate->handCount[currentPlayer]);
   printf("Expected number of cards in hand (Village is discarded): %d\n", preVillageCards);

   printf("Actual number of actions after playing Village: %d\n", prestate->numActions);
   printf("Expected number of actions after playing Village: %d\n", preVillageActions + 1);

   if(preVillageCards == prestate->handCount[currentPlayer]) //Village worked correctly, should have same hand count
      correctNumCards = 0;
   else
      correctNumCards = 1;

   if((preVillageActions + 1 == prestate->numActions) && (correctNumCards == 0)) 
      return 0;
     
   return 1; 
}

