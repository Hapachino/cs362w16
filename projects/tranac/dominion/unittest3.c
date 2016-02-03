/* -----------------------------------------------------------------------
 * Testing shuffle()
 * Pre conditions
 *  1) Passes in the player number and gameState 
 * Post conditions
 *  1) Deck is shuffled
 *  2) deck size is the same 
 *  
 * shuffle: unittest3.c dominion.o rngs.o
 *      gcc -o unit3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
  int numPlayers = 2;
  int i = 0;
  int same =0;
  int seed = 1004;
  struct gameState G, storeG;
  int r;
  int sgSize, gSize;
  int thisPlayer = 0;
  int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
               council_room, village, mine, tribute, ambassador};
  memset(&G, 23, sizeof(struct gameState));   // clear the game state
  r = initializeGame(numPlayers, kcards, seed, &G);

  printf ("TESTING shuffle():\n");

  memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before shuffle.

  shuffle(thisPlayer, &G);
  
  sgSize = storeG.deckCount[thisPlayer];
  gSize = G.deckCount[thisPlayer];
  assert(sgSize == gSize);  //assert decks are the same size
  
  for (i = 0; i < storeG.deckCount[thisPlayer]; i++) {
    if (storeG.deck[thisPlayer][i] == G.deck[thisPlayer][i])
	{
		printf("same %d, %d\n", storeG.deck[thisPlayer][i], G.deck[thisPlayer][i]);
		same++;
	}
	else{
		printf("not same %d, %d\n", storeG.deck[thisPlayer][i], G.deck[thisPlayer][i]);
	}
  }
	assert(same != gSize);
	
  printf ("Test passed\n");

  return 0;
}
