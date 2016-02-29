/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the Adventurer card.
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

int testAdventurerCard(int player, struct gameState *after)
{
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	int initialHand = before.handCount[player];
	int treasures = 0;
	int cards, i;
	int temp[MAX_HAND];

	while (treasures < 2) 
	{
		if (before.discardCount[player] == 0 && before.deckCount[player] == 0) 
		{
			printf("The discard count and deck counts didn't = 0. \n");
//			assert(checkVal == -1);
			return 1;
		}

		drawCard(player, &before);
		cards = before.hand[player][before.handCount[player] - 1];

		if (cards == copper || cards == silver || cards == gold) 
		{
			treasures++;

		}
		else 
		{
			temp[i] = cards;
			before.handCount[player]--;
			i++;
		}
	}


	while (i - 1 >= 0)
	{
		before.discard[player][before.discardCount[player]++] = temp[i - 1];
		i--;
	}

	if (memcmp(&before, after, sizeof(struct gameState)) != 0)
	{
		printf("The memory was different before and after. \n");
	}
//	assert(memcmp(&before, after, sizeof(struct gameState)) == 0);
	if (initialHand == after->handCount[player] - 2)	
	{
		printf("Cards didn't get discarded. \n");
	}
//	assert(hand == after->handCount[player] - 2);
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

		p = floor(Random() * 2);
		state.whoseTurn = p;

		state.deckCount[p] = floor(Random() * (MAX_DECK));
		for (j = 0; j < state.deckCount[p]; j++) 
		{
			state.deck[p][j] = floor(Random() * (treasure_map + 1));
		}

		state.handCount[p] = floor(Random() * (MAX_DECK - 4));
		for (j = 0; j < state.handCount[p]; j++) 
		{
			state.hand[p][j] = floor(Random() * (treasure_map + 1));
		}

		state.discardCount[p] = floor(Random() * (MAX_DECK));
		for (j = 0; j < state.discardCount[p]; j++) 
		{
			state.discard[p][j] = floor(Random() * (treasure_map + 1));
		}

		testAdventurerCard(p, &state);
	}

	printf("No errors found in tests of Adventurer Card \n");

	return 0;
}
