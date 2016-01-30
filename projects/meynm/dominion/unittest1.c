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

struct testInput {
	int numPlayers, whichPlayer, playerBuys, playerMoney, cardToBuy;
};

int testCount;

int testBuyCard( int numPlayers, int whichPlayer, int playerBuys, int playerMoney, int cardToBuy );

int main()
{
	int i, j, k, l, m, failuresThisTry = 0, failureCount = 0;

	testCount = 0;

	fprintf( stdout, "\nTesting buyCard()\n\n" );

	for (i = 0; i <= treasure_map; i++)					// which card
	{
		for (j = 2; j < MAX_PLAYERS; j++)				// how many players
		{
			for (k = 0; k < j; k++)						// which player
			{
				for (l = 1; l <= 13; l++)				// how many buys to start with
				{
					for (m = 1; m < START_MONEY; m++)    // money to start with
					{
						failuresThisTry = testBuyCard( j, k, l, m, i );
						if (failuresThisTry)
						{
							failureCount += failuresThisTry;
							failuresThisTry = 0;
						}
					}
				}
			}
		}
	}
	fprintf( stdout, "%d tests run.\n", testCount );
	if (failureCount)
	{
		fprintf( stdout, "%d Problems found.\n\n", failureCount );
	} else
	{
		fprintf( stdout, "All tests passed.\n\n" );
	}
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
	int i, found = 0, result, expectedResult, failFlag = 0, failCount = 0, maxBuys;
	int k[10] = {
			adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy
	};
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
			k[0] = cardToBuy;
	}
	initializeGame( numPlayers, k, SEED, &pre );
	pre.coins = playerMoney;
	pre.whoseTurn = whichPlayer;
	pre.numBuys = playerBuys;
	memcpy( &post, &pre, sizeof(struct gameState) );

	// try to buy all the cards of type cardToBuy, and then one more!
	maxBuys = 1 + post.supplyCount[cardToBuy];
	for (i = 0; i <= maxBuys; i++)
	{
		if (playerBuys < 1 || getCost( cardToBuy ) > playerMoney || post.supplyCount[cardToBuy] < 1)
			expectedResult = -1;
		else
			expectedResult = 0;

		result = buyCard( cardToBuy, &post );
		testCount++;
		if (result != expectedResult)
			failFlag = 1;

		if (result == 0)	// if buy was successful, check postconditions
		{
			// update our own variables
			playerMoney -= getCost( cardToBuy );
			--playerBuys;

			// check whether postconditions have been met
			if (post.coins != playerMoney)
				failFlag = 1;
			if (post.numBuys != playerBuys)
				failFlag = 1;
			if (post.supplyCount[cardToBuy] != pre.supplyCount[cardToBuy] - 1)
				failFlag = 1;
			if (post.discardCount[whichPlayer] != 1 + pre.discardCount[whichPlayer])
				failFlag = 1;
			else
			{
				if (post.discard[whichPlayer][post.discardCount[whichPlayer] - 1] != cardToBuy)
					failFlag = 1;
			}
		}
		else	// if buy unsuccessful, check to make sure nothing was changed
		{
			if (memcmp( &pre, &post, sizeof(struct gameState) ) != 0)
				failFlag = 1;
		}

		if (failFlag)
		{
			fprintf( stdout,
					"Player %d of %d attempts to buy Card #%d with %d coins and %d buys:\tFAIL\n",
					whichPlayer, numPlayers, cardToBuy, playerMoney, playerBuys );
			failCount++;
		}
		memcpy( &pre, &post, sizeof(struct gameState) );
		failFlag = 0;
	}
	return failCount;
}
