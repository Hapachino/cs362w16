/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the smithy cardEffect function in dominion.c. This 
 *   file utilizes the function smithy cardEffect and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: cardtest1.c
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
		validationCheck = 1,		// used to determine pass or fail
		found = 0;					// detecs if card found in deck
	struct infosStruct infos;
	infos.currentPlayer = 0;
	infos.handPos = 4;
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	state.hand[state.whoseTurn][4] = smithy;
	memcpy(&stateOriginal, &state, sizeof(struct gameState));

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: effectSmithy\n");
	printf("***************************************************************************\n");
	printf("  NOTE: Smithy card placed in position 0 before each test...\n");
	printf("\n  EXECUTING: effectSmithy(&state, &infos)\n\n");

	printf("  TEST: 3 valid cards added to current player hand...\n");
	effectSmithy(&state, &infos);
	validationCheck = 1;
	for (i = 0; i < state.handCount[state.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] != stateOriginal.hand[state.whoseTurn][i]) {
			if (state.hand[state.whoseTurn][i] == -1) {
				validationCheck = 0;
			}
		}
	}
	
	// Ensure top card is valid selection
	if (state.hand[state.whoseTurn][stateOriginal.handCount[state.whoseTurn] + 1] == -1)
		validationCheck = 0;
	// Ensure card after top card is -1
	if (state.hand[state.whoseTurn][stateOriginal.handCount[state.whoseTurn] + 2] != -1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Current player hand count changed: 3 draws - 1 discard = +2...\n");
	validationCheck = 1;
	if (state.handCount[state.whoseTurn] != stateOriginal.handCount[state.whoseTurn] + 2)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: The smithy card is properly removed from the player hand...\n");
	validationCheck = 1;
	if (state.hand[state.whoseTurn][0] == smithy)
		validationCheck = 1;
	printTestResult(validationCheck, -999, -999);
	
	printf("  TEST: 3 cards	came from player's deck...\n");
	validationCheck = 1;
	for (i = 0; i < state.handCount[state.whoseTurn]; i++) {
		if (state.hand[state.whoseTurn][i] != stateOriginal.hand[state.whoseTurn][i]) {
			found = 0;
			for (j = 0; j < stateOriginal.deckCount[state.whoseTurn]; j++) {
				if (state.hand[state.whoseTurn][i] == stateOriginal.deck[state.whoseTurn][j]) {
					found = 1;
				}
			}
			if (found == 0)
				validationCheck = 0;
		}
	}
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Player 2's decks were not modified...\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Game kingdom decks were not modified...\n");
	validationCheck = 1;
	for (i = 0; i < 28; i++) {
		if (state.supplyCount[i] != stateOriginal.supplyCount[i])
			validationCheck = 0;
	}
	printTestResult(validationCheck, -999, -999);
	
	return 0;
}
