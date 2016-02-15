/* -----------------------------------------------------------------------
 * CS362 - Assignment 4 - Emmalee Jones
 * Date: 02/14/2016
 * Description of randomtestcard.c for great_hall Card in card effect function in dominion.c. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 *      randomtestcard > randomtestcard.out
 *      gcov randomtestcard >> randomtestcard.out
 * -----------------------------------------------------------------------
 */ 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "math.h" 
#include <time.h> 

#define TESTCARD "great_hall"

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


	printf("----------------- Testing randdomtestcard.c: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: choice1 = 0 = +2 cards --------------
	printf("Random Tests\n");

	for (i = 0; i < 10000; i++) {	

		seed = rand(); 

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

		//Test great_hall card
		printf("--------------------------------------------------------------\n");

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

		printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
			G.handCount[nextPlayer]);
    	if (testG.handCount[nextPlayer] == G.handCount[nextPlayer])
        	printf("great_hall(): PASS on handcount does not change on next player\n");    
		else 	
        	printf("great_hall: FAIL on handcount does not change on next player\n");

		printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
			G.deckCount[nextPlayer]);
		if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer])  
        	printf("great_hall: PASS on deckcount does not change on next player\n");
    	else 
        	printf("great_hall: FAIL on deckcount does not change on next player\n");

		printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
		 	testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
			G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
		if (testG.supplyCount[estate] == G.supplyCount[estate])  
        	printf("great_hall: PASS on estate count does not change\n");
   		else 
        	printf("great_hall: FAIL on estate count does not change\n");
    	if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        	printf("great_hall: PASS on duchy count does not change\n");
    	else 
        	printf("great_hall: FAIL on duchy count does not change\n");    
	    if (testG.supplyCount[province] == G.supplyCount[province])  
        	printf("great_hall: PASS on province count does not change\n");
   		else 
        	printf("great_hall: FAIL on province count does not change\n");

		printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
	   		G.supplyCount[adventurer]);
    	if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        	printf("great_hall: PASS on adventurer count does not change\n");
    	else 
        	printf("great_hall: FAIL on adventurer count does not change\n");

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