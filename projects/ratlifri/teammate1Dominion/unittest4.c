/*
 * unittest4.c
 *
 * business rules
 * unittest4.c for fullDeckCount() - no bugs found.
 *	1. count all cards in deck for a player
 *	2. count all cards in hand for a player
 *	3. count all cards in discard for a player
 *	4. return total count
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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
	int testnum = 0;
	int player = 0;
	int count = 0;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("--------- Testing fullDeckCount() ---------\n");
  
	testG.handCount[0] = 5;
	testG.handCount[1] = 5;
	testG.deckCount[0] = 5;
	testG.deckCount[1] = 5;
	testG.discardCount[0] = 5;
	testG.discardCount[1] = 5;

	player = 0;
	testG.hand[player][0] = copper;
	testG.hand[player][1] = silver;
	testG.hand[player][2] = gold;
	testG.hand[player][3] = estate;
	testG.hand[player][4] = duchy;
	testG.deck[player][0] = province;
	testG.deck[player][1] = curse;
	testG.deck[player][2] = adventurer;
	testG.deck[player][3] = feast;
	testG.deck[player][4] = gardens;
	testG.discard[player][0] = mine;
	testG.discard[player][1] = remodel;
	testG.discard[player][2] = smithy;
	testG.discard[player][3] = village;
	testG.discard[player][4] = baron;

    testnum++;
	count = 1;
	r = fullDeckCount(0, copper, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, silver, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, gold, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, estate, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, duchy, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, province, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, curse, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, adventurer, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, feast, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, gardens, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, mine, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, remodel, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, smithy, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, village, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 1;
	r = fullDeckCount(0, baron, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, minion, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, steward, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, tribute, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = estate;
	testG.hand[player][3] = estate;
	testG.hand[player][4] = duchy;
	testG.deck[player][0] = copper;
	testG.deck[player][1] = copper;
	testG.deck[player][2] = estate;
	testG.deck[player][3] = estate;
	testG.deck[player][4] = duchy;
	testG.discard[player][0] = copper;
	testG.discard[player][1] = copper;
	testG.discard[player][2] = estate;
	testG.discard[player][3] = estate;
	testG.discard[player][4] = duchy;

    testnum++;
	count = 6;
	r = fullDeckCount(0, copper, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 6;
	r = fullDeckCount(0, estate, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 3;
	r = fullDeckCount(0, duchy, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, steward, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, tribute, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

	testG.hand[player][0] = copper;
	testG.hand[player][1] = copper;
	testG.hand[player][2] = copper;
	testG.hand[player][3] = copper;
	testG.hand[player][4] = copper;
	testG.deck[player][0] = copper;
	testG.deck[player][1] = copper;
	testG.deck[player][2] = copper;
	testG.deck[player][3] = copper;
	testG.deck[player][4] = copper;
	testG.discard[player][0] = copper;
	testG.discard[player][1] = copper;
	testG.discard[player][2] = copper;
	testG.discard[player][3] = copper;
	testG.discard[player][4] = copper;

    testnum++;
	count = 15;
	r = fullDeckCount(0, copper, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    testnum++;
	count = 0;
	r = fullDeckCount(0, tribute, &testG);
    printf("test %d: fullDeckCount            ", testnum);
    if( r == count )
        printf("pass: expected %d, result %d\n", count, r);
    else
        printf("FAIL: expected %d, result %d\n", count, r);

    return 0;
}
