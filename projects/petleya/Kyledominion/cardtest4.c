/*********************************************************************
** Program Filename: cardtest4.c
** Author: Kyle Johnson
** Date: 2/2/2016
** Description: implementation file for council room card test
*********************************************************************/ 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

//set-up and initialization based on cardtest4.c, week 4 module CS362W16
int main() {
    int newCards = 4;
    int discarded = 1;
	int addBuy = 1;
	int otherCard = 1;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
	int playedCards = 1;
	
	
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing cardtest4: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: +4 cards --------------
	printf("TEST 1: +4 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 4;
	
	//check player hand count
	printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards - discarded);
	if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("PASSED - player hand count matches\n");    
	else 	
        printf("FAILED - player hand count does not match\n");
	
	//check player deck count
	printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - newCards);
	if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards)  
        printf("PASSED - player deck count did not change\n");
    else 
        printf("FAILED - player deck count changed\n");
	
	//check that card is added to played cards count
	printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + playedCards);
	if (testG.playedCardCount == G.playedCardCount + playedCards)
		printf("PASSED - played card count matches\n");
	else
		printf("FAILED - played card count does not match\n");
	
	// ----------- TEST 2: +1 buy --------------
	printf("TEST 2: +1 buy\n");
	
	printf("buy count = %d, expected = %d\n", testG.numBuys , G.numBuys + addBuy);
	if (testG.numBuys == G.numBuys + addBuy)
		printf("PASSED - number of buys matches\n");
	else
		printf("FAILED - number of buys does not match\n");
	
	// ----------- TEST 3: +1 card for next player --------------
	printf("TEST 3: +1 next player card\n");
	
	//check next player hand count
	printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer] + otherCard);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + otherCard)
        printf("PASSED - next player hand count matches\n");    
	else 	
        printf("FAILED - next player hand count does not match\n");
	
	//check next player deck count
	printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - otherCard);
	if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - otherCard)  
        printf("PASSED - next player deck count changes\n");
    else 
        printf("FAILED - next player deck count does not change\n");
	
	//check victory card piles
	printf("estate = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
	if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("PASSED - supply count matches\n");
    else 
        printf("FAILED - supply count does not match\n");
	
	printf("duchy = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
	if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("PASSED - supply count matches\n");
    else 
        printf("FAILED - supply count does not match\n");
	
	printf("province = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
	if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("PASSED - supply count matches\n");
    else 
        printf("FAILED - supply count does not match\n");
	
	printf("council room card testing completed.\n");
	
	return 0;
}