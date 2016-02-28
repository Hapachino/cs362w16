/*
 * unittest3.c
 *
 * business rules
 * unittest3.c for isGameOver() - no bugs found.
 *	1. game is over if supply of province cards is 0
 *	2. game is over if three supply piles are 0
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int main () {
    //int newCards = 0;
    //int discarded = 1;
    //int xtraCoins = 0;
    //int shuffledCards = 0;
    //int i, j, m;
    //int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    //int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
				 sea_hag, tribute, smithy, council_room};
    int r;
    int tmp1, tmp2, tmp3;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("--------- Testing isGameOver() ---------\n");
  
    // province empty test
    tmp1 = supplyCount(province, &testG);
    testG.supplyCount[province] = 0;  
    r = isGameOver(&testG);   
    printf("test 1: province empty\n");
    if( r == 1 )
        printf("pass: expected %d, result %d, game over\n", 1, r);
    else
        printf("FAIL: expected %d, result %d\n", 1, r);
    testG.supplyCount[province] = tmp1;

    // three supply piles empty test
    tmp1 = supplyCount(duchy, &testG);
    tmp2 = supplyCount(estate, &testG);
    tmp3 = supplyCount(silver, &testG);
    testG.supplyCount[duchy] = 0;
    testG.supplyCount[estate] = 0;
    testG.supplyCount[silver] = 0;  
    r = isGameOver(&testG);
    printf("test 2: three supply piles empty\n");
    if( r == 1 )
        printf("pass: expected %d, result %d, game over\n", 1, r);
    else
        printf("FAIL: expected %d, result %d\n", 1, r);
    testG.supplyCount[silver] = tmp3;  

    // two supply piles empty test
    testG.supplyCount[duchy] = 0;
    testG.supplyCount[estate] = 0;
    r = isGameOver(&testG);
    printf("test 3: two supply piles empty\n");
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d, game over\n", 0, r);
    testG.supplyCount[duchy] = tmp1;
    testG.supplyCount[estate] = tmp2;

    // test to make sure game does not end with cards still on pile
    r = isGameOver(&testG);
    printf("test 4: no empty supply piles\n");
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d, game over\n", 0, r);

    // test for any changes in gameState
    printf("test 5: gameState unchanged\n");
    r = memcmp(&G, &testG, sizeof(struct gameState));
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d\n", 0, r);

    return 0;
}
