/* -----------------------------------------------------------------------
 * CS362 - Assignment 5 - Emmalee Jones
 * Description of cardtest1 for smithy Card. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *      cardtest1 >> cardtestresult.out
 *      gcov cardtest1 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing cardtest1: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 0 = +3 cards --------------
	printf("TEST 1: +3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//choice1 = 0;
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	//Test smithy card
	printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
		G.handCount[currentPlayer] + newCards - discarded);
	if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("smithy(): PASS on handcount does not change on current player\n");    
	else 	
        printf("smithy: FAIL on handcount does not change on current player\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
	 G.deckCount[currentPlayer] - newCards + shuffledCards);
		if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        printf("smithy: PASS on deckcount does not change\n");
    else 
        printf("smithy: FAIL on deckcount does not change\n");

	printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
		G.handCount[nextPlayer]);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer])
        printf("smithy(): PASS on handcount does not change on next player\n");    
	else 	
        printf("smithy: FAIL on handcount does not change on next player\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
		G.deckCount[nextPlayer]);
	if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer])  
        printf("smithy: PASS on deckcount does not change on next player\n");
    else 
        printf("smithy: FAIL on deckcount does not change on next player\n");

	printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
		 testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
		 G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
	if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("smithy: PASS on estate count does not change\n");
    else 
        printf("smithy: FAIL on estate count does not change\n");
    if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("smithy: PASS on duchy count does not change\n");
    else 
        printf("smithy: FAIL on duchy count does not change\n");    
	    if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("smithy: PASS on province count does not change\n");
    else 
        printf("smithy: FAIL on province count does not change\n");

	printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
	    G.supplyCount[adventurer]);
    if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        printf("smithy: PASS on adventurer count does not change\n");
    else 
        printf("smithy: FAIL on adventurer count does not change\n");

 	printf("All tests completed!\n");    

	return 0;
}