/* -----------------------------------------------------------------------
 * Random test for Village. Here we trust that discardCard and drawCard
 * are not broken as we assume we have already ran tests for them.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testVillage(struct gameState *post, int hand, int p);

int main() {
	
	
  int n, p, pos;
  struct gameState game;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
  
  SelectStream(2);
  PutSeed(3);
  
  
  for (n = 0; n < 5000; n++) { //runs 5000 tests
      printf ("--------------------------\n");
      printf ("Running test series %d ...\n", n+1);
	  initializeGame(2, k, 1000, &game);
	  p = floor(Random() * 2);
	  game.deckCount[p] = floor(Random() * MAX_DECK); //random deck size
	  game.discardCount[p] = floor(Random() * MAX_DECK); //random discardCount
	  game.handCount[p] = floor(Random() * MAX_HAND); //random handCount
	  pos = floor(Random() * game.handCount[p]); //Places card randomly in hand
	  
	  testVillage(&game, pos, p);
	  printf ("--------------------------\n\n");
  }
  return 0;
}

int testVillage(struct gameState *post, int hand , int p){
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	int r, i;
	
	r = playVillage(p, post, hand);
	
	drawCard(p, &pre);
	pre.numActions += 2;
	discardCard(hand, p, &pre, 0);
	
	printf ("Testing player %d's deck count...\n", p+1);
	if (pre.deckCount[p] == post->deckCount[p]) { //Makes sure both deck counts are equal
		printf ("Test passed\n\n");
	}
	else
		printf ("Test failed\n\n");
	
	printf ("Testing player %d's discard count...\n", p+1);
	if (pre.discardCount[p] == post->discardCount[p]){ //Makes sure both hand counts are correct
		printf ("Test passed\n\n"); 
	}
	else
		printf ("Test failed\n\n");
	
	printf ("Testing player %d's hand count...\n", p+1);
	if (pre.handCount[p] == post->handCount[p]){ //Makes sure both hand counts are correct
		printf ("Test passed\n\n");
	}
	else
		printf ("Test failed\n\n");
	
	printf ("Testing player %d's action count...\n", p+1);
	if (pre.numActions == post->numActions){ //Makes sure both action counts are correct
		printf ("Test passed\n\n");
	}
	else
		printf ("Test failed\n\n");
	
	for ( i = 0; i < post->numPlayers; i++) {
		if ( i != p) {
			printf ("Testing player %d's deck count...\n", i+1);
			if (pre.deckCount[i] == post->deckCount[i]) { //Makes sure both deck counts are equal
				printf ("Test passed\n\n");
			}
			else
				printf ("Test failed\n\n");
	
			printf ("Testing player %d's discard count...\n", i+1);
			if (pre.discardCount[i] == post->discardCount[i]){ //Makes sure both hand counts are correct
				printf ("Test passed\n\n"); 
			}
			else
				printf ("Test failed\n\n");
	
			printf ("Testing player %d's hand count...\n", i+1);
			if (pre.handCount[i] == post->handCount[i]){ //Makes sure both hand counts are correct
				printf ("Test passed\n\n");
			}
			else
				printf ("Test failed\n\n");
					
			printf ("Testing player %d's action count...\n", i+1);
			if (pre.numActions == post->numActions){ //Makes sure both action counts are correct for others
				printf ("Test passed\n\n");
			}
			else
				printf ("Test failed\n\n");
		}
	}
	
	printf ("Testing for other state changes...\n");
	if (memcmp(&pre, post, sizeof(struct gameState)) == 0){ //Makes sure no other state change has happened
		printf ("Test passed\n\n");
	}
	else
		printf ("Test failed\n\n");
	
	
	return 0;
}