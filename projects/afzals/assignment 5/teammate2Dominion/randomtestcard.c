#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int main()
{
	int rcard, n, p;
	int t;
	int i = 0;
	struct gameState G, testG;
	int k[20] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall, copper, copper, copper, 
		   copper, silver, silver, silver, gold, gold, gold};
	
	SelectStream(8);
	PutSeed(2);

	printf("Testing great hall card\n");
	
	for (n = 0; n < 50; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
    }
		p = floor(Random() * 2);
		G.whoseTurn = p;
		G.deckCount[p] = floor(Random() * MAX_HAND);
		G.discardCount[p] = 5;
		G.handCount[p] = floor(Random() * MAX_HAND);
		for(i = 0; i < G.deckCount[p]; i++){
			rcard = floor(Random() * 19);
			G.deck[p][i] = k[rcard];
		}
		for(i = 0; i < G.handCount[p]; i++){
			rcard = floor(Random() * 19);
			G.hand[p][i] = k[rcard];
		}
		for(i = 0; i < G.discardCount[p]; i++){
			rcard = floor(Random() * 19);
			G.discard[p][i] = k[rcard];
		}
		
		memcpy(&testG, &G, sizeof(struct gameState));
		
	t = adventurerCard(&testG, 0);
	assert(t == 0);
	
	greatHallCard(&testG, 0);
	
	if(G.handCount[p] + 1 != testG.handCount[p]){
		printf("Failed hand count, Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 1, testG.handCount[testG.whoseTurn]);
	}

	if(G.numActions + 1 != testG.numActions){
		printf("Failed action count, Expected action count: %d, Result: %d\n", G.numActions + 1, testG.numActions);
	}
	}	
	return 0;
}
