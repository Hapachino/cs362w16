/* Author: Kim McLeod
 * Assignment: 4
 * File: randomtestcard.c
 *
 *
 * smithy - 	receives three cards
 *		discards card in hand
 *
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>


#define TESTCARD "smithy"

int main() {

    int i, error1 = 0, error2 = 0;
    int handpos = 0;    
    int seed = 2000;
    int player = 0;
    int numBefore;
    int numAfter;
    int bonus = 0;
    int card = 0;
    int numPlayers;

	struct gameState G, testG;
	int k[10] = {smithy, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, adventurer, council_room};

	printf("---------------- Random Testing for %s Begin ----------------\n", TESTCARD);
for(i = 0; i < seed; i++){
	player = floor(Random() * 2);
	numPlayers = floor(Random() * MAX_PLAYERS);
	G.deckCount[player] = floor(Random() * MAX_DECK);
	G.discardCount[player] = floor(Random() * MAX_DECK);
	G.handCount[player] = floor(Random() * MAX_HAND);


	// initialize a game state and player cards
	initTestGame(numPlayers, k, seed, &G);


	

	/*************** TEST 1: User gets +3 cards ***********/
	


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card
	gainCard(smithy,&testG,2,player);


	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);


	endTurn(&testG);


	// test passes if number of cards in hand is 3 more
	// than start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(numAfter != (numBefore + 3 - 1))
	{	printf("Error 1 'User gains 3 cards' Expected: %d, Actual %d\n", (numBefore + 3 - 1), numAfter);
		error1++;
		
	}





	/*************** TEST 2: User discards card in hand ***********/
	

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player smithy card
	gainCard(smithy,&testG,2,player);


	// record number of cards before and after smithy is played
	numBefore = numHandCards(&testG);
	cardEffect(card, 0, 0, 0, &testG, handpos, &bonus);
	numAfter = numHandCards(&testG);

	endTurn(&testG);

	// test passes if number of cards in hand is 3 more
	// than start, minus one discarded
	// this will fail due to alterations in the dominion.c code
	if(&testG.discardCount[player] != &G.discardCount[player])
	{	printf("Error 2 'User discards smithy card' Expected: %d, Actual: %d\n", &G.discardCount[player], &testG.discardCount[player]);
		error2++;
		
	}



    }


	printf("\n >>>>> SUCCESS: Testing complete for %s <<<<<\n\n", TESTCARD);
    

	printf("Error 1 'User gains 3 cards' Failed %d of %d times\n", error1, seed); 
	printf("Error 2 'User discards smithy card' Failed %d of %d times\n\n\n\n", error2, seed);

	return 0;
}

