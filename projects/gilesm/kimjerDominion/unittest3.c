/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the gainCard function in dominion.c. This 
 *   file utilizes the function gainCard and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: unittest3.c
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
	memcpy(&stateOriginal, &state, sizeof(struct gameState));
	state.supplyCount[smithy] = 10;
	gainCard(smithy, &state, 1, state.whoseTurn);

	// DISPLAY
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: gainCard\n");
	printf("* CONDITION: Successful use of function gainCard.\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: gainCard(smithy, &state, 1, state.whoseTurn)\n\n");

	printf("  TEST: gainCard with toFlag = 1 increments the player's deck count by 1...\n");
	validationCheck = 1;
	if (state.deckCount[state.whoseTurn] != stateOriginal.deckCount[state.whoseTurn] + 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: gainCard with toFlag = 1 adds the card to the top of the player's deck...\n");
	validationCheck = 1;
	if (state.deck[state.whoseTurn][state.deckCount[state.whoseTurn] - 1] != smithy)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: supply count for smithy decremented by 1, all other positions remain the same...\n");
	validationCheck = 1;
	for (i = 0; i < 28; i++) {
		if (i == smithy) {
			if (state.supplyCount[i] != stateOriginal.supplyCount[i] - 1) {
				validationCheck = 0;
			}
		} else if (state.supplyCount[i] != stateOriginal.supplyCount[i]) {
			validationCheck = 0;
		}
	}
	printTestResult(validationCheck, -999, -999);

	// reset game state
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	// add card to the player's hand
	gainCard(smithy, &state, 2, state.whoseTurn);
	printf("  EXECUTING: gainCard(smithy, &state, 2, state.whoseTurn)\n\n");
	
	printf("  TEST: gainCard with toFlag = 3 increments the player's hand count by 1...\n");
	validationCheck = 1;
	if (state.handCount[state.whoseTurn] != stateOriginal.handCount[state.whoseTurn] + 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	printf("  TEST: gainCard with toFlag = 3 adds the card to the top of the player's hand...\n");
	validationCheck = 1;
	if (state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] != smithy)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// ensure there are smithy cards available in supply count
	state.supplyCount[smithy] = 10;
	gainCard(smithy, &state, 3, state.whoseTurn);
	printf("  EXECUTING: gainCard(smithy, &state, 3, state.whoseTurn)\n\n");

	printf("  TEST: gainCard with toFlag = 3 increments the player's discard count by 1...\n");
	validationCheck = 1;
	if (state.discardCount[state.whoseTurn] != stateOriginal.discardCount[state.whoseTurn] + 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	printf("  TEST: gainCard with toFlag = 3 adds the card to the top of the player's discard...\n");
	validationCheck = 1;
	if (state.discard[state.whoseTurn][state.discardCount[state.whoseTurn] - 1] != smithy)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: All changes are for current player, player 2's discard should be unchanged...\n");
	validationCheck = 1;
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) == 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: All changes are for current player, player 2's hand should be unchanged...\n");
	validationCheck = 1;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) == 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: All changes are for current player, player 2's deck should be unchanged...\n");
	validationCheck = 1;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) == 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	// setting supply count to zero
	stateOriginal.supplyCount[smithy] = 0;
	memcpy(&state, &stateOriginal, sizeof(struct gameState));
	gainCard(smithy, &state, 1, state.whoseTurn);

	printf("  TEST: gainCard with supply count for card set to zero should not change state at all...\n");
	validationCheck = 1;
	if (memcmp(&state, &stateOriginal, sizeof(struct gameState)) != 0)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);
	
	return 0;
}
