/* -----------------------------------------------------------------------
 * Unit test for Great Hall Card. Pretty much identical to Village except
 * with on less action. Again here we trust that discCard and drawCard
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

int testAdventurer(struct gameState *post, int p);

int main() {
	
	
  int n, p, j, i;
  struct gameState game;
  int treasure[3] = {copper, silver, gold};
  int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
  
  SelectStream(2);
  PutSeed(3);
  
  
  for (n = 0; n < 2000; n++) { //runs 2000 tests
      printf ("--------------------------\n");
      printf ("Running test series %d ...\n", n+1);
	  
	  initializeGame(2, k, 1000, &game);
	  p = floor(Random() * 2);
	  game.deckCount[p] = floor(Random() * MAX_DECK);
	  game.discardCount[p] = floor(Random() * MAX_DECK);
	  game.handCount[p] = floor(Random() * MAX_HAND);
	  for (j = 0; j < 3; j++) {
		  for (i = 1; i < 3; i++){ //Randomly changes top two cards in the deck to a treasure
		  game.deck[p][game.deckCount[p]-i] = treasure[j];
	   }
	   
	   testAdventurer(&game, p); 
	  }
	   printf ("--------------------------\n\n");
  }
  return 0;
}

int testAdventurer(struct gameState *post, int p){
	int r, i;
	struct gameState pre;
	
	memcpy (&pre, post, sizeof(struct gameState));
	
	
	r = playAdventurer(post, p);
	
	pre.handCount[p] += 2;
	pre.deckCount[p] -= 2;
	
	printf ("Testing player %d's deck count...\n", p+1);
	if (pre.deckCount[p] == post->deckCount[p]) { //Makes sure both deck counts are equal
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