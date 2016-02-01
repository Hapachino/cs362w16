#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main() {
	struct gameState state,			// running instance of game
					 stateBackup;	// backup copy of game to detect changes
	int i = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		randomSeed = 10000;			// seed for random generation
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, embargo, minion, mine, cutpurse,
							sea_hag, tribute, smithy};

	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);
	
	/**************************************************************************
	 * TEST CONDITION 1 - Successful use of function drawCard()
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION

	// TEST: New card was in player's discard deck
	
	// TEST: New card is removed from the supply deck
	
	// TEST: No other decks should change 
	
	// TEST: Purchased card's cost is deducted from player's coins
	
	// TEST: No other player coins should be affected
	
	// TEST: Number of buys is decremented by one

	/**************************************************************************
	 * TEST CONDITION 2 - Player unable to afford the requested card
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	
	// TEST: Game state should not change at all, still same phase and turn

	/**************************************************************************
	 * TEST CONDITION 3 - The chosen supply card is out of stock
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	
	// TEST: Game state should not change at all, still same phase and turn

	/**************************************************************************
	 * TEST CONDITION 4 - The chosen supply card is not in use during this game
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	
	// TEST: Game state should not change at all, still same phase and turn
	printf("Hi from unit test 1\n");
	return 0;
}
