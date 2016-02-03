/******************************************************************************
 * Author: Mark Giles
 * Description: Unit tests for the adventurer cardEffect function in dominion.c. This 
 *   file utilizes the function adventurer cardEffect and dominion supporting files to 
 *   execute the function and check for error conditions.
 * File Name: cardtest2.c
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
		validationCheck = 1,		// used to determine pass or fail
		cardDrawn = 0,				// card selected from deck
		count = 0,					// number of cards removed from player deck
		drawntreasure = 0,			// determines number of cards drawn
		temphand[100];				// used to store non-treasure cards
	// initial array of kingdom cards
	int kingdomCards[10] = {adventurer, gardens, village, minion, mine, cutpurse,
							sea_hag, remodel, smithy};
	
	// Initializing game and backup copy of game
	initializeGame(numPlayers, kingdomCards, randomSeed, &state);

	// PERFORMING OPERATIONS TO MEET TEST CONDITION
	memcpy(&stateOriginal, &state, sizeof(struct gameState));

	// DISPLAY
	for (i = 0; i < 100; i++) {
		temphand[i] = -1;
	}
	printf("***************************************************************************\n");
	printf("* TESTING FUNCTION: adventurerEffect\n");
	printf("***************************************************************************\n");
	printf("\n  EXECUTING: adventurerEffect(state.whoseTurn, -1, -1, temphand, &state)\n\n");
	
	printf("  TEST: Non-treasure cards are successfully added to the discard pile\n\n");
	adventurerEffect(state.whoseTurn, -1, -1, temphand, &state);
	validationCheck = 1;
	while (drawntreasure < 2) {
		cardDrawn = stateOriginal.deck[state.whoseTurn][stateOriginal.deckCount[state.whoseTurn] - 1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
			drawntreasure++;
			count++;
		} else {
			count++;
		}
	}
	if (state.discardCount[state.whoseTurn] != stateOriginal.discardCount[state.whoseTurn] + (count - 2))
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Two additional treasure cards are added to the player's hand\n\n");
	validationCheck = 1;
	if (state.handCount[state.whoseTurn] != state.handCount[state.whoseTurn] + 2)
		validationCheck = 0;
	if (!(state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == copper ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == silver ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 1] == gold)) {
		validationCheck = 0;
	}
	if (!(state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == copper ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == silver ||
		state.hand[state.whoseTurn][state.handCount[state.whoseTurn] - 2] == gold)) {
		validationCheck = 0;
	}
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Other Player's cards are not modified\n\n");
	validationCheck = 1;
	if (isDeckSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	if (isHandSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	if (isDiscardSame(&state, &stateOriginal, state.whoseTurn + 1) != 1)
		validationCheck = 0;
	printTestResult(validationCheck, -999, -999);

	printf("  TEST: Game state supply count is not modified\n\n");
	validationCheck = 1;
	for (i = 0; i < 28; i++) {
		if (state.supplyCount[i] != stateOriginal.supplyCount[i])
		validationCheck = 0;
	}
	printTestResult(validationCheck, -999, -999);
	
	return 0;
}
