

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
#include <time.h> // timer set to avoid dead loop
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

/* Arrange the N elements of ARRAY in random order.
Only effective if N is much smaller than RAND_MAX;
if this may not be the case, use a better random
number generator. */
void shuffleDeck(int *array, size_t n)
{
	if (n > 1)
	{
		size_t i;
		for (i = 0; i < n - 1; i++)
		{
			size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
			int t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}

/*for adventurer test
test if 1 card add to hand; this card be discard ; and deck card <= deckcard - 2
if 2 action add to player
check if other status not change: coins
*/
static void generateRandDeck()
{
	initializeGame(numPlayers, k, seed, &G);
	G.deckCount[thisPlayer] = 0;
	int treasure[3] = { 4, 5, 6 };
	int notreasure[3] = { 0, 1, 2 };
	int trCardNum = rand() % 3; // rand a treasure car number;
	int i = 0;
	for (i = 0; i < trCardNum; i++)
	{
		int trCard = rand() % 3;
		G.deck[thisPlayer][i] = treasure[trCard];
		G.deckCount[thisPlayer] += 1;
	}
	int leftCard = 5 - trCardNum; // possible non treasure card number;
	int noTrCardNum = rand() % leftCard;
	for (i = 0; i < noTrCardNum; i++)
	{
		int nontrCard = rand() % 3;
		G.deck[thisPlayer][trCardNum + i] = notreasure[nontrCard];
		G.deckCount[thisPlayer] += 1;
	}
	shuffleDeck(G.deck[thisPlayer], 5);
	// initialize discard card set for 0 card on deck and need to shuffle to get new deck set
	G.discard[thisPlayer][0] = 1;
	G.discard[thisPlayer][1] = 4;
	G.discard[thisPlayer][2] = 1;
	G.discard[thisPlayer][3] = 1;
	G.discard[thisPlayer][4] = 4;
	G.discardCount[thisPlayer] = 5;
	for (i = 0; i < G.deckCount[thisPlayer]; i++)
	{
		printf("deckcard: %d\n", G.deck[thisPlayer][i]);
	}
}



static char * test_adventurer() {
	printf("======== test adventurer card ==========\n");	
	generateRandDeck();
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
	printf("discardcountbefore = %d, discardcountafter =%d\n", G.discardCount[thisPlayer], testG.discardCount[thisPlayer]);
	//function didn't discard this adventure card after play
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newcard -1 );
	printf("coins = %d, expected = %d\n", testG.coins, G.coins);
	printf("action = %d, expected = %d\n", testG.numActions, G.numActions);
	//bug z-1>=0
	mu_assert("-error: card discard not correct", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer] - newcard);
	mu_assert("-error: handcount not correct", testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newcard - 1);
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
	clock_t start = clock(), diff; // timer
	srand(time(NULL));
	// initialize a game state and player cards
	int i = 0;
	for (i = 0; i < 1000; i++)
	{
		all_tests();
		printf("Tests run: %d\n", tests_run);
	}
	

	return 0;
}
