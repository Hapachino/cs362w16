/*********************************************************************
** Program Filename: randomtestadventurer.c
** Author: Kyle Johnson
** Date: 2/14/2016
** Description: implementation file for random testing of village card
*********************************************************************/ 
/*
Please note: this will run with normal dominion.c and dominion.h, 
but leads to core dump on my modified/re factored version.  Will redo
if time is sufficient
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "math.h" 

#define TESTCARD "adventurer"

//set-up and initialization based on cardtest4.c, week 4 module CS362W16
int main() {
    int newCards = 0;
    int discarded = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
	int playedCards = 1;
	int i, j, l;
	//int card;
	int pHandCount = 0;
	int pDeckCount = 0;
	int nHandCount = 0;
	int nDeckCount = 0;
	int playedCount = 0;
	int victoryCount = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing: %s ----------------\n", TESTCARD);
	printf("Failure Descriptions\n");
	
	for (i = 0; i < 10000; i++) 
	{	
		seed = rand();
		// ----------- TEST 1: +2 cards --------------
		for (l = 0; l < sizeof(struct gameState); l++)
			((char*)&G)[l] = floor(Random() * 256);
		
		// initialize a random game state and random number of cards
		initializeGame(numPlayers, k, seed, &G);
		G.handCount[currentPlayer] = floor(Random() * 15);
		G.deckCount[currentPlayer] = floor(Random() * 50 + 2);
		G.discardCount[currentPlayer] = floor(Random() * 25);
		
		G.handCount[nextPlayer] = floor(Random() * 15);
		G.deckCount[nextPlayer] = floor(Random() * 50 + 2);
		
		/*
		//random hand cards from cards in game
		for (j = 0; j < G.handCount[currentPlayer]; j++) 
		{
			card = floor(Random() * 10);
			G.hand[currentPlayer][j] = k[card];
		}
		
		//random discard cards from cards in game
		for (j = 0; j < G.discardCount[currentPlayer]; j++)
		{
			card = floor(Random() * 10);
			G.discard[currentPlayer][j] = k[card];
		}		
	
		//random deck cards from cards in game
		for (j = 0; j < G.deckCount[currentPlayer]; j++) 
		{
			card = floor(Random() * 10);
			G.deck[currentPlayer][j] = k[card];
		}
		*/
		
		for (j = 0; j < G.handCount[currentPlayer]; j++) 
			G.hand[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		
		for (j = 0; j < G.discardCount[currentPlayer]; j++) 
			G.discard[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		
		for (j = 0; j < G.deckCount[currentPlayer]; j++) 
			G.deck[currentPlayer][j] = floor(Random() * (treasure_map + 1));
		
		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
		newCards = 2;
		
		//check player hand count
		if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + newCards - discarded)
		{
			printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + newCards - discarded);
			pHandCount++;
		}
		
		//check player deck count
		if (testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer] != G.deckCount[currentPlayer] - newCards)
		{
			printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer] + testG.discardCount[currentPlayer], G.deckCount[currentPlayer] - newCards);
			pDeckCount++;
		}
		
		//check next player hand count
		if (testG.handCount[nextPlayer] != G.handCount[nextPlayer])
		{
			printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
			nHandCount++;
		}	
		
		//check next player deck count
		if (testG.deckCount[nextPlayer] != G.deckCount[nextPlayer])
		{
			printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
			nDeckCount++;
		}
			
		//check that card is added to played cards count
		
		if (testG.playedCardCount != G.playedCardCount + playedCards)
		{
			printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + playedCards);
			playedCount++;
		}
	
		//check victory card piles
		if (testG.supplyCount[estate] != G.supplyCount[estate])  
		{
			printf("estate = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
			victoryCount++;
		}
		
		if (testG.supplyCount[duchy] != G.supplyCount[duchy])  
		{
			printf("duchy = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
			victoryCount++;
		}
		
		if (testG.supplyCount[province] != G.supplyCount[province])  
		{
			printf("province = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
			victoryCount++;
		}
	}
	//print sum of errors for each test type
	printf("adventurer card random testing completed.\n");
		printf("-------------------------------------------\n");
		printf("Results Summary (10,000 runs):\n");
		printf("-------------------------------------------\n");
		printf("Player hand count failures: %d\n",pHandCount);
		printf("Player deck count failures: %d\n",pDeckCount);
		printf("Next player hand count failures: %d\n",nHandCount);
		printf("Next player deck count failures: %d\n",nDeckCount);
		printf("Played card count failures: %d\n",playedCount);
		printf("Victory card supply failures: %d\n\n",victoryCount);
		return 0;
}
	
	