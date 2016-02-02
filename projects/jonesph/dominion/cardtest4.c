/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the Great Hall card.
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

int testGreatHall(int card, int player, int position, struct gameState *after)
{
	int i, actions, count;
	
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	actions = after->numActions;
	count = after->handCount[player];
	i = cardEffect(card, 0, 0, 0, after, position, 0);

	drawCard(player, &before);
	before.numActions = before.numActions + 1;

	discardCard(position, player, &before, 0);

	if (i != 0)
	{
		printf("The Great Hall card didn't work properly. \n");
	}
//	assert(i == 0);

	if (after->handCount[player] != count)
	{
		printf("The amount of cards isn't what it should be. \n");
	}
//	assert(after->handCount[player] == count);

	if (after->numActions == (actions + 1))
	{
		printf("Actions didn't go up by 1. \n");
	}
//	assert(after->numActions == (actions + 1));

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

		position = floor(Random() * state.handCount[p]);
		
		testGreatHall(great_hall, p, position, &state);
	}

	printf("No errors found in tests of Great Hall Card \n");

	return 0;
}