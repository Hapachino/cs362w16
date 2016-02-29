#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define RSEED 5


void customInit (int players, int cards[10], struct gameState *state, int rseed) {
	initializeGame(players, cards, rseed, state);
	int i;
	for (i = 0; i < players; i++) {
		state->handCount[i] = 0;
		state->discardCount[i] = 0;
		state->deckCount[i] = 0;
	}
	state->hand[0][0] = council_room;
	state->handCount[0] = 1;
}

void fillDecks (int players, int cards[10], struct gameState *state) {
	int i, j, k;
	for (i = 0; i < players; i++) {
		int decksize;
		decksize = rand() % (MAX_DECK - 4) + 5;
		for (j = 0; j < decksize; j++) {
			k = rand() % 10;
			state->deck[i][j] = cards[k];
			state->deckCount[i]++;
		}
	}
}


int main() {
	int rseed;
	#ifdef RSEED
		rseed = RSEED;
	#else
		rseed = time(0);
	#endif
	srand(rseed);
	int players, correct, i, j;
	players = rand() % (MAX_PLAYERS - 2) + 2;	
	struct gameState state;
	int cards[10] = {adventurer, estate, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state, rseed);

	fillDecks(players, cards, &state);


	printf("TEST: COUNCIL ROOM CARD\n\n");
	printf("FULL DECKS\n");
	cardEffect(council_room, 0, 0, 0, &state, 0, NULL);
	printf("Print Player 0 hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Hand count: %d\n", state.handCount[0]); 
	printf("Should be 4\n");
	if (state.handCount[0] == 4)
		printf("PASSED\n");
	else printf("FAILED\n");
	printf("Check if council room was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == council_room)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count: %d\n", state.discardCount[0]);
	printf("Should be 1\n");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else printf("FAILED\n");

	for (i = 1; i < players; i++) {
		printf("\nPrint Player %d hand: ", i);
		for (j = 0; j < state.handCount[i]; j++)
			printf("%d ", state.hand[i][j]);
		printf("\n");
		printf("Hand count: %d\n", state.handCount[i]);
		printf("Should be 1\n");
		if (state.handCount[i] == 1)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}

	customInit(players, cards, &state, rseed);
	fillDecks(players, cards, &state);

	printf("\nEMPTY DECKS\n");
	for (i = 0; i < players; i++) {
		for (j = 0; j < state.deckCount[i]; j++) {
			state.discard[i][j] = state.deck[i][j];
			state.discardCount[i]++;
		}
		state.deckCount[i] = 0;
	}
	cardEffect(council_room, 0, 0, 0, &state, 0, NULL);
	printf("Print Player 0 hand: ");
	for (i = 0; i < state.handCount[0]; i++)
		printf("%d ", state.hand[0][i]);
	printf("\n");
	printf("Hand count: %d\n", state.handCount[0]); 
	printf("Should be 4\n");
	if (state.handCount[0] == 4)
		printf("PASSED\n");
	else printf("FAILED\n");
	printf("Check if council room was discarded: ");
	correct = 1;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] == council_room)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count: %d\n", state.discardCount[0]);
	printf("Should be 1\n");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else printf("FAILED\n");

	for (i = 1; i < players; i++) {
		printf("\nPrint Player %d hand: ", i);
		for (j = 0; j < state.handCount[i]; j++)
			printf("%d ", state.hand[i][j]);
		printf("\n");
		printf("Hand count: %d\n", state.handCount[i]);
		printf("Should be 1\n");
		if (state.handCount[i] == 1)
			printf("PASSED\n");
		else
			printf("FAILED\n");
	}

	return 0;
}