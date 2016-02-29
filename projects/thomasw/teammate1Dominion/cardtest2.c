/*******************************************
* Test for Village
* Add this to your dominion makefile
* cardtest2: cardtest2.c dominion.o rngs.o
     gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main(int argc, char const *argv[])
{
	int newCards = 0;
	int newActions = 0;
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

	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	//Test 1: Player gets +1 card
	printf("\nTesting draw 1 card:\n");
	newCards = 1;
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

	//Test 2: +2 action for player
	printf("\nTesting +2 action:\n");
	newActions = 2;
	printf("Action count = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	if((testG.numActions != G.numActions + newActions))
	{
		printf("----------------- TEST FAILED -----------------\n");
	}
	else
		printf("----------------- TEST PASSED -----------------\n");

	//Checking gamestate for next player. Should be unchanged.
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
