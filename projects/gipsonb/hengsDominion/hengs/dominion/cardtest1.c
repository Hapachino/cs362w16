/* -----------------------------------------------------------------------
 * Test is for smithy()
 *
 * cardtest1
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;

    
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
   
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
	printf("TEST 1: choice1 = 0 = +3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 3;
	xtraCoins = 0;
	printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[player1], G.handCount[player1] + newCards - discarded);
	printf("Player 1 deck count = %d, expected = %d\n", testG.deckCount[player1], G.deckCount[player1] - newCards + shuffledCards);
	printf("Player 1 discard count = %d, expected = %d\n", testG.discardCount[player1], G.discardCount[player1] + 1);
	printf("Player 1 coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	//for player 2
	printf("Player 2 hand count = %d, expected = %d\n", testG.handCount[player2], G.handCount[player2]);
	printf("Player 2 deck count = %d, expected = %d\n", testG.deckCount[player2], G.deckCount[player2]);
	printf("Player 2 discard count = %d, expected = %d\n", testG.discardCount[player2], G.discardCount[player2]);
	if(testG.handCount[player1] == G.handCount[player1] + newCards - discarded){
		printf("\n >>>>>> Success: Handcount of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of current player is incorrect!!!");
	}
	if(testG.handCount[player2] == G.handCount[player2]){
		printf("\n >>>>>> Success: Handcount of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of player2 is incorrect!!!");
	}
	if(testG.deckCount[player1] == G.deckCount[player1] - newCards + shuffledCards){
		printf("\n >>>>>> Success: Deck count of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of current player is incorrect!!!");
	}
	if(testG.deckCount[player2] == G.deckCount[player2]){
		printf("\n >>>>>> Success: Deck count of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of player2 is incorrect!!!");
	}
	if(testG.discardCount[player1] == G.discardCount[player1] + 1){
		printf("\n >>>>>> Success: Discard count of player1 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: discardCount of player1 is incorrect!!!");
	}
	if(testG.discardCount[player2] == G.discardCount[player2]){
		printf("\n >>>>>> Success: Discard count of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: discardCount of player2 is incorrect!!!");
	}
	if(testG.coins == G.coins + xtraCoins){
		printf("\n >>>>>> Success: Coin count of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Coin count of current player is incorrect!!!");
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
