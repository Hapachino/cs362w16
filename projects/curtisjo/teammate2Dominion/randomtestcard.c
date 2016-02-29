/*
 * Author: Joshua Curtis
 * randomtestcard.c
 * Random test for the Smithy card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
    struct gameState G;
    struct gameState testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int seed = 1000;
	int i; 			//iterator for for loop
    int curPlayer = 0;
    int otherPlayer = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int newCards = 3;
    int testNum = 0;
	int handPassed = 0; //counter for correct currentPlayer handCount
	int deckPassed = 0; //counter for correct currentPlayer deckCount
	int otherHandPassed = 0; //counter for correct otherPlayer handCount
	int otherDeckPassed = 0; //counter for correct otherPlayer handCount
	int randHand, randDeck; //variable to store random number of currentPlayer handCount and deckCount
	int negRandHand = 0; // Counter for handCount > 500
	int negDeckHand = 0; // counter for deckCount > 500
	int overRandHand = 0; // counter for handCount < 0
	int overDeckHand = 0; // counter for deckCount < 0
	int zeroHand = 0; // counter for handCount == 0
	int zeroDeck = 0; // counter for deckCount == 0
	time_t t;
	
	// Initialize random number generator for testing
	srand((unsigned) time(&t));
	printf("---------- Testing smithy card ----------\n"); 
for (i = 0; i <100000; i++) {	
    // initialize the game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
	
	// Generate random number of cards for testG hand
	randHand = rand() % MAX_HAND - 1;
	randDeck = rand() % MAX_DECK - 1;
	//printf("randHand: %d\n", randHand);
	//printf("randDeck: %d\n", randDeck);
	if (randHand < 0)
		negRandHand++;
	if (randDeck < 0)
		negDeckHand++;
	if (randHand == 0)
		zeroHand++;
	if (randDeck == 0)
		zeroDeck++;
	
	testG.handCount[curPlayer] = randHand;
	testG.deckCount[curPlayer] = randDeck;
   
    //play smithy card on testG check handCount
    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
  if ( testG.handCount[curPlayer] == G.handCount[curPlayer] + newCards){
		//printf("handCount: Passed\n");
		handPassed++;
	}
	else
		//printf("handCount: Failed\n");
    //check adventure card on testG check deckCount
    if ( testG.deckCount[curPlayer] <= G.deckCount[curPlayer]) {
		//printf("deckCount: Passed\n");
		deckPassed++;
	}
	else
		//printf("deckCount: Failed\n");
    //check that other players state is not changed
    if ( testG.handCount[otherPlayer] == G.handCount[otherPlayer]) {
		//printf("otherPlayer handCount: Passed\n");
		otherHandPassed++;
	}
	else
		//printf("otherPlayer handCount: Failed\n");
	//check adventure card on testG check deckCount
    if ( testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]) {
		//printf("otherPlayer deckCount: Passed\n");
		otherDeckPassed++;
	}
	else
		//printf("otherPlayer deckCount: Failed\n");
	testNum++;
}
	printf("Total Tests: %d\n", testNum);
	printf("handCount Passed: %d\n", handPassed);
	printf("deckCount Passed: %d\n", deckPassed);
	printf("otherPlayer handCount Passed: %d\n", otherHandPassed);
	printf("otherPlayer deckCount Passed: %d\n", otherDeckPassed);
	printf("negRandHand: %d\n", negRandHand);
	printf("negDeckHand: %d\n", negDeckHand);
	printf("zeroHand: %d\n", zeroHand);
	printf("zeroHand: %d\n", zeroDeck);

    return 0;
}