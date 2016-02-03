/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the updateCoins function in dominion.c. This 
 *   file utilizes the function updateCoins and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: unittest4.c
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
		randomSeed = 10000,			// seed for random generation
		validationCheck = 1;		// used to determine pass or fail
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	/**************************************************************************
	 * TEST CONDITION - Successful use of function gainCard
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	for (i = 0; i < 5; i++) {
		state.hand[state.whoseTurn][i] = copper;
	}
	updateCoins(state.whoseTurn, &state, 0);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: updateCoins\n");
	printf("* CONDITION: Successful use of function updateCoins.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: updateCoins(state.whoseTurn, &state, 0)\n\n");

	printf("  TEST: Placed five copper cards in player hand, should be 5...\n");
	validationCheck = 1;
	if (state.coins != 5)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Placed six silver cards in player hand, set handCount to 6, should be 12...\n");
	validationCheck = 1;
	for (i = 0; i < 6; i++) {
		state.hand[state.whoseTurn][i] = silver;
	}
	state.handCount[state.whoseTurn] = 6;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 12)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: 1 Copper, 2 Silver, 2 Gold, set handCount to 5, should be 11...\n");
	validationCheck = 1;
	state.handCount[state.whoseTurn] = 5;
	state.hand[state.whoseTurn][0] = copper;
	state.hand[state.whoseTurn][1] = silver;
	state.hand[state.whoseTurn][2] = silver;
	state.hand[state.whoseTurn][3] = gold;
	state.hand[state.whoseTurn][4] = gold;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 11)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Setting hand count to 4, should only read value of top 4 cards = 8...\n");
	validationCheck = 1;
	state.handCount[state.whoseTurn] = 4;
	updateCoins(state.whoseTurn, &state, 0);
	if (state.coins != 8)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	printf("  TEST: Including bonus of 5, should result in 8 + 5 = 13...\n");
	validationCheck = 1;
	updateCoins(state.whoseTurn, &state, 5);
	if (state.coins != 13)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	printf("  TEST: updateCoins only accesses cards, card piles should be unchanged...\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	if (isHandSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	if (isDeckSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	if (isDeckSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	if (isDiscardSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	if (isDiscardSame(&state, &stateOriginal, 0) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	return 0;
}
