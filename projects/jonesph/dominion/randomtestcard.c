/********************
* Author: Philip Jones
* Term: Winter 2016
* Description: Does random tests on the Feast card.
********************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int randomFeast(int player, struct gameState *after, int position, int trash)
{
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));

	int i, j, k;
	int card = feast;
	int firstChoice = 0;
	int secondChoice = 0;
	int thirdChoice = 0;
	int bonus = 0;
	int temp[MAX_HAND];
	
	player = before.whoseTurn;
	j = cardEffect(card, firstChoice, secondChoice, thirdChoice, after, position, &bonus);

	for (i = 0; i <= before.handCount[player]; i++)
	{
		temp[i] = before.hand[player][i];
		before.hand[player][i] = -1;
	}

	before.coins = 0;

	for (i = 0; i < before.handCount[player]; i++)
	{
		if (before.hand[player][i] == copper)
		{
			before.coins += 1;
		}
		else if (before.hand[player][i] == silver)
		{
			before.coins += 2;
		}
		else if (before.hand[player][i] == gold)
		{
			before.coins += 3;
		}
	}
//bonus
	before.coins += 5;

	k = 1;
	while (k == 1)
	{
		if (supplyCount(firstChoice, &before) <= 0)
		{
			k = 0;
		}
		else if (before.coins < getCost(firstChoice))
		{
			k = 0;
		}
		else
		{
			if (firstChoice < 0)
			{
				return -1;
			}

			before.discard[player][before.discardCount[player]] = firstChoice;
			before.discardCount[player]++;

			before.supplyCount[firstChoice]--;
			k = 0;
		}
	}

	for (i = 0; i <= before.handCount[player]; i++)
	{
		before.hand[player][i] = temp[i];
		temp[i] = -1;
	}

	before.playedCards[before.playedCardCount] = before.hand[player][position];
	before.playedCardCount++;
	before.hand[player][position] = -1;

	if (position == (before.handCount[player] - 1))
	{
		before.handCount[player]--;
	}
	else if (before.handCount[player] == 1)
	{
		before.handCount[player]--;
	}
	else
	{
		before.hand[player][position] = before.hand[player][(before.handCount[player] - 1)];
		before.hand[player][before.handCount[player] - 1] = -1;
		before.handCount[player]--;
	}

//	assert(j == 0);
	printf("Error in cardEffect. \n");

//	assert(memcmp(&before, after, sizeof(struct gameState)) == 0);
	printf("Error in memory comparison. \n");

	return 0;
}

int main()
{
	int i, j, k, p;
	int trash, position, count, seed, players;

	struct gameState state;
	int card[10] = { adventurer, baron, council_room, feast, gardens, great_hall, mine, remodel, smithy, village };

	SelectStream(2);
	PutSeed(3);
	srand(time(NULL));

	for (count = 0; count < 200; count++)
	{
		seed = rand();
		players = 5;

		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&state)[i] = floor(Random() * 256);
		}

		initializeGame(players, card, seed, &state);

		state.numPlayers = players;
		p = floor(Random() * (players - 1));
		state.whoseTurn = p;

		for (j = 0; j < players - 1; j++)
		{
			state.deckCount[j] = floor(Random() * MAX_DECK);
			for (k = 0; k < state.deckCount[j]; k++)
			{
				state.deck[j][k] = floor(Random() * 26);
			}

			state.discardCount[j] = floor(Random() * MAX_DECK);
			for (k = 0; k < state.discardCount[j]; k++)
			{
				state.discard[j][k] = floor(Random() * 26);
			}

			state.handCount[j] = rand() % MAX_HAND + 1;
			for (k = 0; k < state.handCount[j]; k++)
			{
				state.hand[j][k] = floor(Random() * 26);
			}

			for (k = 0; k < 26; k++)
			{
				state.supplyCount[k] = floor(Random() * 26) + 1;
			}
		}

		state.playedCardCount = floor(Random() * MAX_DECK);
		for (k = 0; k < state.playedCardCount; k++)
		{
			state.playedCards[k] = floor(Random() * 26) + 1;
		}

		if (state.handCount[p] < 1)
		{
			exit(-1);
		}

		state.coins = floor(Random() * 20);
		position = floor(Random() * MAX_HAND);
		trash = floor(Random() * 1);
		randomFeast(p, &state, position, trash);
	}
	printf("No errors encountered \n");

	return 0;
}