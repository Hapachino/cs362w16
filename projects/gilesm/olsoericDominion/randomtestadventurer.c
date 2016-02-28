/******************************************************************************
 * Author: Mark Giles
 * Filename: randomtestcard.c
 * Date Created: 2/13/2016
 * Last Modified: 2/13/2016
 * Description: This program performs random tests on the effects of the 
 *   adventurer card in the dominion card game as implemented in the dominion.c
 *   file. The random tests attempt to reach maximum boundary and path coverage
 *   testing by automatically generating combinations of player hands and 
 *   calling the adventurerEffect function to compare expected results against 
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
		isValidDiscard = 1,
		numNonTreasure = 0,
		treasurePos = 0,
		numRemoved = -1,
		treasureCount = 0,
		currentPlayer = 0,
		i = 0,
		j = 0,
		numPassed = 0,
		numFailed = 0,
		temphand[MAX_HAND];

	for (i = 0; i < numTests; i++) {
		// reset validation check to 1, 0 if test fails
		isValidDraw = 1;
		isValidDiscard = 1;
		numNonTreasure = 0;
		// setup working copy of game
		initializeGame(numPlayers, kingdomCards, randomSeed, &state);
		// randomize number of cards in player's hand
		state.handCount[currentPlayer] = (rand() %10) + 1;
		// fill in the player's hand
		for (j = 0; j < state.handCount[currentPlayer]; j++) {
			state.hand[currentPlayer][j] = rand() % 26;
		}

		// read from the end of the deck bachwards until two treasure cards are found
		for (j = state.deckCount[currentPlayer] - 1; j >= 0; j--) {
			if (state.deck[currentPlayer][i] == copper ||
				state.deck[currentPlayer][i] == silver ||
				state.deck[currentPlayer][i] == gold) {
				treasureCount++;
			} else {
				numNonTreasure++;
			}
			if (treasureCount == 2) {
				treasurePos = j;
				break;
			}
		}
		// copy game state to backup for error detection
		memcpy(&backup, &state, sizeof(struct gameState));
		
		// call village card effect
		adventurer_play(currentPlayer, &state);
		// check two cards are added to hand
		if (state.handCount[currentPlayer] != backup.handCount[currentPlayer] + 2) {
			isValidDraw = 0;
		}
		// ensure two additional cards are treasure cards
		if (!(state.hand[currentPlayer][backup.handCount[currentPlayer] + 1] == copper ||
			state.hand[currentPlayer][backup.handCount[currentPlayer] + 1] == silver ||
			state.hand[currentPlayer][backup.handCount[currentPlayer] + 1] == gold)) {
			isValidDraw = 0;
		}
		if (!(state.hand[currentPlayer][backup.handCount[currentPlayer]] == copper ||
			state.hand[currentPlayer][backup.handCount[currentPlayer]] == silver ||
			state.hand[currentPlayer][backup.handCount[currentPlayer]] == gold)) {
			isValidDraw = 0;
		}
		
		// ensure non-treasure cards are discarded
		if (state.discardCount[currentPlayer] != backup.discardCount[currentPlayer] + numNonTreasure) {
			isValidDiscard = 0;
		}

		// print test conditions if the test failed
		if (isValidDraw == 0 || isValidDiscard == 0 || 1 == 1) {
			printf("TEST %i\n", i + 1);
			printf("Function Used: adventurerEffect(%i, 0, temphand[], &state);\n", currentPlayer);
			printf("Position of second treasure card: %i\n", treasurePos);
			printf("Cards in starting hand: \n");
			for (j = 0; j < backup.handCount[currentPlayer]; j++) {
				printf("%i, ", backup.hand[currentPlayer][j]);
			}
			printf("\n");
			printf("Cards in ending hand: \n");
			for (j = 0; j < state.handCount[currentPlayer]; j++) {
				printf("%i, ", state.hand[currentPlayer][j]);
			}
			printf("\n");
			printf("Random Seed: %i\n", randomSeed);
			printf("Failed Item(s): \n");
			if (isValidDraw == 0)
				printf("Invalid draw operation\n");
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
