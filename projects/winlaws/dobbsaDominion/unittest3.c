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
}


int main() {
	srand(RSEED);
	int players, gameover, i;
	players = rand() % (MAX_PLAYERS - 2) + 2;	
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);

	printf("TEST: ISGAMEOVER\n\n");
	printf("TEST: No piles empty\n");
	gameover = isGameOver(&state);
	if (gameover)
		printf("Game over - FAILED\n");
	else
		printf("Game not over - PASSED\n");

	customInit(players, cards, &state);
	printf("TEST: province pile empty\n");
	state.supplyCount[province] = 0;
	gameover = isGameOver(&state);
	if (gameover)
		printf("Game over - PASSED\n");
	else
		printf("Game not over - FAILED\n");

	customInit(players, cards, &state);
	printf("TEST: three random piles empty\n");
	printf("Empty piles: ");
	for (i = 0; i < 3; i++) {
		int empty;
		do {
			empty = rand() % (treasure_map + 1);
		} while (empty == province);
		state.supplyCount[empty] = 0;
		printf("%d ", empty);
	}
	printf("\n");
	gameover = isGameOver(&state);
	if (gameover)
		printf("Game over - PASSED\n");
	else
		printf("Game not over - FAILED\n");

	customInit(players, cards, &state);
	printf("TEST: two random piles empty\n");
	printf("Empty piles: ");
	for (i = 0; i < 2; i++) {
		int empty;
		do {
			empty = rand() % (treasure_map  + 1);
		} while (empty == province);
		state.supplyCount[empty] = 0;
		printf("%d ", empty);
	}
	printf("\n");
	gameover = isGameOver(&state);
	if (gameover)
		printf("Game over - FAILED\n");
	else
		printf("Game not over - PASSED\n");

	customInit(players, cards, &state);
	printf("TEST: more than three random piles empty\n");
	printf("Empty piles: ");
	for (i = 0; i < 5; i++) {
		int empty;
		do {
			empty = rand() % (treasure_map + 1);
		} while (empty == province);
		state.supplyCount[empty] = 0;
		printf("%d ", empty);
	}
	printf("\n");
	gameover = isGameOver(&state);
	if (gameover)
		printf("Game over - PASSED\n");
	else
		printf("Game not over - FAILED\n");

	return 0;
}