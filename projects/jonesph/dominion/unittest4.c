/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Checks the discardCard() function.
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

int testDiscardCard(int position, int player, struct gameState *after, int trash)
{
	
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	int cardStart = after->playedCardCount;
	int handStart = after->handCount[player];
	int c = discardCard(position, player, after, trash);

	if (trash < 1) //not being trashed
	{
		before.playedCards[before.playedCardCount] = before.hand[player][position];
		before.playedCardCount++;

//		assert(after->playedCardCount == (cardStart + 1));
		if (after->playedCardCount != (cardStart + 1))
		{
			printf ("The discard didn't work as it should have. \n");
		}
	}

	before.hand[player][position] = -1;

	if (position == (before.handCount[player] - 1))
	{
		before.handCount[player]--;

//		assert(after->handCount[player] == (handStart + 1));
		if (after->handCount[player] != (handStart - 1))
		{
			printf("The discard didn't work as it should have. \n");
		}
	}

	else if (before.handCount[player] == 1)
	{
		before.handCount[player]--;

//		assert(after->handCount[player] == (handStart - 1));
		if (after->handCount[player] != (handStart - 1))
		{
			printf("The discard didn't work as it should have. \n");
		}
	}

	else
	{
		before.hand[player][position] = before.hand[player][(before.handCount[player] - 1)];
		before.hand[player][before.handCount[player] - 1] = -1;
		before.handCount[player]--;

//		assert(after->handCount[player] == (handStart - 1));
		if (after->handCount[player] != (handStart - 1))
		{
			printf("The discard didn't work as it should have. \n");
		}
	}
	
	if (c != 0)
	{
		printf("The discard didn't work as it should have. \n");
	}
	//assert(c == 0);

	if (memcmp(&before, after, sizeof(struct gameState)) != 0)
	{
		printf("The discard didn't work as it should have. \n");
	}
	//assert(memcmp(&before, after, sizeof(struct gameState)) == 0);

	return 0;
}

int main()
{
	int i, j, position, trash, player;

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
		player = floor(Random() * state.numPlayers);
		state.whoseTurn = player;

		trash = floor(Random() * 3);

		state.deckCount[player] = floor(Random() * MAX_DECK);
		state.handCount[player] = floor(Random() * MAX_HAND);
		state.discardCount[player] = floor(Random() * MAX_DECK);
		state.playedCardCount = floor(Random() * MAX_DECK);

		position = floor(Random() * state.handCount[player]);

		for (j = 0; j < state.handCount[player]; j++)
		{
			state.hand[player][j] = floor(Random() * (treasure_map + 1));
		}

		for (j = 0; j < state.playedCardCount; j++)
		{
			state.playedCards[j] = floor(Random() * (treasure_map + 1));
		}

		testDiscardCard(position, player, &state, trash);
	}

	printf("No errors encountered in 2000 tests of discardCard(). \n");
	return 0;
}