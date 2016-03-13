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
	int x, rcard, n, p, draw;
	int t;
	int treas1 = 0;
	int treas2 = 0;
	int i = 0;
	int pass = 0;
	int treas = 0;
	int temp[MAX_HAND];
	struct gameState G, testG;
	int k[20] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall, copper, copper, copper, 
		   copper, silver, silver, silver, gold, gold, gold};
	
	SelectStream(8);
	PutSeed(2);

	printf("Testing adventurer card\n");
	
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
	t = cardEffect(adventurer, 0, 0, 0, &testG, 0, 0);
	
	assert(t == 0);
	
	if(G.handCount[G.whoseTurn] + 2 != testG.handCount[testG.whoseTurn]){
		printf("Failed card number, Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 2, testG.handCount[testG.whoseTurn]);
		pass = 1;
	}
	
	while(treas<2){
	drawCard(G.whoseTurn, &G);
	draw = G.hand[G.whoseTurn][G.handCount[G.whoseTurn]-1];
	if (draw == copper || draw == silver || draw == gold){
	  treas++;
	}
	else{
	  temp[i]=draw;
	  G.handCount[G.whoseTurn]--; 
	  i++;
	}
    }
	
	if(G.discardCount[G.whoseTurn] + i != testG.discardCount[testG.whoseTurn]){
		printf("Failed discard count, expected: %d, Result: %d\n", G.discardCount[G.whoseTurn] + i, testG.discardCount[testG.whoseTurn]);
		pass = 1;
	}
	
	for(x = 0; x < G.handCount[G.whoseTurn]; x++){
		if (G.hand[G.whoseTurn][x] == copper || G.hand[G.whoseTurn][x] == silver || G.hand[G.whoseTurn][x] == gold){
			treas1++;
		}
			
	}
	
	for(x = 0; x < testG.handCount[testG.whoseTurn]; x++){
		if (testG.hand[testG.whoseTurn][x] == copper || testG.hand[testG.whoseTurn][x] == silver || testG.hand[testG.whoseTurn][x] == gold){
			treas2++;
		}
			
	}
	
	if(treas1 != treas2){
		printf("Failed treasure count, Expected: %d, Result: %d\n", treas1, treas2);
		pass = 1;
	}
	
	if(pass == 0){
		printf("Passed all tests\n");
	}

	}
	printf("Hand count: %d, MAX_HAND: %d\n", G.handCount[p], MAX_HAND);
	
	return 0;
}
