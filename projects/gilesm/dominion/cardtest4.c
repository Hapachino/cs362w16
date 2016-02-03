/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the remodel cardEffect function in dominion.c. This 
 *   file utilizes the function remodel cardEffect and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: cardtest4.c
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
		j = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1;		// used to determine pass or fail
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	state.hand[state.whoseTurn][0] = silver;
	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: remodelEffect\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: remodelEffect(state.whoseTurn, 1, 2, &state, 0)\n\n");
	remodelEffect(state.whoseTurn, 1, 2, &state, 0);

	printf("  TEST: Choice1 removed from player's hand with valid selection...\n\n");
	validationCheck = 0;
	for (i = 0; i < state.handCount[state.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] == 1) {
			validationCheck = 1;
			break;
		}
	}
	printTestResult(validationCheck, -999, -999);

	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	remodelEffect(state.whoseTurn, province, copper, &state, 0);
	printf("  TEST: Choice1/discard card cost + 2 must not be greater than choice2/buyCard...\n\n");
	validationCheck = 1;
	if (memcmp(&state, &stateOriginal, sizeof(struct gameState)) != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);


	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	remodelEffect(state.whoseTurn, copper, province, &state, 0);
	printf("  TEST: The new card must be added to the player's hand...\n\n");
	validationCheck = 1;
	if (state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] != copper)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: The trashed card must be removed from the player's hand and placed in discard...\n\n");
	if (state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1] != province)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	return 0;
}
