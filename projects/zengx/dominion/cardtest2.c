

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

#define TESTCARD "adventurer"

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
int temphand[MAX_HAND];
int cardDrawn = 0;
int z = 0;
int drawntreasure = 0;
int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
sea_hag, tribute, smithy, council_room };


/*for adventurer test
test if 1 card add to hand; this card be discard ; and deck card <= deckcard - 2
if 2 action add to player
check if other status not change: coins
*/
static char * test_adventurer() {
	printf("======== test adventurer card ==========\n");	
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	int lastone = testG.hand[testG.handCount[thisPlayer] - 1];
	int lasttwo = testG.hand[testG.handCount[thisPlayer] - 2];
	int istreasure = 0;
	if ((lastone == gold || lastone == copper || lastone == silver) && (lasttwo == gold || lasttwo == copper || lasttwo == silver))
	{
		istreasure = 1;
	}
	int newcard = 2;
	int discardNum = 3;
	printf("discardcountbefore = %d, discardcountafter =%d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newcard -1 );
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	printf("action = %d, expected = %d\n", testG.numActions, G.numActions);
	mu_assert("-error: card discard not correct", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer] - discardNum);
	mu_assert("-error: last 2 cards not treasure", istreasure == 1);
	mu_assert("-error: coins not correct", testG.coins == G.coins );
	mu_assert("-error: action not correct", testG.numActions == G.numActions);
	return 0;
}



static char * all_tests() {
	mu_run_test(test_adventurer);

	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	G.deck[thisPlayer][0] = 1;
	G.deck[thisPlayer][1] = 4;
	G.deck[thisPlayer][2] = 1;
	G.deck[thisPlayer][3] = 1;
	G.deck[thisPlayer][4] = 4;


	all_tests();
	printf("Tests run: %d\n", tests_run);

	return 0;
}
