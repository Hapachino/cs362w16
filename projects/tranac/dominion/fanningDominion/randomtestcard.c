  /* -----------------------------------------------------------------------
 * Random testing of great_hall
 * pre conditions
 *  1) calls cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);
 * post conditions
 *  1) players hand is increased by 1
 *  2) players deck is decreased by 1
 *  3) players actions are increased by 1
 *  4) players discard pile is increased by 1
 *
 * randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 *      randomtestcard > randomtestcard.out
 *      gcov randomtestcard >> randomtestcard.out
 * -----------------------------------------------------------------------*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "math.h" 
#include <time.h> 


int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int newActions;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, great_hall,
			sea_hag, tribute, smithy, council_room};
	int i, j, m;


	printf("Random Tests for great_hall----------------------------------------------------\n");
	

	for (i = 0; i < 10000; i++) {	
		
		printf("Random Tests # %d\n", i + 1);
		seed = rand(); 
		
		//from lecture
		for (m = 0; m < sizeof(struct gameState); m++) {
			((char*)&G)[m] = floor(Random() * 256);
		}
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);		

		G.handCount[currentPlayer] = floor(Random() * 10);
		//printf("handCount %d\n", G.handCount[currentPlayer]);
		G.deckCount[currentPlayer] = floor(Random() * 25);
		//printf("deckCount %d\n", G.deckCount[currentPlayer]);
		G.discardCount[currentPlayer] = floor(Random() * 25);
		//printf("discardCount %d\n", G.discardCount[currentPlayer]);

		//Randomly select cards for hand pile
		for (j = 0; j < G.handCount[currentPlayer]; j++) {
			G.hand[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		}

		//Randomly select cards for discard pile
		for (j = 0; j < G.discardCount[currentPlayer]; j++) {
			G.discard[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		}

		//Randomly select cards for deck 
		for (j = 0; j < G.deckCount[currentPlayer]; j++) {
			G.deck[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		}

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		 
		cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

		newCards = 1;
		newActions = 1;

		printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
			G.handCount[currentPlayer] + newCards - discarded);
		if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        	printf("great_hall(): PASS on handcount does not change on current player\n");    
		else 	
        	printf("great_hall: FAIL on handcount does not change on current player\n");

		printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
	 		G.deckCount[currentPlayer] - newCards + shuffledCards);
		if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        	printf("great_hall: PASS on deckcount does not change\n");
    	else 
        	printf("great_hall: FAIL on deckcount does not change\n");

		printf("numActions = %d, expected = %d\n", testG.numActions, \
	    	G.numActions + newActions);
		if (testG.numActions == G.numActions + newActions)  
        	printf("great_hall: PASS on number of actions count is correct\n");
    	else 
        	printf("great_hall: FAIL on number of actions count is not correct\n");

        printf("--------------------------------------------------------------\n");
	}

    printf("All tests completed!\n");

	return 0;
}