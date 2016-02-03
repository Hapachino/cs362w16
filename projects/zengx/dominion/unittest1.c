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

/*for discard Card
for each handpos(0 <=handpos <= 4)
check if played pile add correctly; played count
check if handcard count correct
check if deckcard count correct
check if hand pos in vliad
check other coins not change
*/

//if trashFlag is not on : trashflag == 0;
static char * test_discardCard_notrash() {
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int countdiscard = 1;
	for (int handPos = 0; handPos < 5; handPos++)
	{

		discardCard(handPos, currentPlayer, &testG, 0);
		printf("handPos = %d\n", handPos);
		printf("hand count reduce = %d, played count add = %d\n", G.handCount[thisPlayer] - testG.handCount[thisPlayer],  testG.playedCardCount - G.playedCardCount);
		printf("lastone in played pile = %d, discardCard = %d\n", testG.playedCards[testG.playedCardCount -1], G.hand[thisPlayer][handPos]);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		printf("action before = %d, action after = %d\n", testG.numActions, G.numActions);
		mu_assert("-error: handCard number not correct\n", G.handCount[thisPlayer] - testG.handCount[thisPlayer] == testG.playedCardCount - G.playedCardCount);
		mu_assert("-error:add to played pile incorrect\n", testG.playedCards[testG.playedCardCount -1] == G.hand[thisPlayer][handPos]);
		mu_assert("-error: deckCard number not correct\n", testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
		mu_assert("-error: coins not correct\n", testG.coins == G.coins + xtraCoins);
		mu_assert("-error: action not correct\n", testG.numActions == G.numActions);
	}
	return 0;
}

static char * test_discardCard_trash()
{
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int countdiscard = 1;
	for (int handPos = 0; handPos < testG.handCount[thisPlayer]; handPos++)
	{

		discardCard(handPos, currentPlayer, &testG, 1);
		printf("handPos = %d\n", handPos);
		printf("hand count reduce = %d, discard add = %d\n", G.handCount[thisPlayer] - testG.handCount[thisPlayer], testG.discardCount[thisPlayer] - G.discardCount[thisPlayer]);
		printf("playedcard = %d\n", testG.playedCardCount);
		printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		printf("action before = %d, action after = %d\n", testG.numActions, G.numActions);
		mu_assert("-error: handCard to discard number not correct\n", G.handCount[thisPlayer] - testG.handCount[thisPlayer] == testG.playedCardCount - G.playedCardCount);
		mu_assert("-error: playedCard change", testG.playedCardCount == G.playedCardCount);
		mu_assert("-error: deckCard number not correct\n", testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);
		mu_assert("-error: coins not correct\n", testG.coins == G.coins + xtraCoins);
		mu_assert("-error: action not correct\n", testG.numActions == G.numActions);
	}
	return 0;
}

static char * all_tests() {
	mu_run_test(test_discardCard_trash);
	mu_run_test(test_discardCard_notrash);
	

	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();
	
	printf("Tests run: %d\n", tests_run);

	return 0;
}