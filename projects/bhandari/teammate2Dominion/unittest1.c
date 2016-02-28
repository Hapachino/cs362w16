/*
Rishi Bhandarkar
CS 362

Unit test for scoreFor() function
Gamestate
	- We are creating a game between 2 players
	- After initialization, both players have 3 Estate cards and 7 copper cards
		- Player 1 will draw 5 cards, player 2 has all their cards in their deck
	- This equates to both players having 3 points

Requirements to test
	- After initialization, both players must have 3 points
	- After calculating points:
		- The state of both players' hands, decks, and discards must be the same
		- The state of the Kingdom and Victory piles must be the same
*/

/*
Notes: function incorrect, error in 3rd for loop (disacrd had twice)
		- not entering for since discard = 0, so not counting points in deck
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {
	int seed = 1000, fail = 0; //flag to determine if we saw a failure
	int scoreOne, scoreTwo;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,	sea_hag, tribute, smithy};
	struct gameState G, prevG;

	SelectStream(2);
	PutSeed(3);

	initializeGame(2, k, seed, &G);
	memcpy(&prevG, &G, sizeof(struct gameState));
	
	printf ("Testing the scoreFor() method\n");
	scoreOne = scoreFor(0, &G);
	scoreTwo = scoreFor(1, &G);
	
	printf("Test if scores are calculated correctly..\n");
	if(scoreOne != 3 && scoreTwo != 3){
		printf("TEST FAILED: Player 1 and Player 2 scored inaccurately\n");
		fail = 1;
	}
	else if(scoreOne != 3){
		printf("TEST FAILED: Player 1 score inaccurate\n");
		fail = 1;
	}
	else if(scoreTwo != 3){
		printf("TEST FAILED: Player 2 score inaccurate\n");
		fail = 1;
	}
	
	printf("Test if hands, decks, and discard piles are unchanged for both players..\n" );
	if(G.handCount[0] != prevG.handCount[0]){
		printf("TEST FAILED: Player 1 hand altered\n");
		fail = 1;
	}
	if(G.deckCount[0] != prevG.deckCount[0]){
		printf("TEST FAILED: Player 1 deck altered\n");
		fail = 1;
	}
		
	if(G.discardCount[0] != prevG.discardCount[0]){
		printf("TEST FAILED: Player 1 discard pile altered\n");
		fail = 1;
	}
	if(G.handCount[1] != prevG.handCount[1]){
		printf("TEST FAILED: Player 2 hand altered\n");
		fail = 1;
	}
	if(G.deckCount[1] != prevG.deckCount[1]){
		printf("TEST FAILED: Player 2 deck altered\n");
		fail = 1;
	}
		
	if(G.discardCount[1] != prevG.discardCount[1]){
		printf("TEST FAILED: Player 2 discard pile altered\n");
		fail = 1;
	}
	
	printf("Test if Victory and Kingdom piles are unchanged..\n");
	int arraySize = sizeof(G.supplyCount) / sizeof(int);
	for(int i = 0; i < arraySize; i++){
		if(G.supplyCount[i] != prevG.supplyCount[i]){
			printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
			fail = 1;
		}
	}
	
	if(fail == 0){
		printf("TEST SUCCEEDED\n");
	}
	
	return 0;
}
