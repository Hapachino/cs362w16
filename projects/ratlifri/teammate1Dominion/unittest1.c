/*
 * unittest1.c
 *
 * unittest1.c for getCost()
 *	1. get the cost to buy/gain a card, return integer of cost like 2,3,4,etc.
 *	2. for cards in dominion system not in the simulation set, return -1 
 *
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int cost;
	int cardnum = 0;
	int testnum = 1;

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("--------- Testing getCost() ---------\n");
  
	// compare game state for differences
    testnum = 1;
    printf("test %d: gameState comparison      ", testnum);
    r = memcmp(&G, &testG, sizeof(struct gameState));
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d\n", 0, r);

	// test cost of card curse
    testnum++;
	cardnum = 0;
    cost = 0;
    printf("test %d: curse                     ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card estate
    testnum++;
	cardnum++;
    cost = 2;
    printf("test %d: estate                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card duchy
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: duchy                     ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card province
    testnum++;
	cardnum++;
    cost = 8;
    printf("test %d: province                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card copper
    testnum++;
	cardnum++;
    cost = 0;
    printf("test %d: copper                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card silver
    testnum++;
	cardnum++;
    cost = 3;
    printf("test %d: silver                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card gold
    testnum++;
	cardnum++;
    cost = 6;
    printf("test %d: gold                      ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card adventurer
    testnum++;
	cardnum++;
    cost = 6;
    printf("test %d: adventurer                ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card council_room
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: council_room             ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card feast
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: feast                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card gardens
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: gardens                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card mine
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: mine                     ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card remodel
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: remodel                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card smithy
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: smithy                   ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card village
    testnum++;
	cardnum++;
    cost = 3;
    printf("test %d: village                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card baron
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: baron                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card great_hall
    testnum++;
	cardnum++;
    cost = 3;
    printf("test %d: great_hall               ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card minion
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: minion                   ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card steward
    testnum++;
	cardnum++;
    cost = 3;
    printf("test %d: steward                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card tribute
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: tribute                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card ambassador
    testnum++;
	cardnum++;
    cost = 3;
    printf("test %d: ambassador               ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card cutpurse
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: cutpurse                 ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card embargo
    testnum++;
	cardnum++;
    cost = 2;
    printf("test %d: embargo                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card outpost
    testnum++;
	cardnum++;
    cost = 5;
    printf("test %d: outpost                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card salvager
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: salvager                 ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card sea_hag
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: sea_hag                  ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card treasure_map
    testnum++;
	cardnum++;
    cost = 4;
    printf("test %d: treasure_map             ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card spy - this one should return -1
    testnum++;
	cardnum++;
    cost = -1;
    printf("test %d: spy                      ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card thief - this one should return -1
    testnum++;
	cardnum++;
    cost = -1;
    printf("test %d: thief                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// test cost of card witch - this one should return -1
    testnum++;
	cardnum++;
    cost = -1;
    printf("test %d: witch                    ", testnum);
    r = getCost(cardnum);   
    if( r == cost )
        printf("pass: expected %d, result %d\n", cost, r);
    else
        printf("FAIL: expected %d, result %d\n", cost, r);

	// compare game state for differences
    testnum++;
    printf("test %d: gameState unchanged      ", testnum);
    r = memcmp(&G, &testG, sizeof(struct gameState));
    if( r == 0 )
        printf("pass: expected %d, result %d\n", 0, r);
    else
        printf("FAIL: expected %d, result %d\n", 0, r);

    return 0;
}
