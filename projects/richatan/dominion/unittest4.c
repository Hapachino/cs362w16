/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: getWinners()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PLAYERS 4
#define ZERO_CARD copper
#define SCORE_CARD province
 
int main () {
	int i;				//loop control
	int result;			//return value for function calls
	int failed;			//flags for tests
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;
	
	int players[MAX_PLAYERS];	//array for getWinners()

	printf("---Testing getWinners()---\n");
	
//---Test all scores = 0
/*---Expected result: 
	- All players are winners
	- No changes to gameState
*/
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Clear all players cards
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = 0;
		g->handCount[i] = 0;
		g->discardCount[i] = 0;
	}
	g->playedCardCount = 0;
	//Add one 0-score card to each player's hand
	for (i = 0; i < g->numPlayers; i++){
		g->handCount[i]++;
		g->hand[i][0] = ZERO_CARD;
	}
	//Change turn to last player (to avoid bonus points)
	g->whoseTurn = g->numPlayers - 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to get winners
	result = getWinners(players, g);
	failed = 0;
	if (result != 0){
		printf("FAIL when all scores = 0\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL when all scores = 0\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Check all players are winners
	for (i = 0; i < g->numPlayers; i++){
		if (players[i] != 1){
			printf("FAIL when all scores = 0\n");
			printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 1);
			failed = 1;	
		}
	}
	//Final check
	if (!failed){
		printf("PASS when all scores = 0\n");
	}

//---Test one winner
/*---Expected result: 
	- Player 0 win value = 1
	- All other player's win value = 0
	- No changes to gameState
*/
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Clear all players cards
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = 0;
		g->handCount[i] = 0;
		g->discardCount[i] = 0;
	}
	g->playedCardCount = 0;
	//Add one 0-score card to each player's hand
	for (i = 0; i < g->numPlayers; i++){
		g->hand[i][g->handCount[i]] = ZERO_CARD;
		g->handCount[i]++;
	}
	//Add one victory card to player 0's hand
	g->hand[0][g->handCount[0]] = SCORE_CARD;
	g->handCount[0]++;
	//Change turn to last player (to avoid bonus points)
	g->whoseTurn = g->numPlayers - 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to get winners
	result = getWinners(players, g);
	failed = 0;
	if (result != 0){
		printf("FAIL for 1 winner\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL for 1 winner\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Check player 0 wins
	if (players[0] != 1){
		printf("FAIL for 1 winner\n");
		printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 1);
		failed = 1;	
	}
	//Check players 1-3 lose
	for (i = 1; i < g->numPlayers; i++){
		if (players[i] != 0){
			printf("FAIL for 1 winner\n");
			printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 0);
			failed = 1;	
		}
	}
	//Final check
	if (!failed){
		printf("PASS for 1 winner\n");
	}

//---Test two winners
/*---Expected result: 
	- Player 0 and 1 win value = 1
	- All other player's win value = 0
	- No changes to gameState
*/
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Clear all players cards
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = 0;
		g->handCount[i] = 0;
		g->discardCount[i] = 0;
	}
	g->playedCardCount = 0;
	//Add one 0-score card to each player's hand
	for (i = 0; i < g->numPlayers; i++){
		g->hand[i][g->handCount[i]] = ZERO_CARD;
		g->handCount[i]++;
	}
	//Add one victory card to player 0 and 1's hand
	g->hand[0][g->handCount[0]] = SCORE_CARD;
	g->handCount[0]++;
	g->hand[1][g->handCount[1]] = SCORE_CARD;
	g->handCount[1]++;
	//Change turn to last player (to avoid bonus points)
	g->whoseTurn = g->numPlayers - 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to get winners
	result = getWinners(players, g);
	failed = 0;
	if (result != 0){
		printf("FAIL for 2 winners\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL for 2 winners\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Check players 0-1 win
	for (i = 0; i <= 1; i++){
		if (players[i] != 1){
			printf("FAIL for 2 winners\n");
			printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 1);
			failed = 1;	
		}
	}
	//Check players 2-3 lose
	for (i = 2; i < g->numPlayers; i++){
		if (players[i] != 0){
			printf("FAIL for 2 winners\n");
			printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 0);
			failed = 1;	
		}
	}
	//Final check
	if (!failed){
		printf("PASS for 2 winners\n");
	}
	
//---Test all winners
/*---Expected result: 
	- All player's win value = 1
	- No changes to gameState
*/
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Clear all players cards
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = 0;
		g->handCount[i] = 0;
		g->discardCount[i] = 0;
	}
	g->playedCardCount = 0;
	//Add one victory card to each player's hand
	for (i = 0; i < g->numPlayers; i++){
		g->hand[i][g->handCount[i]] = SCORE_CARD;
		g->handCount[i]++;
	}
	//Change turn to last player (to avoid bonus points)
	g->whoseTurn = g->numPlayers - 1;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to get winners
	result = getWinners(players, g);
	failed = 0;
	if (result != 0){
		printf("FAIL for all winners\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("FAIL for all winners\n");
		printf("  gameState changed\n");
		failed = 1;
	} 
	//Check all players win
	for (i = 0; i < g->numPlayers; i++){
		if (players[i] != 1){
			printf("FAIL for all winners\n");
			printf("  Player %d win value: %d, Expected: %d\n", i, players[i], 1);
			failed = 1;	
		}
	}
	//Final check
	if (!failed){
		printf("PASS for all winners\n");
	}
	
	return 0;
}
