/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of cardtest3 for council_room Card. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 *      cardtest3 >> cardtestresult.out
 *      gcov cardtest3 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

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
    int newBuys;
    int nextCards;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing cardtest3: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 0 = +4 cards --------------
	printf("TEST 1: +4 cards, +1 buy, +1 card for nextPlayer\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	//choice1 = 0;
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 4;
	nextCards = 1;
	newActions = 0;
	newBuys = 1;
	//Test council_room card
	printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
		G.handCount[currentPlayer] + newCards - discarded);
	if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("council_room(): PASS on handcount does not change on current player\n");    
	else 	
        printf("council_room: FAIL on handcount does not change on current player\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
	 G.deckCount[currentPlayer] - newCards + shuffledCards);
		if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        printf("council_room: PASS on deckcount does not change\n");
    else 
        printf("council_room: FAIL on deckcount does not change\n");

	printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
		G.handCount[nextPlayer] + nextCards);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + nextCards)
        printf("council_room(): PASS on handcount does not change on next player\n");    
	else 	
        printf("council_room: FAIL on handcount does not change on next player\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
		G.deckCount[nextPlayer] - nextCards);	
	if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - nextCards)  
        printf("council_room: PASS on deckcount does not change on next player\n");
    else 
        printf("council_room: FAIL on deckcount does not change on next player\n");

	printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
		 testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
		 G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
	if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("council_room: PASS on estate count does not change\n");
    else 
        printf("council_room: FAIL on estate count does not change\n");

    if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("council_room: PASS on duchy count does not change\n");
    else 
        printf("council_room: FAIL on duchy count does not change\n");  

	if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("council_room: PASS on province count does not change\n");
    else 
        printf("council_room: FAIL on province count does not change\n");

	printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
	    G.supplyCount[adventurer]);
    if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        printf("council_room: PASS on adventurer count does not change\n");
    else 
        printf("council_room: FAIL on adventurer count does not change\n");

	printf("numBuys = %d, expected = %d\n", testG.numBuys, \
	    G.numBuys + newBuys);
	if (testG.numBuys == G.numBuys + newBuys)  
        printf("council_room: PASS on number of buys count is correct\n");
    else 
        printf("council_room: FAIL on number of buys count is not correct\n");

    printf("All tests completed!\n");

	return 0;
}