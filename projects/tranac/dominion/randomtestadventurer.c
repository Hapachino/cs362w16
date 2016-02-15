
  /* -----------------------------------------------------------------------
 * Random testing of adventurer card
 * testG conditions
 *  1) passed in p, gamestate 
 * G conditions
 *  1) players hand is increased by correct number of coin cards
 *  2) players deck is decreased by by number of cards drawn
 *  4) players discard pile is increased by extra drawn cards - cards kept in hand
 *
 *  randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *      randomtestadventurer > randomtestadventurer.out
 *      gcov randomtestadventurer >> randomtestadventurer.out
 * -----------------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h> 



int testAdventurer (int p, struct gameState *G) {
	
	struct gameState controlG;
	int treasureCount, controlTreasureCount, i, r, j;
	
	treasureCount = 0; //reset for each itteration
	
	memcpy (&controlG, G, sizeof(struct gameState));
	
	r = adventurerCard(p, G);
		
	// Check deck for number of treasures
	for (i = 0; i < G->deckCount[p]; i++) {
		if (G->deck[p][i] == copper || G->deck[p][i] == silver || G->deck[p][i] == gold) {
			treasureCount++;
		}
	}
	
	//no treasure card in deck
	if (treasureCount == 0) {
		printf("hand count = %d, expected = %d\n", G->handCount[p], 
		controlG.handCount[p]);
		if (G->handCount[p] == controlG.handCount[p] ) 
			printf("adventurer: PASS on handcount did not change on current player\n");    
		else 	
			printf("adventurer: FAIL on handcount did not change on current player\n");

		printf("deck count = %d, expected = %d\n", G->deckCount[p], 
			controlG.deckCount[p] - r ) ;
		if (controlG.deckCount[p] -r == G->deckCount[p])  
			printf("adventurer: PASS on deckcount decreased by number of cards drawn\n");
		else 
			printf("adventurer: FAIL on deckcount decreased by number of cards drawn\n");

		printf("discard count count = %d, expected = %d\n", G->discardCount[p], 
			controlG.discardCount[p] + r);
		if (controlG.discardCount[p] + r == G->discardCount[p] )  
			printf("adventurer: PASS on discardcount changes by number of cards drawn and not kept in hand\n");
		else 
			printf("adventurer: FAIL on discardcount changes by number of cards drawn and not kept in hand\n");
		
		
		for(j = 0; j < sizeof(controlG.hand); j++){
			if(controlG.hand[p][j] == gold || controlG.hand[p][j] == silver || controlG.hand[p][j] == copper){
				controlTreasureCount++;
			}
		}
		for(j = 0; j < sizeof(G->hand); j++){
			if(G->hand[p][j] == gold || G->hand[p][j] == silver || G->hand[p][j] == copper){
				treasureCount++;
			}
		}

		printf("treasure card count = %d, expected = %d\n", treasureCount, controlTreasureCount );
		
		if(controlTreasureCount == treasureCount ){
			printf("adventurer: PASS on treasure card count increased by 2\n");
		}
		else{	
				printf("adventurer: FAIL on treasure card count increased by 2\n");
		}
	}

	// 1 treasure in deck,
	else if (treasureCount == 1) {
		printf("hand count = %d, expected = %d\n", G->handCount[p], 
		controlG.handCount[p] + 1);
		if (G->handCount[p] == controlG.handCount[p]+ 1 ) 
			printf("adventurer: PASS on handcount on current player\n");    
		else 	
			printf("adventurer: FAIL on handcount on current player\n");

		printf("deck count = %d, expected = %d\n", G->deckCount[p], 
			controlG.deckCount[p] - r ) ;
		if (controlG.deckCount[p] -r == G->deckCount[p])  
			printf("adventurer: PASS on deckcount decreased by number of cards drawn\n");
		else 
			printf("adventurer: FAIL on deckcount decreased by number of cards drawn\n");

		printf("discard count count = %d, expected = %d\n", G->discardCount[p], 
			controlG.discardCount[p] + r - 1);
		if (controlG.discardCount[p] + r - 1 == G->discardCount[p] )  
			printf("adventurer: PASS on discardcount changes by number of cards drawn and not kept in hand\n");
		else 
			printf("adventurer: FAIL on discardcount changes by number of cards drawn and not kept in hand\n");
		
		
		for(j = 0; j < sizeof(controlG.hand); j++){
			if(controlG.hand[p][j] == gold || controlG.hand[p][j] == silver || controlG.hand[p][j] == copper){
				controlTreasureCount++;
			}
		}
		for(j = 0; j < sizeof(G->hand); j++){
			if(G->hand[p][j] == gold || G->hand[p][j] == silver || G->hand[p][j] == copper){
				treasureCount++;
			}
		}

		printf("treasure card count = %d, expected = %d\n", treasureCount, controlTreasureCount + 1 );
		
		if(controlTreasureCount + 1 == treasureCount ){
			printf("adventurer: PASS on treasure card count increased by 1\n");
		}
		else{	
				printf("adventurer: FAIL on treasure card count increased by 1\n");
		}
	}
	// If at least 2 treasures in deck
	else {
		printf("hand count = %d, expected = %d\n", G->handCount[p], 
		controlG.handCount[p] + 2);
		if (G->handCount[p] == controlG.handCount[p] + 2 ) 
			printf("adventurer: PASS on handcount  on current player\n");    
		else 	
			printf("adventurer: FAIL on handcount  on current player\n");

		printf("deck count = %d, expected = %d\n", G->deckCount[p], 
			controlG.deckCount[p] - r ) ;
		if (controlG.deckCount[p] -r == G->deckCount[p])  
			printf("adventurer: PASS on deckcount decreased by number of cards drawn\n");
		else 
			printf("adventurer: FAIL on deckcount decreased by number of cards drawn\n");

		printf("discard count count = %d, expected = %d\n", G->discardCount[p], 
			controlG.discardCount[p] + r - 2);
		if (controlG.discardCount[p] + r - 2 == G->discardCount[p] )  
			printf("adventurer: PASS on discardcount changes by number of cards drawn and not kept in hand\n");
		else 
			printf("adventurer: FAIL on discardcount changes by number of cards drawn and not kept in hand\n");
		
		
		for(j = 0; j < sizeof(controlG.hand); j++){
			if(controlG.hand[p][j] == gold || controlG.hand[p][j] == silver || controlG.hand[p][j] == copper){
				controlTreasureCount++;
			}
		}
		for(j = 0; j < sizeof(G->hand); j++){
			if(G->hand[p][j] == gold || G->hand[p][j] == silver || G->hand[p][j] == copper){
				treasureCount++;
			}
		}

		printf("treasure card count = %d, expected = %d\n", treasureCount, controlTreasureCount + 2 );
		
		if(controlTreasureCount + 2 == treasureCount ){
			printf("adventurer: PASS on treasure card count increased by 2\n");
		}
		else{	
				printf("adventurer: FAIL on treasure card count increased by 2\n");
		}
	}
	

	printf("Test completed. \n");
	
	return 0;
}



int main() {
    int i, m, p, r, seed, index;
	int numPlayers = 2;
	
	int cards[10] = {copper, smithy, village, silver, mine, gold,
                gardens, remodel, embargo, cutpurse};
	
	int k[10] = {adventurer, embargo, village, minion, mine, great_hall,
			sea_hag, tribute, smithy, council_room}; 
			
	struct gameState G;
	
	printf("Random Tests-----------------------------------------------------\n");


	for (m = 0; m < 100000; m++) {	
	
		srand(time(NULL));
		seed = rand();
		SelectStream(2);
		PutSeed(3);
		
		memset(&G, 23, sizeof(struct gameState));   // clear the game state
		r = initializeGame(numPlayers, k, seed, &G);
	
		printf("Random Tests # %d\n", m + 1);
	
		// set up the game with random info per lecture video
		/*for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 25);
		}*/
		
		//set game up for testing
		p = floor(Random() * 2);
		G.deckCount[p] = 0;
		G.discardCount[p] = 0;
		G.handCount[p] = 0;
		
		// Create deck of 10 random cards
        for (i = 0; i < 10; i++) {
            index = floor(Random() * 10);
            G.deck[p][i] = cards[index];
            G.deckCount[p]++;
        }
		

        // Create fixed hand of 5 cards
        for (i = 0; i < 5; i++) {
            G.hand[p][i] = estate;
            G.handCount[p]++;
        }
		
		//call tests
		testAdventurer(p, &G);
	}
	 
	
	return 0;
}