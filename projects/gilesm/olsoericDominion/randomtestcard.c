/******************************************************************************
 * Author: Mark Giles
 * Filename: randomtestcard.c
 * Date Created: 2/13/2016
 * Last Modified: 2/13/2016
 * Description: This program performs random tests on the effects of the 
 *   village card in the dominion card game as implemented in the dominion.c
 *   file. The random tests attempt to reach maximum boundary and path coverage
 *   testing by automatically generating combinations of player hands and 
 *   calling the villageEffect function to compare expected results against 
 *   actual results.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char *argv[]) {
	struct gameState state,		// initialized game state for testing
					 backup;	// backup game state for comparisons
	// array of kingdom cards for game initialization
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, 
							cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 10000,
		numTests = 1000,
		numPlayers = 2,
		isValidDraw = 1,
		isValidActions = 1,
		isValidDiscard = 1,
		currentPlayer = 0,
		handpos,
		i = 0,
		j = 0,
		numPassed = 0,
		numFailed = 0;

	for (i = 0; i < numTests; i++) {
		// reset validation check to 1, 0 if test fails
		isValidDraw = 1;
		isValidActions = 1;
		isValidDiscard = 1;
		// setup working copy of game
		initializeGame(numPlayers, kingdomCards, randomSeed, &state);
		// randomize number of cards in player's hand
		state.handCount[currentPlayer] = (rand() % 10) + 1;
		// randomize position of village card and place it in hand
		handpos = rand() % state.handCount[currentPlayer];
		// randomize the player's deck count
		state.deckCount[currentPlayer] = rand() % 5;
		// fill in the rest of the cards in the player's hand
		for (j = 0; j < state.handCount[currentPlayer]; j++) {
			if (j != handpos)
				state.hand[currentPlayer][j] = rand() % 26;
			else
				state.hand[currentPlayer][j] = village;
		}
		// copy game state to backup for error detection
		memcpy(&backup, &state, sizeof(struct gameState));
		// call village card effect
		village_play(currentPlayer, &state, handpos);
		// check drawcard component
		if (state.handCount[currentPlayer] != (backup.handCount[currentPlayer]))
			isValidDraw = 0;
		if (state.deckCount[currentPlayer] != backup.deckCount[currentPlayer] - 1) {
			isValidDraw = 0;
		}
		if (state.hand[currentPlayer][state.handCount[currentPlayer] - 1] == -1) {
			isValidDraw = 0;
		}
		// check additional actions
		if (state.numActions != backup.numActions + 2) {
			isValidActions = 0;
		}	
		// check village card is discarded
		if (state.playedCards[state.playedCardCount - 1] != village) {
			isValidDiscard = 0;
		}	
		// print test conditions if the test failed
		if (isValidDraw == 0 || isValidActions == 0 || isValidDiscard == 0) {
			printf("TEST %i\n", i + 1);
			printf("Function Used: villageEffect(%i, &state, %i);\n", currentPlayer, handpos);
			printf("Position of village card: %i\n", handpos);
			printf("Number of Cards in Hand: %i\n", backup.handCount[currentPlayer]);
			printf("Starting deck count: %i\n", backup.deckCount[currentPlayer]);
			printf("Cards in hand: ");
			for (j = 0; j < backup.handCount[currentPlayer]; j++) {
				printf("%i, ", backup.hand[currentPlayer][j]);
			}
			printf("\n");
			printf("Random Seed: %i\n", randomSeed);
			printf("Failed Item(s): \n");
			if (isValidDraw == 0)
				printf("Invalid draw card operation\n");
			if (isValidActions == 0)
				printf("Invalid number of actions\n");
			if (isValidDiscard == 0)
				printf("Invalid discard operation\n");	
			numFailed++;
		} else {
			numPassed++;
		}
	
		randomSeed++;
	}

	printf("\nTotal Tests: %i\n", numTests);
	printf("Total Passed: %i\n", numPassed);
	printf("Total Failed: %i\n", numFailed);

	return 0;
}
