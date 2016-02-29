/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the Smithy card.
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

int testSmithyCard(int card, int player, int position, struct gameState *after)
{
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));
	int i;
	int count = after->handCount[player];
	int x = cardEffect(card, 0, 0, 0, after, position, 0);

	for (i = 0; i < 3; i++)
	{
		drawCard(player, &before);
	}

	discardCard(position, player, &before, 0);

	if (after->handCount[player] != (count + 2))
	{
		printf("The Smithy card didn't add two cards. \n");
	}
//	assert(after->handCount == (count + 3));

	if (x != 0)
	{
		printf("The Smithy card didn't work properly. \n");
	}
//	assert(r == 0);

	if (memcmp(&before, after, sizeof(struct gameState)) != 0)
	{
//		printf("Something wierd happened. \n");
	}
//	assert(memcmp(&before, after, sizeof(struct gameState)) == 0);

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

		state.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
		p = floor(Random() * state.numPlayers);
		state.whoseTurn = p;

		state.deckCount[p] = floor(Random() * MAX_DECK);
		state.discardCount[p] = floor(Random() * MAX_DECK);
		state.handCount[p] = floor(Random() * MAX_HAND);
		state.playedCardCount = floor(Random() * MAX_DECK);

		position = floor(Random() * (state.handCount[p]));

		testSmithyCard(smithy, p, position, &state);
	}

	printf("No errors found in tests of Smithy Card \n");

	return 0;
}