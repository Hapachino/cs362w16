/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of cardtest4 for great_hall Card. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *      cardtest4 >> cardtestresult.out
 *      gcov cardtest4 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "great_hall"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int newActions;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing cardtest4: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 0 = +1 cards --------------
	printf("TEST 1: +1 cards, +1 action\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//choice1 = 0;
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	newActions = 1;
	//Test great_hall card
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

	return 0;
}