/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the buyCard() function.
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

int testBuyCard(int player, struct gameState *after)
{
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	int results = buyCard(player, after);
	int turn = before.whoseTurn;
	int canBuy = 0;
	int cost = getCost(player);

	if (before.numBuys < 0 || before.supplyCount[player] < 1 || before.coins < cost)
	{
		canBuy = -1;
	}

	assert(results == canBuy);

	if (canBuy == 0)
	{
		before.phase = 1;
		before.discard[turn][before.discardCount[turn]] = player;
		before.discardCount[turn]++;
		before.supplyCount[player]--;
	}

	assert(before.phase == after->phase);
	assert(before.discard[turn][before.discardCount[turn]] == after->discard[turn][after->discardCount[turn]]);
	assert(before.discardCount[turn] == after->discardCount[turn]);
	assert(before.supplyCount[player] == after->supplyCount[player]);

	return 0;
}

int main()
{
	int i, j, p, s;
//	int card[10] = { adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village };
	struct gameState state;

	SelectStream(2);
	PutSeed(3);

	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
		{
			((char*)&state)[j] = floor(Random() * 256);
		}

		s = floor(Random() * 10);

		for (p = 0; p < MAX_PLAYERS; p++)
		{
			state.deckCount[p] = floor(Random() * MAX_DECK);
			state.discardCount[p] = floor(Random() * MAX_DECK);
			state.handCount[p] = floor(Random() * MAX_HAND);
		}

		state.whoseTurn = floor(Random() * MAX_PLAYERS);
		testBuyCard(s, &state);
	}
	printf("No errors encountered in 2000 tests of buyCard(). \n");
	return 0;
}