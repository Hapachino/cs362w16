/* -----------------------------------------------------------------------
 * Test is for village()
 *
 * cardtest3
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int newCards = 0;
    int discarded = 1;
   
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  
    int seed = 1000;
    int numPlayers = 2;
    int player1 = 0;
    int player2 = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	
	printf("TEST 1: choice1 = 0 = +1 card & +2 actions.\n");

	// copy the game state
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 1;
	

	printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[player1], G.handCount[player1] + newCards - discarded);
	printf("Player 1 deck count = %d, expected = %d\n", testG.deckCount[player1], G.deckCount[player1] - newCards);
	printf("Player 1 actions = %d, expected = %d\n", testG.numActions, G.numActions + 1);
	//for player 2
	printf("Player 2 hand count = %d, expected = %d\n", testG.handCount[player2], G.handCount[player2]);
	printf("Player 2 deck count = %d, expected = %d\n", testG.deckCount[player2], G.deckCount[player2]);

	//Player 1 hand count
	if(testG.handCount[player1] == G.handCount[player1] + newCards - discarded){
		printf("\n >>>>>> Success: Handcount of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of current player is incorrect!!!");
	}
	//Player 1 deck count
	if(testG.deckCount[player1] == G.deckCount[player1] - newCards){
		printf("\n >>>>>> Success: Deck count of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of current player is incorrect!!!");
	}
	//Player 1 Number of actions
	if(testG.numActions== G.numActions + 1){
		printf("\n >>>>>> Success: Number of Actions of current player is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Number of Actions of current player is incorrect!!!");
	}

	//Player 2 handcount
	if(testG.handCount[player2] == G.handCount[player2]){
		printf("\n >>>>>> Success: Handcount of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Handcount of player2 is incorrect!!!");
	}
	//Player 2 deck Count
	if(testG.deckCount[player2] == G.deckCount[player2]){
		printf("\n >>>>>> Success: Deck count of player2 is correct!!!");
	}
	else{
		printf("\n >>>>>> Fail: Deck count of player2 is incorrect!!!");
	}
	

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}
