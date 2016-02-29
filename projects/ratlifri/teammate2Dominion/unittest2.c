/*
 * unittest2.c
 *
 * business rules
 * unittest2.c for updateCoins()
 *	1. add coin value of all treasure cards and bonus.
 *	2. add 1 for copper treasure cards.
 *	3. add 2 for silver treasure cards.
 *	4. add 3 for gold treasure cards.
 *	5. add bonus (passed in as parameter).
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

int compareStates(struct gameState *s1, struct gameState *s2) {

	int i;
	int compare;

	if ( s1->numPlayers == s2->numPlayers ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for      numPlayers:  G = %d      testG = %d\n", compare, s1->numPlayers, s2->numPlayers );
	if ( s1->outpostPlayed == s2->outpostPlayed ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for   outpostPlayed:  G = %d      testG = %d\n", compare, s1->outpostPlayed, s2->outpostPlayed );
	if ( s1->outpostTurn == s2->outpostTurn ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for     outpostTurn:  G = %d      testG = %d\n", compare, s1->outpostTurn, s2->outpostTurn );
	if ( s1->whoseTurn == s2->whoseTurn ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for       whoseTurn:  G = %d      testG = %d\n", compare, s1->whoseTurn, s2->whoseTurn );
	if ( s1->phase == s2->phase ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for           phase:  G = %d      testG = %d\n", compare, s1->phase, s2->phase );
	if ( s1->numActions == s2->numActions ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for      numActions:  G = %d      testG = %d\n", compare, s1->numActions, s2->numActions );
	if ( s1->coins == s2->coins ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for           coins:  G = %d      testG = %d\n", compare, s1->coins, s2->coins );
	if ( s1->numBuys == s2->numBuys ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for         numBuys:  G = %d      testG = %d\n", compare, s1->numBuys, s2->numBuys );
	if ( s1->playedCardCount == s2->playedCardCount ) { 
		compare = 1;
	} else {
		compare = 0;
	}
    printf("compare = %d for playedCardCount:  G = %d      testG = %d\n", compare, s1->playedCardCount, s2->playedCardCount );
	for (i = 0; i < sizeof(s1->supplyCount)/sizeof(int); i++) {
		if ( s1->supplyCount[i] == s2->supplyCount[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for     supplyCount:  G = %d      testG = %d\n", compare, s1->supplyCount[i], s2->supplyCount[i] );
	}
	for (i = 0; i < sizeof(s1->embargoTokens)/sizeof(int); i++) {
		if ( s1->embargoTokens[i] == s2->embargoTokens[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for   embargoTokens:  G = %d      testG = %d\n", compare, s1->embargoTokens[i], s2->embargoTokens[i] );
	}
	for (i = 0; i < sizeof(s1->handCount)/sizeof(int); i++) {
		if ( s1->handCount[i] == s2->handCount[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for       handCount:  G = %d      testG = %d\n", compare, s1->handCount[i], s2->handCount[i] );
	}
	for (i = 0; i < sizeof(s1->deckCount)/sizeof(int); i++) {
		if ( s1->deckCount[i] == s2->deckCount[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for       deckCount:  G = %d      testG = %d\n", compare, s1->deckCount[i], s2->deckCount[i] );
	}
	for (i = 0; i < sizeof(s1->discardCount)/sizeof(int); i++) {
		if ( s1->discardCount[i] == s2->discardCount[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for       discardCount:  G = %d      testG = %d\n", compare, s1->discardCount[i], s2->discardCount[i] );
	}
	for (i = 0; i < sizeof(s1->playedCards)/sizeof(int); i++) {
		if ( s1->playedCards[i] == s2->playedCards[i] ) { 
			compare = 1;
		} else {
			compare = 0;
		}
		printf("compare = %d for       playedCards:  G = %d      testG = %d\n", compare, s1->playedCards[i], s2->playedCards[i] );
	}

	return 0;
}

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
	int testnum = 1;
	int player = 0;
	int coin = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("--------- Testing updateCoins() ---------\n");
  
	// compare game state for differences
    testnum = 1;
    printf("test %d: gameState comparison      ", testnum);
    r = memcmp(&G, &testG, sizeof(struct gameState));
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d\n", 0, r);

	testG.handCount[0] = 5;
	testG.handCount[1] = 5;

	// test five coppers
	player = 0;
	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = copper;
	testG.hand[player][3] = copper;
	testG.hand[player][4] = copper;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 5;
	r = testG.coins;
    printf("test %d: five coppers             ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five silver
	player = 0;
	testG.hand[player][0] = silver;
	testG.hand[player][1] = silver;
	testG.hand[player][2] = silver;
	testG.hand[player][3] = silver;
	testG.hand[player][4] = silver;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 10;
	r = testG.coins;
    printf("test %d: five silver              ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five gold
	player = 0;
	testG.hand[player][0] = gold;
	testG.hand[player][1] = gold;
	testG.hand[player][2] = gold;
	testG.hand[player][3] = gold;
	testG.hand[player][4] = gold;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 15;
	r = testG.coins;
    printf("test %d: five gold                ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five coppers
	player = 0;
	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = copper;
	testG.hand[player][3] = copper;
	testG.hand[player][4] = copper;
	updateCoins(player, &testG, 3);

    testnum++;
	coin = 8;
	r = testG.coins;
    printf("test %d: five coppers and bonus 3 ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five silver
	player = 0;
	testG.hand[player][0] = silver;
	testG.hand[player][1] = silver;
	testG.hand[player][2] = silver;
	testG.hand[player][3] = silver;
	testG.hand[player][4] = silver;
	updateCoins(player, &testG, 1);

    testnum++;
	coin = 11;
	r = testG.coins;
    printf("test %d: five silver and bonus 1  ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five gold and a bonus 2
	player = 0;
	testG.hand[player][0] = gold;
	testG.hand[player][1] = gold;
	testG.hand[player][2] = gold;
	testG.hand[player][3] = gold;
	testG.hand[player][4] = gold;
	updateCoins(player, &testG, 2);

    testnum++;
	coin = 17;
	r = testG.coins;
    printf("test %d: five gold and bonus 2    ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five coppers - player 2
	player = 1;
	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = copper;
	testG.hand[player][3] = copper;
	testG.hand[player][4] = copper;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 5;
	r = testG.coins;
    printf("test %d: p2 five coppers          ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five silver - player 2
	player = 1;
	testG.hand[player][0] = silver;
	testG.hand[player][1] = silver;
	testG.hand[player][2] = silver;
	testG.hand[player][3] = silver;
	testG.hand[player][4] = silver;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 10;
	r = testG.coins;
    printf("test %d: p2 five silver           ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five gold - player 2
	player = 1;
	testG.hand[player][0] = gold;
	testG.hand[player][1] = gold;
	testG.hand[player][2] = gold;
	testG.hand[player][3] = gold;
	testG.hand[player][4] = gold;
	updateCoins(player, &testG, 0);

    testnum++;
	coin = 15;
	r = testG.coins;
    printf("test %d: p2 five gold             ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five coppers and bonus 3 - player 2
	player = 1;
	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = copper;
	testG.hand[player][3] = copper;
	testG.hand[player][4] = copper;
	updateCoins(player, &testG, 3);

    testnum++;
	coin = 8;
	r = testG.coins;
    printf("test %d: p2 five coppers and bonus 3 ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five silver and bonus 1 - player 2
	player = 1;
	testG.hand[player][0] = silver;
	testG.hand[player][1] = silver;
	testG.hand[player][2] = silver;
	testG.hand[player][3] = silver;
	testG.hand[player][4] = silver;
	updateCoins(player, &testG, 1);

    testnum++;
	coin = 11;
	r = testG.coins;
    printf("test %d: p2 five silver and bonus 1  ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

	// test five gold and a bonus 2 - player 2
	player = 1;
	testG.hand[player][0] = gold;
	testG.hand[player][1] = gold;
	testG.hand[player][2] = gold;
	testG.hand[player][3] = gold;
	testG.hand[player][4] = gold;
	updateCoins(player, &testG, 2);

    testnum++;
	coin = 17;
	r = testG.coins;
    printf("test %d: p2 five gold and bonus 2    ", testnum);
    if( r == coin )
        printf("pass: expected %d, result %d\n", coin, r);
    else
        printf("FAIL: expected %d, result %d\n", coin, r);

    // test game state - expect a difference for coins
    testnum++;
    printf("test %d: gameState coins changed  ", testnum);
    r = memcmp(&G, &testG, sizeof(struct gameState));
    if( r == 0 )
        printf("FAIL: expected %d, result %d\n", 0, r);
    else
        printf("pass: expected %d, result %d\n", 0, r);

	// compareStates( &G, &testG );

    return 0;
}
