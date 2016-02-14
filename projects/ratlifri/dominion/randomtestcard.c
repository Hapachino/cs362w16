#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>
#include "interface.h"

int checkSmithy(int p, struct gameState *post, int pos) {
	int i, r;
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));

	r = cardEffectSmithy(p, post, pos);

    // oracle - expected results of adventurer in pre game state
	pre.discard[p][pre.handCount[p]-1] = pre.hand[p][pos];
	pre.discardCount[p]++;
	for( i=0; i<3; i++ ) {
		pre.deckCount[p]--;
		pre.handCount[p]++;
		pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
		printf("deck count %d, hand count %d\n", pre.deckCount[p], pre.handCount[p]);
	}

    // oracle - compare results 
	if ( pre.deckCount[p] == post->deckCount[p] ) {
		printf("results: deck count pass %d == %d\n", pre.deckCount[p], post->deckCount[p]);
	} else {
		printf("results: deck count FAIL %d != %d\n", pre.deckCount[p], post->deckCount[p]);
	}

	if ( pre.handCount[p] == post->handCount[p] ) {
		printf("         hand count pass %d == %d\n", pre.handCount[p], post->handCount[p]);
	} else {
		printf("         hand count FAIL %d != %d\n", pre.handCount[p], post->handCount[p]);
	}

	if ( pre.discardCount[p] == post->discardCount[p] ) {
		printf("         discard count pass %d == %d\n", pre.discardCount[p], post->discardCount[p]);
	} else {
		printf("         discard count FAIL %d != %d\n", pre.discardCount[p], post->discardCount[p]);
	}

//	assert (r == 0);
//	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

    return 0;
}

int main () {

	int i, j, x, n, p;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
				 remodel, smithy, village, baron, great_hall};
	int t[3] = {copper, silver, gold};

	struct gameState G;

	printf("--------- Testing adventurer with random tests ---------\n");

	SelectStream( floor(Random() * 256) ); // 256 streams available
	PlantSeeds( -1 );                      // use system clock for seed

	for (n = 0; n < 2000; n++) {

		p = floor(Random() * MAX_PLAYERS);
		if ( p < 2 ) {
			p = 2;
		}
		initializeGame(p, k, floor(Random()*1000), &G);
		// randomize card pile counts
		G.handCount[p] = floor(Random() * MAX_HAND) + 5;
		G.deckCount[p] = floor(Random() * MAX_HAND) + 5;
		G.discardCount[p] = floor(Random() * MAX_DECK) + 5;
		// randomize cards in hand but ensure at least one smithy
		G.hand[p][0] = smithy;
		for (i = 1; i < G.handCount[p]; i++) {
			x = floor(Random() * 10);
			if ( x < 5 ) {
				j = floor(Random() * 10);  // random kingdom cards
				G.hand[p][i] = k[j];
			} else {
				j = floor(Random() * 3);   // random treasure cards
				G.hand[p][i] = t[j];
			}
		}
		// randomize cards in deck
		for (i = 1; i < G.deckCount[p]; i++) {
			x = floor(Random() * 10);
			if ( x < 8 ) {
				j = floor(Random() * 10);  // random kingdom cards - bias
				G.deck[p][i] = k[j];
			} else {
				j = floor(Random() * 3);   // random treasure cards
				G.deck[p][i] = t[j];
			}
		}
		// initialization complete, check adventurer
		printf("Test# %d: ", n+1);
		checkSmithy(p, &G, 0);
		printf ("\n");
	}

	return 0;
}
