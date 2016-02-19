/*
*Author: Robyn Lin
*This tests the smithy card
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

int testSmithy(struct gameState *, int); //function declaration

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

   result = testSmithy(&G, handPos);

   if(result == 1)
      printf("Smithy did not pass test!\n");

   else
      printf("All tests passed!\n");

   return 0;
}

int testSmithy(struct gameState *prestate, int handPos)
{
   int result, preSmithy;
   int currentPlayer = whoseTurn(prestate);
   
   preSmithy = prestate->handCount[currentPlayer]; //hand count before playing Smithy
   printf("Number of cards in hand before playing Smithy: %d\n", preSmithy);

   result = cardEffect(smithy, 0, 0, 0, prestate, handPos, 0);
   printf("\nActual number of cards in hand after playing Smithy: %d\n", prestate->handCount[currentPlayer]);
   printf("Expected number of cards in hand (Smithy is discarded): %d\n", preSmithy + 2);

   if((preSmithy + 2) == prestate->handCount[currentPlayer]) //smithy worked correctly, should have net +2 cards
      return 0;
   
   return 1; 
}
