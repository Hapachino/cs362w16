/* -----------------------------------------------------------------------
 * Test is for adventurer()
 *
 * cardtest2
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
   
    int i;
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

	
	printf("TEST 1: choice1 = 0 = Reveal 2 treasure cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


	printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[player1], G.handCount[player1] + 2 - 1);


	printf("Player 1 deck count = %d, expected = %d\n", testG.deckCount[player1], G.deckCount[player1] - (testG.discardCount[player1] + 2));
	
	printf("Player 1 discard count = %d, expected = %d\n", testG.discardCount[player1], G.discardCount[player1] + 1);
	int coinCardsTest = 0;
	for(i=0; i < sizeof(testG.hand); i++){
		if(testG.hand[player1][i] == gold || testG.hand[player1][i] == silver || testG.hand[player1][i] == copper){
			coinCardsTest++;
		}
	}
	int coinCardsG = 0;
	for(i=0; i < sizeof(G.hand); i++){
		if(G.hand[player1][i] == gold || G.hand[player1][i] == silver || G.hand[player1][i] == copper){
			coinCardsG++;
		}
	}

	printf("Player 1 hand Treasure count = %d, expected = %d\n", coinCardsTest, coinCardsG + 2);


	//for player 2
	printf("Player 2 hand count = %d, expected = %d\n", testG.handCount[player2], G.handCount[player2]);
	printf("Player 2 deck count = %d, expected = %d\n", testG.deckCount[player2], G.deckCount[player2]);
	

	//HandCount
	if(testG.handCount[player1] == G.handCount[player1] + 2 - 1){
		printf("\n >>>>>> Success: Handcount of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of current player is incorrect!!!");
	}
	//Deck Count, might be plus 2
	if(testG.deckCount[player1] == G.deckCount[player1] - (testG.discardCount[player1] + 1)){
		printf("\n >>>>>> Success: Deck count of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of current player is incorrect!!!");
	}

	//Discard count
	if(testG.discardCount[player1] >= G.discardCount[player1] + 1){
		printf("\n >>>>>> Success: Discard count of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Discard count of current player is incorrect!!!");
	}
	//Coin Count
	if(testG.coins > G.coins){
		printf("\n >>>>>> Success: Coin count of player1 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Coin count of player1 is incorrect!!!");
	}
	
	if(coinCardsTest == coinCardsG + 2){
		printf("\n >>>>>> Success: Treasure Handcount of player1 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Treasure Handcount of player1 is incorrect!!!");
	}
	//Player 2 Hand Count
	if(testG.handCount[player2] == G.handCount[player2]){
		printf("\n >>>>>> Success: Handcount of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of player2 is incorrect!!!");
	}
	//Player 2 Deck Count
	if(testG.deckCount[player2] == G.deckCount[player2]){
		printf("\n >>>>>> Success: Deck count of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of player2 is incorrect!!!");
	}
	//Discard Count
	if(testG.discardCount[player2] == G.discardCount[player2]){
		printf("\n >>>>>> Success: Discard count of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Discard count of player2 is incorrect!!!");
	}
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
