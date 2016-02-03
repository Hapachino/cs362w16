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

/*for updateCoin
check the treasure card in hand if they all add to coins
check if add bouns
check after updateCoin no hand card change.

*/

//if bouns == 0; 
static char * test_treasureCard_coinNum()
{
	// All gold
	int i = 0;
	for (; i < 5; i++)
	{
		G.hand[thisPlayer][i] = gold;
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer =  whoseTurn(&G);
	updateCoins(currentPlayer, &testG, 0);
	int coinsAdd = 3*5;
		printf("handcard[0] = %d\n", testG.hand[thisPlayer][0]);
		printf("handcard[1] = %d\n", testG.hand[thisPlayer][1]);
		printf("handcard[2] = %d\n", testG.hand[thisPlayer][2]);
		printf("handcard[3] = %d\n", testG.hand[thisPlayer][3]);
		printf("handcard[4] = %d\n", testG.hand[thisPlayer][4]);
		printf("coin expected =%d\n", testG.coins);
		mu_assert("-error: coin not correct", testG.coins == coinsAdd);
		// All silver
		
		for (i = 0; i < 5; i++)
		{
			G.hand[thisPlayer][i] = silver;
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		currentPlayer = whoseTurn(&G);
		updateCoins(currentPlayer, &testG, 0);
		coinsAdd = 2 * 5;
		printf("handcard[0] = %d\n", testG.hand[thisPlayer][0]);
		printf("handcard[1] = %d\n", testG.hand[thisPlayer][1]);
		printf("handcard[2] = %d\n", testG.hand[thisPlayer][2]);
		printf("handcard[3] = %d\n", testG.hand[thisPlayer][3]);
		printf("handcard[4] = %d\n", testG.hand[thisPlayer][4]);
		printf("coin expected =%d\n", testG.coins);
		mu_assert("-error: coin not correct", testG.coins == coinsAdd);
		// All copper
		for (i = 0; i < 5; i++)
		{
			G.hand[thisPlayer][i] = copper;
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		currentPlayer = whoseTurn(&G);
		updateCoins(currentPlayer, &testG, 0);
		 coinsAdd = 1 * 5;
		printf("handcard[0] = %d\n", testG.hand[thisPlayer][0]);
		printf("handcard[1] = %d\n", testG.hand[thisPlayer][1]);
		printf("handcard[2] = %d\n", testG.hand[thisPlayer][2]);
		printf("handcard[3] = %d\n", testG.hand[thisPlayer][3]);
		printf("handcard[4] = %d\n", testG.hand[thisPlayer][4]);
		printf("coin expected =%d\n", testG.coins);
		mu_assert("-error: coin not correct", testG.coins == coinsAdd);
		// none
		for (i = 0; i < 5; i++)
		{
			G.hand[thisPlayer][i] = 0;
		}
		memcpy(&testG, &G, sizeof(struct gameState));
		currentPlayer = whoseTurn(&G);
		updateCoins(currentPlayer, &testG, 0);
		coinsAdd = 0 * 5;
		printf("handcard[0] = %d\n", testG.hand[thisPlayer][0]);
		printf("handcard[1] = %d\n", testG.hand[thisPlayer][1]);
		printf("handcard[2] = %d\n", testG.hand[thisPlayer][2]);
		printf("handcard[3] = %d\n", testG.hand[thisPlayer][3]);
		printf("handcard[4] = %d\n", testG.hand[thisPlayer][4]);
		printf("coin expected =%d\n", testG.coins);
		mu_assert("-error: coin not correct", testG.coins == coinsAdd);

	
	return 0;
}
// if bounus add
static char * test_bounus()
{
	printf("add bounus from -100 to 100");
	int bounus = 0;
	int i = 0;
	for (; i < 5; i++)
	{
		G.hand[thisPlayer][i] = 0;
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&G);
	for (bounus = -100; bounus < 100; bounus++)
	{
		updateCoins(currentPlayer, &testG, bounus);
		mu_assert("-error: bounus not correct add to", testG.coins == bounus);
	}
	return 0;

}

// if checkhand card
static char * test_handcard()
{
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = whoseTurn(&G);
	updateCoins(currentPlayer, &testG, 0);
	printf("handcard Before = %d, handcard[0] = %d\n", G.hand[thisPlayer][0], testG.hand[thisPlayer][0]);
	printf("handcard Before = %d, handcard[1] = %d\n", G.hand[thisPlayer][1], testG.hand[thisPlayer][1]);
	printf("handcard Before = %d, handcard[2] = %d\n", G.hand[thisPlayer][2], testG.hand[thisPlayer][2]);
	printf("handcard Before = %d, handcard[3] = %d\n", G.hand[thisPlayer][3], testG.hand[thisPlayer][3]);
	printf("handcard Before = %d, handcard[4] = %d\n", G.hand[thisPlayer][4], testG.hand[thisPlayer][4]);
	mu_assert("-error: handcard0 changed", G.hand[thisPlayer][0] == testG.hand[thisPlayer][0]);
	mu_assert("-error: handcard1 changed", G.hand[thisPlayer][1] == testG.hand[thisPlayer][1]);
	mu_assert("-error: handcard2 changed", G.hand[thisPlayer][2] == testG.hand[thisPlayer][2]);
	mu_assert("-error: handcard3 changed", G.hand[thisPlayer][3] == testG.hand[thisPlayer][3]);
	mu_assert("-error: handcard4 changed", G.hand[thisPlayer][4] == testG.hand[thisPlayer][4]);
	return 0;

}


static char * all_tests() {
	printf("=============test update coin =========");
	mu_run_test(test_treasureCard_coinNum);
	mu_run_test(test_bounus);
	mu_run_test(test_handcard);



	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();

	printf("Tests run: %d\n", tests_run);

	return 0;
}
