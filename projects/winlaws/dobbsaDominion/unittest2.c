#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#define RSEED 5


void customInit (int players, int cards[10], struct gameState *state) {
	initializeGame(players, cards, RSEED, state);
	int i;
	for (i = 0; i < players; i++) {
		state->handCount[i] = 0;
		state->discardCount[i] = 0;
		state->deckCount[i] = 0;
	}

	for (i = 0; i < 5; i++)
		state->hand[0][i] = i;
	state->handCount[0] = 5;
}


int main() {
	srand(RSEED);
	int players, i, correct, oldcard;
	correct = 1;
	players = rand() % (MAX_PLAYERS - 2) + 2;	
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);

	printf("TEST: DISCARDCARD\n\n");
	printf("Base hand: 5, 1, 2, 3, 4\n");
	printf("		   Silver, Estate, Duchy, Province, Copper\n\n");
	state.hand[0][0] = 5;
	printf("TEST: discard first card in hand\n");
	discardCard(0, 0, &state, 0);
	printf("Hand count: %d; Expected: 4\n", state.handCount[0]);
	if (state.handCount[0] == 4)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Print cards in hand: ");
	for (i = 0; i < state.handCount[0]; i++) {
		printf("%d ", state.hand[0][i]);
		if (state.hand[0][i] == 0)
			correct = 0;
	}
	printf("\n");
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count increment: ");
	if (state.discardCount[0] == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in discard pile: ");
	if (state.discard[0][0] == 5)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Played cards increment: ");
	if (state.playedCardCount == 1)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in played cards: ");
	if (state.playedCards[0] == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	correct = 1;
	printf("TEST: discard last card in hand\n");
	oldcard = state.handCount[0] - 1;
	discardCard(state.handCount[0] - 1, 0, &state, 0);
	printf("Hand count: %d; Expected: 3\n", state.handCount[0]);
	if (state.handCount[0] == 3)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Print cards in hand: ");
	for (i = 0; i < state.handCount[0]; i++) {
		printf("%d ", state.hand[0][i]);
		if (state.hand[0][i] == oldcard)
			correct = 0;
	}
	printf("\n");
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Discard count increment: ");
	if (state.discardCount[0] == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in discard pile: ");
	if (state.discard[0][1] == oldcard)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Played cards increment: ");
	if (state.playedCardCount == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in played cards: ");
	if (state.playedCards[1] == oldcard)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	correct = 1;
	oldcard = state.hand[0][1];
	int prevDiscard = state.discardCount[0];
	int prevPlayed = state.playedCardCount;
	printf("TEST: trash second card\n");
	discardCard(1, 0, &state, 1);
	printf("Hand count: %d; Expected: 2\n", state.handCount[0]);
	if (state.handCount[0] == 2)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Print cards in hand: ");
	for (i = 0; i < state.handCount[0]; i++) {
		printf("%d ", state.hand[0][i]);
		if (state.hand[0][i] == oldcard)
			correct = 0;
	}
	printf("\n");
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("No discard count increment: ");
	if (state.discardCount[0] == prevDiscard)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in discard pile: ");
	correct = 1;
	for (i = 0; i < state.discardCount[0]; i++) {
		if (state.discard[0][i] == oldcard)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("No played cards increment: ");
	if (state.playedCardCount == prevPlayed)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("Card in played cards: ");
	correct = 1;
	for (i = 0; i < state.playedCardCount; i++) {
		if (state.playedCards[i] == oldcard)
			correct = 0;
	}
	if (correct)
		printf("PASSED\n");
	else
		printf("FAILED\n");


	customInit(players, cards, &state);
	for (i = 0; i < state.handCount[0]; i++)
		state.hand[0][i] = -1;
	state.handCount[0] = 0;
	printf("TEST: discard from empty hand\n");
	discardCard(1, 0, &state, 0);
	printf("Hand count: %d; Expected: 0\n", state.handCount[0]);
	if (state.handCount[0] == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("No discard count increment: ");
	if (state.discardCount[0] == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");
	printf("No played cards increment: ");
	if (state.playedCardCount == 0)
		printf("PASSED\n");
	else
		printf("FAILED\n");

	return 0;
}