/*******************************************
* Test for smithy
* Add this to your dominion makefile
* cardtest3: cardtest3.c dominion.o rngs.o
     gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main(int argc, char const *argv[])
{
	int newCards = 0;
	int discarded = 1;
	int shuffledCards = 0;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Test1 - +3 cards
	printf("\nTesting draw 3 card:\n");
	newCards = 3;
	int xtraCoins = 0;
	printf("New hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	if ((testG.handCount[thisPlayer]) != (G.handCount[thisPlayer] + newCards - discarded))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	printf("\nChecking coins unchanged:\n");
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	if (testG.coins != G.coins + xtraCoins)
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	//Deck cound should decrement after card is drawn.
	printf("\nTesting deck count after card draw\n");
	printf("Original deck count = %d\n", G.deckCount[thisPlayer]);
	printf("New deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
	if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - 1)
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	//Check gamestate is unchanged
	printf("\nTesting unchanged state for player2:\n");
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer+1], G.handCount[thisPlayer+1]);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer+1], G.deckCount[thisPlayer+1]);
	printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer+1], G.discardCount[thisPlayer+1]);
	if ((testG.handCount[thisPlayer+1]) != (G.handCount[thisPlayer+1]) || (testG.deckCount[thisPlayer+1]) != (G.deckCount[thisPlayer+1]) || (testG.discardCount[thisPlayer+1]) != (G.discardCount[thisPlayer+1]))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");	

	return 0;
}