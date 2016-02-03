/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the village cardEffect function in dominion.c. This 
 *   file utilizes the function village cardEffect and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: cardtest3.c
 * Date Created: 1/31/2016
 *****************************************************************************/#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include "testTools.c"

int main() {
	struct gameState state,			// running instance of game
					 stateOriginal;	// backup copy of game to detect changes
	int i = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		count = 0,					// counts number of village cards
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1;		// used to determine pass or fail
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	state.hand[state.whoseTurn][0] = village;
	memcpy(&stateOriginal, &state, sizeof(struct gameState));

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: adventurerEffect\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: villageEffect(state.whoseTurn, &state, 0)\n\n");
	printf("%i\n", state.handCount[state.whoseTurn]);
	villageEffect(state.whoseTurn, &state, 0);

	printf("  TEST: One card is drawn and added to the player's hand...\n\n");
	validationCheck = 1;
	if (state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] != 
		stateOriginal.deck[state.whoseTurn][state.deckCount[state.whoseTurn]]) {
		validationCheck = 0;
	}
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Two actions are added to the game state\n\n");
	validationCheck = 1;
	if (state.numActions != stateOriginal.numActions + 2)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Adventurer card is removed from player's hand and discarded\n\n");
	validationCheck = 1;
	count = 0;
	for (i = 0; i < stateOriginal.handCount[stateOriginal.whoseTurn]; i++) {
		if (stateOriginal.hand[state.whoseTurn][i] == village) {
			count++;
		}
	}
	printf("%i", count);
	for (i = 0; i < state.handCount[stateOriginal.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] == village) {
			count--;
		}
	}
	if (count != 1)
		validationCheck = 0;
	// successful if one remains after comparing two decks
	printTestResult(validationCheck, -999, -999);

	return 0;
}
