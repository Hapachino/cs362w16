/* ---------------------------------------------------------------------------
 * Unit test for gainCard function. Test whether my test oracle achieves the
 * same results as the gainCard function.
 * ---------------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testGainCard(int supplyPos, struct gameState *post, int toFlag, int p);

int main() {
	int n, p, randCard, destination;
	struct gameState game;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
	
	SelectStream(2);
	PutSeed(3);
	
	for (n = 0; n < 2000; n++) { //runs 2000 tests
		printf ("--------------------------\n");
        printf ("Running test series %d ...\n", n+1);
	    initializeGame(2, k, 1000, &game);
		p = floor(Random() * 2);
		randCard = floor(Random() * 10); //Selects a random card from the list of cards for supply position
		//destination = floor((Random() * 3) + 1); //Sets random flag for gainCard destination
		game.deckCount[p] = floor(Random() * MAX_DECK);
		game.discardCount[p] = floor(Random() * MAX_DECK);
		game.handCount[p] = floor(Random() * MAX_HAND);
		for (destination = 1; destination < 4; destination++) {
			testGainCard(k[randCard], &game, destination, p);
		}
		
		printf ("--------------------------\n\n");
	}
    
	
	return 0;
}

int testGainCard(int supplyPos, struct gameState *post, int toFlag, int p){
	int r;
	
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	r = gainCard(supplyPos, post, toFlag, p);
	
	if (supplyCount(supplyPos, &pre) < 1) { //Nothing changes in either state here
		assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
		printf ("Test passed\n");
		
		return -1;
	}
	
	// The following code walks through the basic functionality of gainCard
	if (toFlag == 1) {
		pre.deck[p][pre.deckCount[p]] = supplyPos;
		pre.deckCount[p]++;
	}
	else if (toFlag == 2) {
		pre.hand[p][pre.handCount[p]] = supplyPos;
		pre.handCount[p]++;
	}
	else {
		pre.discard[p][pre.discardCount[p]] = supplyPos;
		pre.discardCount[p]++;
	}
	
	pre.supplyCount[supplyPos]--;
	
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0); //Checks to see if both states recieved the same results
	printf ("Test passed\n");
	
	return 0;
}

