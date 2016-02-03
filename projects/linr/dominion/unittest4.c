/*This tests isGameOver() function*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testIsGameOver(struct gameState *);

int main() {
   int r, result;
   int numPlayer = 3;
   int seed = 1000;
   struct gameState G;

   int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
   printf ("TESTING isGameOver():\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game               }

   result = testIsGameOver(&G);

   printf ("All tests passed!\n");

   return 0;
}

int testIsGameOver(struct gameState *G) {
   int result;
   result = isGameOver(G);

   printf("Test #1: Setting provinces supply count to 0...\n");
   if(G->supplyCount[province] == 0) { //no more provinces remaining
 	assert (result == 1);
	return result;
   }

   printf("Test #2: Setting 3 supply counts to 0...\n");
   //Run out of 3 supplies
   if(G->supplyCount[mine] == 0) { //no more provinces remaining
 	assert (result == 0);
	return result;
   }
   if(G->supplyCount[feast] == 0) { //no more provinces remaining
 	assert (result == 0);
	return result;
   }
   if(G->supplyCount[baron] == 0) { //no more provinces remaining
 	assert (result == 1);
	return result;
   }

   assert(result == 0);

   return result;
}
