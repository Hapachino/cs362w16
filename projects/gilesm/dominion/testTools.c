#include <stdio.h>
#include <string.h>
#include "dominion.h"

int isDiscardSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0,
		validationCheck = 1;
	for (i = 0; i < stateOriginal->discardCount[player]; i++) {
		if (stateOriginal->discard[player][i] != state->discard[player][i])
			return 0;
	}

	return 1;
}

int isHandSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0,
		validationCheck = 1;
	for (i = 0; i < stateOriginal->handCount[player]; i++) {
		if (stateOriginal->hand[player][i] != state->hand[player][i])
			return 0;
	}

	return 1;
}

int isDeckSame(struct gameState *state, struct gameState *stateOriginal, int player) {
	int i = 0,
		validationCheck = 1;
	for (i = 0; i < stateOriginal->deckCount[player]; i++) {
		if (stateOriginal->deck[player][i] != state->deck[player][i])
			return 0;
	}

	return 1;
}

void printTestResult(int validationCheck, int expected, int actual) {
	if (validationCheck == 1)
		printf("\tPASS!\n\n");
	else
		printf("\tFAIL!\n\n");
	if (expected != -999) {
		printf("\t\tEXPECTED VALUE: %i\n", expected);
		printf("\t\tACTUAL VALUE: %i\n", actual);
	}
}
