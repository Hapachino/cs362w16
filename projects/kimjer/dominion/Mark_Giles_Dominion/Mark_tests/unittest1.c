/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the buyCard function in dominion.c. This file
 *   utilizes the function buyCard and dominion supporting files to execute
 *   the function and check for error conditions.
 * File Name: unittest1.c
 * Date Created: 1/31/2016
 *****************************************************************************/

#include <stdio.h>
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
		validationCheck = 1,		// used to determine pass or fail
		testCard = 0;				// determines test card for function call
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	/**************************************************************************
	 * TEST CONDITION 1 - Successful use of function buyCard
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	state.coins = 100;
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	testCard = smithy;
	buyCard(testCard, &state);
	
	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: buyCard\n");
	printf("* CONDITION: Successful use of function.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: buyCard(smithy, &state)\n\n");
	printf("  TEST: Player's discard count is incremented by one...\n");

	// TEST: Player's discard count is incremented by one
	validationCheck = 1;
	if (state.discardCount[state.whoseTurn] != stateOriginal.discardCount[stateOriginal.whoseTurn] + 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: New card is in player's discard
	printf("  TEST: Newly purchased card is in player's discard deck and the rest is unchanged...\n");
	validationCheck = 1;
	for (i = 0; i < state.discardCount[state.whoseTurn]; i++) {
		if (i < state.discardCount[state.whoseTurn] - 1) {
			if (state.discard[state.whoseTurn][i] != stateOriginal.discard[stateOriginal.whoseTurn][i]) {
				validationCheck = 0;
			}
		} else {
			if (state.discard[state.whoseTurn][i] != testCard) {
				validationCheck = 0;
			}
		}
	}
	printTestResult(validationCheck, -999, -999);

	// TEST: Purchased card is removed from the supply deck
	printf("  TEST: Purchased card is removed from the supply deck...\n");
	validationCheck = 1;
	if (state.supplyCount[testCard] != stateOriginal.supplyCount[testCard] - 1)
		validationCheck = 1;
	printTestResult(validationCheck, -999, -999);

	// TEST: Player's deck should be unchanged
	printf("  TEST: Player's deck should be unchanged...\n");
	validationCheck = 1;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: Player's hand should be unchanged
	printf("  TEST: Player's hand should be unchanged...\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: Other player's discard should be unchanged
	printf("  TEST: Other player's discard should be unchanged...\n");
	validationCheck = 1;
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: Other player's deck should be unchanged
	printf("  TEST: Other player's deck should be unchanged...\n");
	validationCheck = 1;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) != 1) 
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// TEST: Other player's hand should be unchanged
	printf("  TEST: Other player's hand should be unchanged...\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);	

	// TEST: Purchased card's cost is deducted from player's coins
	printf("  TEST: Purchased card's cost is deducted from player's coins...\n");
	validationCheck = 1;
	if (state.coins != stateOriginal.coins - getCardCost(smithy))
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	// TEST: Number of buys is decremented by one
	printf("  TEST: Number of buys is deecremented by one...\n");
	validationCheck = 1;
	if (state.numBuys != stateOriginal.numBuys - 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	/**************************************************************************
	 * TEST CONDITION 2 - Player unable to afford the requested card
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	stateOriginal.coins = 0;
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	testCard = minion;
	buyCard(testCard, &state);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: buyCard\n");
	printf("* CONDITION: Player unable to afford requested card. Coins set to 0 before \n");
	printf("*   executing buyCard function\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: buyCard(minion, &state)\n\n");
	printf("  TEST: Game state should not change at all...\n");
	
	// TEST: Game state should not change at all
	validationCheck = 1;
	if (memcmp(&state, &stateOriginal, sizeof(struct gameState)) != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	/**************************************************************************
	 * TEST CONDITION 3 - The chosen supply card is out of stock
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	stateOriginal.supplyCount[remodel] = 0;
	stateOriginal.coins = 100;
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	testCard = remodel;
	buyCard(testCard, &state);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: buyCard\n");
	printf("* CONDITION: Supply card unavailable by setting count to 0.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: buyCard(remodel, &state)\n\n");
	printf("  TEST: Game state should not change at all...\n");

	// TEST: Game state should not change at all
	validationCheck = 1;
	if (memcmp(&state, &stateOriginal, sizeof(struct gameState)) != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	/**************************************************************************
	 * TEST CONDITION 4 - Player has zero buys remaining.
	 *************************************************************************/
	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	stateOriginal.supplyCount[remodel] = 10;
	stateOriginal.numBuys = 0;
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	testCard = remodel;
	buyCard(testCard, &state);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: buyCard\n");
	printf("* CONDITION: Player has zero buys remaining.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: buyCard(remodel, &state)\n\n");
	printf("  TEST: Game state should not change at all...\n");

	// TEST: Game state should not change at all
	validationCheck = 1;
	if (memcmp(&state, &stateOriginal, sizeof(struct gameState)) != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	return 0;
}
