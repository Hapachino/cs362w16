/*
 * cardtest2.c
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

#define TESTCARD "adventurer"

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

	// ----------- TEST 1: choice1 = 1 = +2 cards --------------
	printf("TEST 1: = Play adventurer card\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	//If there is something left in the deck, the number of new cards should be 2
	if (testG.deckCount > 0) {
		printf("kept card count = %d, expected = %d\n", (G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]), 2);
		assert((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) == 2);
		newCards = 2;
	} else {
		newCards = (G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] - testG.discardCount[thisPlayer]);
	}
	discarded = G.deckCount[thisPlayer] - testG.deckCount[thisPlayer] - newCards;
	xtraCoins = 0;

	//The - 1 accounts for the fact that adventurer is discarded.
	printf("hand count before hand = %d, newCards = %d, discarded = %d\n", G.handCount[thisPlayer], newCards, discarded);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1);
	assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);

	printf("G.deckCount = %d ", G.deckCount[thisPlayer]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards - discarded);
	assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards - discarded);

	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
	assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded);

	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	assert(testG.coins == G.coins + xtraCoins);

	printf("kept should be of type treasure\n");

	if( newCards >= 1 ) {
		drawnCard1 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1];
		printf("drawnCard1 should be copper, silver or gold.\n");
		if(drawnCard1 == copper) {
			printf("drawnCard1 is copper.\n");
		} else if (drawnCard1 == silver) {
			printf("drawnCard1 is silver.\n");
		} else if (drawnCard1 == gold) {
			printf("drawnCard1 is gold.\n");
		} else {
			printf("drawnCard1 isn't a treasure card.\n");
		}
		assert(drawnCard1 == copper || drawnCard1 == silver || drawnCard1 == gold);
	}
	if (newCards == 2) {
		drawnCard2 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2];
		printf("drawnCard2 should be copper, silver or gold.\n");
		if(drawnCard2 == copper) {
			printf("drawnCard2 is copper.\n");
		} else if (drawnCard2 == silver) {
			printf("drawnCard2 is silver.\n");
		} else if (drawnCard2 == gold) {
			printf("drawnCard2 is gold.\n");
		} else {
			printf("drawnCard2 isn't a treasure card.\n");
		}
		assert(drawnCard2 == copper || drawnCard2 == silver || drawnCard2 == gold);
	}

	printf("Other Player's handcount,deckcount, should be unchanged:");

	printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] );
	assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);

	printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer] );
	assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


