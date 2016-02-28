/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the isGameOver() function.
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void testGameOver(struct gameState *state) 
{
	int r, a, b, c;
	state->supplyCount[province] = 0;
	r = isGameOver(state);
	assert(r == 1);
	state->supplyCount[province] = 5;

	while (a == province) 
	{
		a = floor(Random() * 25);
	}
	state->supplyCount[a] = 0;
	b = floor(Random() * 25);
	while (b == a || b == province) 
	{
		b = floor(Random() * 25);
	}
	state->supplyCount[b] = 0;
	c = floor(Random() * 25);
	while (c == a || c == b || c == province) 
	{
		c = floor(Random() * 25);
	}
	state->supplyCount[c] = 0;
	r = isGameOver(state);
	assert(r == 1);

	for (a = 0; a < 25; a++) {
		state->supplyCount[a] = 1;
	}
	r = isGameOver(state);
	assert(r == 0);
}

int main() {
//	int k[10] = { adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village};
	struct gameState state;

	SelectStream(2);
	PutSeed(3);
	int j, i, p;
	for (i = 0; i < 2000; i++) {
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*) &state)[j] = floor(Random() * 256);
		}
		for (p = 0; p < MAX_PLAYERS; p++) {
			state.deckCount[p] = floor(Random() * MAX_DECK);
			state.discardCount[p] = floor(Random() * MAX_DECK);
			state.handCount[p] = floor(Random() * MAX_HAND);
		}
		state.whoseTurn = floor(Random() * MAX_PLAYERS);
		testGameOver(&state);
	}
	printf("No errors encountered in 2000 tests of isGameOver(). \n");
	return 0;
}
