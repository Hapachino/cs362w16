

#include <stdio.h>
#include "minunit.h"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h> 

#define TESTCARD "steward"

int tests_run = 0;

int foo = 7;
int bar = 4;

int newCards = 0;
int discarded = 1;
int xtraCoins = 0;
int shuffledCards = 0;

int i, j, m;
int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
int remove1, remove2;
int seed = 1000;
int numPlayers = 2;
int thisPlayer = 0;
struct gameState G, testG;
int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
sea_hag, tribute, smithy, council_room };

/*for smithy test
if handcard add 3 and -1(discard this card)
if deckcard -3
if coins/ action keep the same
bug in smithy : only draw 2 cards
*/
static void generateRandDeckHand()
{
	initializeGame(numPlayers, k, seed, &G);
	G.deckCount[thisPlayer] = 0;
	G.handCount[thisPlayer] = 0;
	int cardChoice[7] = { 0, 1, 2, 3, 4, 5, 6 };
	int handSize = rand() % 6; // rand a handcard size
	int i = 0;
	int cardToHand = 0;
	for (i = 0; i < handSize; i++) // rand hand card type
	{
		cardToHand = rand() % 7;
		G.hand[thisPlayer][i] = cardToHand;

	}
	G.handCount[thisPlayer] = handSize;
	int deckSize = rand() % 6; // rand deck exist card size
	int cardOnDeck = 0;
	for (i = 0; i < deckSize; i++) // rand hand card type
	{
		cardOnDeck = rand() % 7;
		G.deck[thisPlayer][i] = cardOnDeck;
	}
	G.deckCount[thisPlayer] = deckSize;
	// initialize discard card set for 0 card on deck and need to shuffle to get new deck set
	G.discard[thisPlayer][0] = 1;
	G.discard[thisPlayer][1] = 4;
	G.discard[thisPlayer][2] = 1;
	G.discard[thisPlayer][3] = 1;
	G.discard[thisPlayer][4] = 4;
	G.discardCount[thisPlayer] = 5;
}
static char * test_smithy() {
	printf("=========== test smity card ============\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	int expectDeckCount = 0;
	if (G.deckCount[thisPlayer] < 3 )
	{
		expectDeckCount = G.discardCount[thisPlayer] + G.deckCount[thisPlayer] - 3;
	}
	else 
	{
		expectDeckCount = G.deckCount[thisPlayer] - 3;
	}
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], expectDeckCount);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("action before = %d, action after = %d\n", testG.numActions, G.numActions);
	mu_assert("-error: handCard number not correct", testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);
	mu_assert("-error: deckCard number not correct", testG.deckCount[thisPlayer] == expectDeckCount);
	mu_assert("-error: coins not correct", testG.coins == G.coins + xtraCoins);
	mu_assert("-error: action not correct", testG.numActions == G.numActions );
	return 0;
}



static char * all_tests() {
	mu_run_test(test_smithy);

	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards

	srand(time(NULL));
	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		generateRandDeckHand();
		all_tests();
		printf("Tests run: %d\n", tests_run);
	}
	return 0;
}
