/* -----------------------------------------------------------------------
 * CS362 - Assignment 4 - Emmalee Jones
 * Date: 02/14/2016
 * Description of randomtestadventurer.c for adventurer Card in card effect function in dominion.c. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *      randomtestadventurer > randomtestadventurer.out
 *      gcov randomtestadventurer >> randomtestadventurer.out
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

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int newActions;
    int newBuys;
    int nextCards;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, great_hall,
			sea_hag, tribute, smithy, council_room};

	int i, j, m;

	printf("----------------- Testing randdomtestadventurer.c: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: choice1 = 0 = +2 cards --------------
	printf("Random Tests\n");

	for (m = 0; m < 10000; m++) {	

		seed = rand(); 

		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&G)[j] = floor(Random() * 256);
		}
		// initialize a game state and player cards
		initializeGame(numPlayers, k, seed, &G);		

		G.handCount[currentPlayer] = floor(Random() * 10);
		
		G.deckCount[currentPlayer] = floor(Random() * 25);
		
		G.discardCount[currentPlayer] = floor(Random() * 25);
	

		//Randomly select cards for hand pile
		for (i = 0; i < G.handCount[currentPlayer]; i++) {
			G.hand[currentPlayer][i] = floor(Random() * (treasure_map + 1));
		}

		//Randomly select cards for discard pile
		for (i = 0; i < G.discardCount[currentPlayer]; i++) {
			G.discard[currentPlayer][i] = floor(Random() * (treasure_map + 1));
		}

		//Randomly select cards for deck 
		for (i = 0; i < G.deckCount[currentPlayer]; i++) {
			G.deck[currentPlayer][i] = floor(Random() * (treasure_map + 1));
		}

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

		newCards = 2;
		nextCards = 0;
		newActions = 0;
		newBuys = 0;

		//Test adventurer card
		printf("--------------------------------------------------------\n");
		
		printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
			G.handCount[currentPlayer] + newCards - discarded);
		if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        	printf("adventurer: PASS on handcount does not change on current player\n");    
		else 	
       		printf("adventurer: FAIL on handcount does not change on current player\n");

		printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
			G.deckCount[currentPlayer] - newCards + shuffledCards);
		if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        	printf("adventurer: PASS on deckcount does not change\n");
    	else 
        	printf("adventurer: FAIL on deckcount does not change\n");

    	printf("discard count count = %d, expected = %d\n", testG.discardCount[currentPlayer], \
			G.discardCount[currentPlayer]);
		if (testG.discardCount[currentPlayer] == G.discardCount[currentPlayer])  
        	printf("adventurer: PASS on discardcount does not change\n");
    	else 
        	printf("adventurer: FAIL on discardcount does not change\n");

		printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
			G.handCount[nextPlayer] + nextCards);
    	if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + nextCards)
       		printf("adventurer: PASS on handcount does not change on next player\n");    
		else 	
        	printf("adventurer: FAIL on handcount does not change on next player\n");

		printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
			G.deckCount[nextPlayer] - nextCards);
		if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - nextCards)  
        	printf("adventurer: PASS on deckcount does not change on next player\n");
   		else 
        	printf("adventurer: FAIL on deckcount does not change on next player\n");

		printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
		 	testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
		 	G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
		if (testG.supplyCount[estate] == G.supplyCount[estate])  
       		printf("adventurer: PASS on estate count does not change\n");
   		else 
        	printf("adventurer: FAIL on estate count does not change\n");

    	if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        	printf("adventurer: PASS on duchy count does not change\n");
    	else 
        	printf("adventurer: FAIL on duchy count does not change\n");    
	    if (testG.supplyCount[province] == G.supplyCount[province])  
        	printf("adventurer: PASS on province count does not change\n");
    	else 
        	printf("adventurer: FAIL on province count does not change\n");

		printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
	    	G.supplyCount[adventurer]);
    	if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        	printf("adventurer: PASS on adventurer count does not change\n");
    	else 
        	printf("adventurer: FAIL on adventurer count does not change\n");

		printf("--------------------------------------------------------\n");
	}

    printf("All tests completed!\n");

	return 0;
}