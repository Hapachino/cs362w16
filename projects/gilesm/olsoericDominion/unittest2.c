/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the numHandCards function in dominion.c. This 
 *   file utilizes the function numHandCards and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: unittest2.c
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
	struct gameState state;			// running instance of game
	int i = 0,						// iteration variable for loop counting
		numPlayers = 2,				// number of players in game
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1;		// used to determine pass or fail
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	/**************************************************************************
	 * TEST CONDITION 1 - Successful use of function numHandCards
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	numHandCards(&state);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: numHandCards\n");
	printf("* CONDITION: Number of hand cards on game initialization.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: numHandCards(&state)\n\n");
	printf("  TEST: Initial number of hand cards for starting player should be 5...\n");

	// TEST: Initial number of hand cards for starting player should be 5
	validationCheck = 1;
	if (state.handCount[state.whoseTurn] != 5)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	// TEST: Initial number of hand cards for non-starting player should be 0
	printf("  TEST: Initial number of hand cards for non-starting player should be 0...\n");
	validationCheck = 1;
	if (state.handCount[state.whoseTurn + 1] != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: Hand deck for player has five valid cards in it
	printf("  TEST: hand deck for player has five valid cards chosen for this game...\n");
	validationCheck = 1;
	for (i = 0; i < 5; i++) {
		if (state.deck[state.whoseTurn][i] == -1 || state.deck[state.whoseTurn][i] == 0)
			validationCheck = 1;	
	}
	printTestResult(validationCheck, -999, -999);

	return 0;
}
