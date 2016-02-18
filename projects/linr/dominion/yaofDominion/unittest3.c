/*
*Author: Robyn Lin
*This tests the scoreFor() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testScoreFor(int, struct gameState *);

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
   int r, p, result, test;
   int seed = 1000;
   int numPlayer = 3;
//   int player = 2; //test score for 2nd player
   struct gameState G;

   int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

   printf("TESTING scoreFor():\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

   for(p = 0; p < numPlayer; p++) //loop through number of players
   {   
      test = scoreFor(p, &G);
      result = testScoreFor(p, &G);
      if(result == 1)
      {
	printf("Score returned by scoreFor() in dominion.c for player %d does not match score calculated in this unit test.\n Possible existing bug in scoreFor() function.\n", p+1);
      }

   }

   if(result == 0) 
      printf("All tests passed!\n");

   return 0;
}

int testScoreFor(int player, struct gameState *post)
{
   int i, postScore = 0;
   int score = 0;
//   int numCards = post->deckCount[0];
//printf("starting # of cards is %d\n", numCards);

   struct gameState pre;
   memcpy(&pre, post, sizeof(struct gameState));
        
   //score from hand
   for (i = 0; i < pre.handCount[player]; i++)
    {
      if (pre.hand[player][i] == curse) { score = score - 1; };
      if (pre.hand[player][i] == estate) { score = score + 1; };
      if (pre.hand[player][i] == duchy) { score = score + 3; };
      if (pre.hand[player][i] == province) { score = score + 6; };
      if (pre.hand[player][i] == great_hall) { score = score + 1; };
      if (pre.hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
    }
   //score from discard pile
   for (i = 0; i < pre.discardCount[player]; i++)
    {
      if (pre.discard[player][i] == curse) { score = score - 1; };
      if (pre.discard[player][i] == estate) { score = score + 1; };
      if (pre.discard[player][i] == duchy) { score = score + 3; };
      if (pre.discard[player][i] == province) { score = score + 6; };
      if (pre.discard[player][i] == great_hall) { score = score + 1; };
      if (pre.discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
    }

   //score from deck
   for (i = 0; i < pre.deckCount[player]; i++)
    {
      if (pre.deck[player][i] == curse) { score = score - 1; };
      if (pre.deck[player][i] == estate) { score = score + 1; };
      if (pre.deck[player][i] == duchy) { score = score + 3; };
      if (pre.deck[player][i] == province) { score = score + 6; };
      if (pre.deck[player][i] == great_hall) { score = score + 1; };
      if (pre.deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, &pre) / 10 ); };
    }

    postScore = scoreFor(player, post);
  
    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

    if(postScore != score)
       return 1;

   return 0;
}
