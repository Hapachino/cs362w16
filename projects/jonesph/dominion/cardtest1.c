/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the Village card.
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

#define NOISY_TEST 1

int testVillageCard(int player, struct gameState *after, int position)
{
	int i;
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	i = cardEffect(village, 0, 0, 0, after, position, 0);

	//village: + 1 card and + 2 actions
	drawCard(player, &before);
	before.numActions = before.numActions + 2;

	discardCard(position, player, &before, 0);

	if (i != 0)
	{
		printf("The Village card didn't work properly. \n");
	}
//	assert(i == 0);

	if (after->handCount[player] != before.handCount[player])
	{
		printf("The hand counts differed. \n");
	}
//	assert(after->handCount[player] == before.handCount[player]);

	if (memcmp(&before, after, sizeof(struct gameState)) != 0)
	{
		printf("The gamestate memory sizes didn't match. \n");
	}
//	assert(memcmp(&before, after, sizeof(struct gameState)) == 0);

	if (memcmp(after->deck[player], before.deck[player], sizeof(after->deck[player])) != 0)
	{
		printf("The player deck memory sizes didn't match. \n");
	}
//	assert(memcmp(after->deck[player], before.deck[player], sizeof(after->deck[player])) == 0);

	return 0;
}

int main()
{
	int i, j, p, position;
	struct gameState state;

	SelectStream(2);
	PutSeed(3);

	for (i = 0; i < 2000; i++)
	{
		for (j = 0; j < sizeof(struct gameState); j++)
		{
			((char*)&state)[j] = floor(Random() * 256);
		}
		p = floor(Random() * 4);

		position = floor(Random() * 20);
		state.deckCount[p] = floor(Random() * MAX_DECK);
		state.discardCount[p] = floor(Random() * MAX_DECK);
		state.playedCardCount = floor(Random() * MAX_DECK);
		state.handCount[p] = floor(Random() * MAX_HAND);
		state.whoseTurn = p;
		state.numActions = floor(Random() * 1);

		for (j = 0; j < treasure_map; j++)
		{
			state.supplyCount[j] = floor(Random() * 25);
		}

		for (j = 0; j < state.handCount[p]; j++)
		{
			state.hand[p][j] = floor(Random() * MAX_HAND);
		}

		for (j = 0; j < state.discardCount[p]; j++)
		{
			state.discard[p][j] = floor(Random() * MAX_DECK);
		}

		for (j = 0; j < state.deckCount[p]; j++)
		{
			state.deck[p][j] = floor(Random() * MAX_DECK);
		}

		for (j = 0; j < state.playedCardCount; j++)
		{
			state.playedCards[j] = floor(Random() * MAX_DECK);
		}

		testVillageCard(p, &state, position);
	}

	printf("No errors found in tests of Village Card \n");

	return 0;
}