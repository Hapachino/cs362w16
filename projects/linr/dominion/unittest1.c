/*This tests the shuffle() function*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testShuffle(int, struct gameState *);

int main() {
   int r;
   int seed = 1000;
   int numPlayer = 3;
   int p = 2;
   struct gameState G;
   int k[10] = {adventurer, council_room, feast, gardens, mine
                                   , remodel, smithy, village, tribute, embargo};

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

   printf("TESTING shuffle():\n");

   testShuffle(p, &G);

   printf("All tests passed!\n");

   return 0;
}

int testShuffle(int player, struct gameState *post){
   int result;
   struct gameState pre;
   memcpy(&pre, post, sizeof(struct gameState));

   printf("Number of cards before shuffling: %d\n", pre.deckCount[player]);

   result = shuffle(player, post);

   printf("Number of cards after shuffling: %d\n", post->deckCount[player]);

   assert(pre.deckCount[player] == post->deckCount[player]); //check that number of cards before & after shuffle are the same

   return 0;
}

