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

/*for isgame over
if province is 0 but supply no 0
 supply has 1 0
 supply has 2 0
 supply has 3 0
 supply has 4 0

 if province is not 0
 supply has 1 0
 supply has 2 0
 supply has 3 0
 supply has 4 0


*/

//if province == 0; 
static char * test_hasprovince()
{
	printf("========== test has province ============\n");
	printf("when  1 province with no supply 0\n");
	int i = 0;
	for (i = 0; i < 25; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[province] = 1;
	memcpy(&testG, &G, sizeof(struct gameState));
	int gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when 2 province with 1 supply 0\n");
	for (i = 0; i < 24; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[province] = 2;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when 3 province with 2 supply 0\n");
	for (i = 0; i < 23; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	G.supplyCount[province] = 3;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when 4 province with 3 supply 0\n");
	for (i = 0; i < 22; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	G.supplyCount[22] = 0;
	G.supplyCount[province] = 4;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when 5 province with 3 supply 0\n");
	for (i = 0; i < 21; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	G.supplyCount[22] = 0;
	G.supplyCount[21] = 0;
	G.supplyCount[province] = 5;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);
	

	return 0;
}

static char * test_noprovince()
{
	printf("========== test has no province ============\n");
	printf("when no province with no supply 0\n");
	int i = 0;
	for (i = 0; i < 25; i++)
	{
		G.supplyCount[i] = 1;
	}
	memcpy(&testG, &G, sizeof(struct gameState));
	int gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);
	printf("when no province with 1 supply 0 \n");
	for (i = 0; i < 24; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when no province with 2 supply 0\n");
	for (i = 0; i < 23; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when no province with 3 supply 0\n");
	for (i = 0; i < 22; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	G.supplyCount[22] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);

	printf("when no province with 3 supply 0\n");
	for (i = 0; i < 21; i++)
	{
		G.supplyCount[i] = 1;
	}
	G.supplyCount[24] = 0;
	G.supplyCount[23] = 0;
	G.supplyCount[22] = 0;
	G.supplyCount[21] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));
	gameover = isGameOver(&testG);
	mu_assert("Game status not correct", gameover = 1);


	return 0;
}


static char * all_tests() {
	printf("=============test isGameOver =========\n");
	mu_run_test(test_noprovince);
	mu_run_test(test_hasprovince);




	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();

	printf("Tests run: %d\n", tests_run);

	return 0;
}