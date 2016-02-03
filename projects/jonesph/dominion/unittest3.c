/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the shuffle() function.
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

int compareShuffles(const void* x, const void* y) {
	if (*(int*) x > *(int*) y)
		return 1;

	if (*(int*) x < *(int*) y)
		return -1;

	return 0;
}

int testShuffle(int player, struct gameState *after)
{
	int i, j;
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	i = shuffle(player, after);
	j = 0;

	if (before.deckCount[player] < 1)
	{
		j = -1;
	}
	qsort((void*)(before.deck[player]), before.deckCount[player], sizeof(int), compareShuffles);
	if (i != j)
	{
		printf("The shuffle didn't work too well. \n");
		return -1;
	}

	if (i == -1 && before.deck[player] == after->deck[player])
	{
		printf("The shuffle didn't work too well. \n");
		return -1;
	}

	return 0;
}

int main()
{
	int i, j, p;
	struct gameState state;

	SelectStream(2);
	PutSeed(3);

	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
		{
			((char*)&state)[j] = floor(Random() * 256);
		}

		state.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 2));
		state.whoseTurn = floor(Random() * state.numPlayers);
		p = state.whoseTurn;

		state.deckCount[p] = floor(Random() * MAX_DECK);
		state.discardCount[p] = floor(Random() * MAX_DECK);
		state.handCount[p] = floor(Random() * MAX_HAND);

		for (j = 0; j < MAX_HAND; j++)
		{
			state.hand[p][j] = floor(Random() * 26);
			state.deck[p][j] = floor(Random() * 26);
			state.discard[p][j] = floor(Random() * 26);
		}

		if (testShuffle(p, &state) != 0)
		{
			break;
		}
	}
	printf("No errors encountered in 2000 tests of shuffle(). \n");
	return 0;
}