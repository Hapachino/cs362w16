/*
 * unittest1.c
 *
 * unit test of function:
 *
 * int buyCard( int supplyPos, struct gameState *state )
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 100
#define MAX_FAILURES 1000
#define START_MONEY 10

struct testInput
{
	int numPlayers, whichPlayer, playerBuys, playerMoney, cardToBuy;
};

int testBuyCard( int numPlayers, int whichPlayer, int playerBuys, int playerMoney, int cardToBuy );

int main()
{
	struct testInput * failureInputs = (struct testInput*)malloc(
			MAX_FAILURES * sizeof(struct testInput)
	);
	int i, j, k, l, m, failureCount = 0;

	for(i = 0; i <= treasure_map; i++)					// which card
	{
		printf("i = %d", i);
		for(j = 2; j < MAX_PLAYERS; j++)				// how many players
		{
			printf("j = %d", j);
			for(k = 0; k < j; k++)						// which player
			{
				for(l = 0; l <= 13; l++)				// how many buys to start with
				{
					for(m = 0; m < START_MONEY; m++)	// money to start with
					{
						if(testBuyCard(j, k, l, m, i) == -1) {
							failureInputs[failureCount].numPlayers = j;
							failureInputs[failureCount].whichPlayer = k;
							failureInputs[failureCount].playerBuys = l;
							failureInputs[failureCount].playerMoney = m;
							failureInputs[failureCount].cardToBuy = i;
							failureCount++;
						}
					}
				}
			}
		}
	}
	if(failureCount) {
		fprintf(stdout, "Problems found for inputs:\n\n");
	}
	for(i = 0; i < failureCount; i++)
	{
		fprintf(stdout, "number of players:\t%d\nwhich player:\t%d\n# of buys:\t%d\nMoney:\t%d\nCard:\t%d\n",
				failureInputs[failureCount].numPlayers,
				failureInputs[failureCount].whichPlayer,
				failureInputs[failureCount].playerBuys,
				failureInputs[failureCount].playerMoney,
				failureInputs[failureCount].cardToBuy
		);
	}
	if(failureCount)
		return 1;
	else
		return 0;
}

/*
 * testBuyCard
 *
 * attempts to buy all available card of specified type and then 1 more card
 *
 * numPlayers		int			how many players in game (2 ... MAX_PLAYERS)
 * whichPlayer		int			which player buys card (0 ... numPlayers - 1)
 * playerMoney		int			how much money the player should start with
 * cardToBuy		int 		which card to buy
 */
int testBuyCard( int numPlayers, int whichPlayer, int playerBuys, int playerMoney, int cardToBuy )
{
	int i, found = 0, result, expectedResult, allPass = 1;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
			smithy };
	struct gameState pre, post;

	// if cardToBuy is a k-card and is not in our initial set of k-cards, make
	// a substitution
	if (cardToBuy >= adventurer && cardToBuy <= treasure_map)
	{
		for (i = 0; i < 10; i++)
		{
			if (k[i] == cardToBuy)
			{
				found = 1;
				break;
			}
		}
		if (!found)
		{
			k[0] = cardToBuy;
		}
	}

	initializeGame( numPlayers, k, SEED, &pre );
	memcpy( &post, &pre, sizeof(struct gameState) );
	pre.coins = playerMoney;
	pre.whoseTurn = whichPlayer;
	pre.numBuys = playerBuys;

	if (playerBuys < 1 || getCost( cardToBuy ) > playerMoney)
		expectedResult = -1;
	else
		expectedResult = 0;

	for (i = 0; i <= pre.supplyCount[cardToBuy]; i++)
	{
		if (playerBuys < 1 || getCost( cardToBuy ) > playerMoney || pre.supplyCount[cardToBuy] < 1)
			expectedResult = -1;
		else
			expectedResult = 0;

		fprintf(stdout, "Player %d of %d attempts to buy Card #%d with %d coins and %d buys:\t",
				whichPlayer, numPlayers, cardToBuy, playerMoney, playerBuys);

		result = buyCard(cardToBuy, &pre);

		if(result == expectedResult) {
			fprintf(stdout, "CORRECT\n");
		}
		else {
			fprintf(stdout, "INCORRECT\n");
			allPass = 0;
		}
		if(result == 0) {
			playerMoney -= getCost(cardToBuy);
			--playerBuys;
		}
	}
	if(allPass)
		return 0;
	else
		return -1;
}
