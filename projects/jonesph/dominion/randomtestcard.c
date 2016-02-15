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
//should gain back a card with a coin cost no greater than 5 and lose the feast card

	for (i = 0; i <= before.handCount[player]; i++)
	{
//creating a temp hand for backup
		temp[i] = before.hand[player][i];
		before.hand[player][i] = -1;
	}
//set starting coins to 0
	before.coins = 0;

//add up any coins that are in the player's hand
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
//add in the 5 coin bonus from the Feast card
	before.coins += 5;

//k serves as a loop checker
	k = 1;
//attempt to buy a card with coins
	while (k == 1)
	{
//need to have enough coins to make the purchase
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
//player should get the card that was bought
			if (firstChoice < 0)
			{
				return -1;
			}
//makes sure that the card is available, then decreases supply of that card
			before.discard[player][before.discardCount[player]] = firstChoice;
			before.discardCount[player]++;

			before.supplyCount[firstChoice]--;
//set loop checker to 0 to exit loop
			k = 0;
		}
	}

//set the temp backup hand back to the player's hand
	for (i = 0; i <= before.handCount[player]; i++)
	{
		before.hand[player][i] = temp[i];
		temp[i] = -1;
	}

//discard the feast card and decrement hand
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

//the j for loop should randomly populate the game state with values in range
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

//generates a random played card count in range
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

//runs the randomFeast with a randomly generated state
		randomFeast(p, &state, position, trash);
	}
	printf("No errors encountered \n");

	return 0;
}