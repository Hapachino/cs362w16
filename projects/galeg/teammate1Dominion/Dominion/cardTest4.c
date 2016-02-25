/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
    int xtraCoins = 0;
    int shuffledCards = 0;
    int drawnCard1 = 0;
    int drawnCard2 = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 645;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: play village card --------------
	printf("TEST 1: = Play village card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	//If there is something left in the deck, the number of new cards should be 1
	printf("drawn card count = %d, expected = %d\n", (G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]), 4);
	assert((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) == 4);

	xtraCoins = 0;

	//this should be 4
	newCards = G.deckCount[thisPlayer] - testG.deckCount[thisPlayer];

	printf("hand count before hand = %d, newCards (should be 4) = %d, discarded = %d\n", G.handCount[thisPlayer], newCards, discarded);
	assert(newCards == 4);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);

	printf("G.deckCount = %d ", G.deckCount[thisPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

	printf("actions remaining = %d, expected = %d\n", testG.numActions, G.numActions);
	assert(testG.numActions == G.numActions);

	printf("buys remaining = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
	assert(testG.numBuys == G.numBuys + 1);

	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.coins == G.coins + xtraCoins);

	printf("kept should be of type treasure\n");

	printf("Other Player's handcount should be higher by 1, and deckcount should be 1 less:\n");

	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + 1 );
	assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + 1);

	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] - 1);
	assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer] - 1);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


