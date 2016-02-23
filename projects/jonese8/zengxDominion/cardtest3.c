

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

#define TESTCARD "village"

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

/*for village test
test if 1 card add to hand; this card be discard ; and deck card -1
if 2 action add to player
check if other status not change: coins
*/
static char * test_village() {
	printf("============ test village card ============\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 1;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	printf("action before = %d, action after = %d\n", testG.numActions, G.numActions + 2);
	mu_assert("-error: handCard number not correct", testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);
	mu_assert("-error: deckCard number not correct", testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	mu_assert("-error: coins not correct", testG.coins == G.coins + xtraCoins);
	mu_assert("-error: action not correct", testG.numActions == G.numActions + 2);
	return 0;
}



static char * all_tests() {
	mu_run_test(test_village);

	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();
	printf("Tests run: %d\n", tests_run);

	return 0;
}
