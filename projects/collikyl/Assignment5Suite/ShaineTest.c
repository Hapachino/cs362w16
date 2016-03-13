#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

int main()
{
	int x, treas, draw;
	int treas1 = 0;
	int treas2 = 0;
	int i = 0;
	int temp[MAX_HAND];
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {minion, mine, adventurer, great_hall, cutpurse,
	sea_hag, tribute, smithy, council_room, copper};

	printf("Testing adventurer card\n");
	
	initializeGame(numPlayers, k, seed, &G);
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.hand[testG.whoseTurn][testG.handCount[testG.whoseTurn]] = adventurer;
	testG.handCount[testG.whoseTurn] = testG.handCount[testG.whoseTurn]+1;
	printf("\nPrinting PreTest\n");
	printHand(testG.whoseTurn,&testG);
	playCard(testG.handCount[testG.whoseTurn]-1,0,0,0,&testG);
//	adventurerCard(&testG, 0);
	printf("\nPrinting PostTest\n");
	printHand(testG.whoseTurn,&testG);
	printf("Expected: %d, Result: %d\n", G.handCount[G.whoseTurn] + 2, testG.handCount[testG.whoseTurn]);

//	G.discardCount[G.whoseTurn] = 5;	
//	memcpy(&testG, &G, sizeof(struct gameState));
//	adventurerCard(&testG, 0);
	
//	while(treas<2){
//	drawCard(G.whoseTurn, &G);
//	draw = G.hand[G.whoseTurn][G.handCount[G.whoseTurn]-1];
//	if (draw == copper || draw == silver || draw == gold){
//	  treas++;
//	}
//	else{
//	  temp[i]=draw;
//	  G.handCount[G.whoseTurn]--; 
//	  i++;
//	}
  //  }
     
//	printf("Expected discard count: %d, Result: %d\n", G.discardCount[G.whoseTurn] + i, testG.discardCount[testG.whoseTurn]);
//	
//	for(x = 0; x < G.handCount[G.whoseTurn]; x++){
//		if (G.hand[G.whoseTurn][x] == copper || G.hand[G.whoseTurn][x] == silver || G.hand[G.whoseTurn][x] == gold){
//			treas1++;
//		}
//			
//	}
//	
//	for(x = 0; x < testG.handCount[testG.whoseTurn]; x++){
//		if (testG.hand[testG.whoseTurn][x] == copper || testG.hand[testG.whoseTurn][x] == silver || testG.hand[testG.whoseTurn][x] == gold){
//			treas2++;
//		}
//			
//	}
//	
//	printf("Expected treasure count: %d, Result: %d\n", treas1, treas2);
	
	return 0;
}
