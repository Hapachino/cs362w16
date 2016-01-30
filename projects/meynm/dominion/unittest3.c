/*
 * unittest3.c
 *
 * test of function:
 *
 * int gainCard( int supplyPos, struct gameState *state, int toFlag, int player )
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 100

int testGainCard( int numPlayers, int numRuns );

int main()
{
	int i, result, anyErrors = 0;
	for (i = 2; i <= MAX_PLAYERS; i++)
	{
		result = testGainCard( i, 5000 );
		if (result == 0)
			continue;
		else if (result == 1)
			anyErrors = 1;
		else
		{
			fprintf( stdout, "Error in Testing\n" );
			return 1;
		}
	}
	if(anyErrors)
		fprintf(stdout, "Some tests failed.\n");
	else
		fprintf(stdout, "All tests passed.\n");
	return 0;
}

int testGainCard( int numPlayers, int numRuns )
{
	int i, j, used = 0, player, card, toFlag, result, expectedResult, errFlag = 0, anyError = 0;
	int k[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};/* = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute,
			smithy };*/
	struct gameState pre, post;
	const int r = treasure_map - adventurer;

	for(i = 0; i < 10;)
	{
		card = rand() % r + adventurer;
		for(j = 0; j < 10; j++)
		{
			if(k[j] == card) {
				used = 1;
				break;
			}
			else
				used = 0;
		}
		if(used)
			continue;
		else {
			k[i] = card;
			i++;
		}
	}

	initializeGame( numPlayers, k, SEED, &pre );
	memcpy( &post, &pre, sizeof(struct gameState) );

	for (i = 0; i < numRuns; i++)
	{
		player = rand() % ( numPlayers );
		card = rand() % ( treasure_map + 1 );
		toFlag = rand() % 3;

		if (post.supplyCount[card] < 1)
			expectedResult = -1;
		else
			expectedResult = 0;

		result = gainCard( card, &post, toFlag, player );

		if (result != expectedResult)
			errFlag = 1;

		if (result == 0)
		{
			switch ( toFlag ) {
			case 0:
				if (post.discardCount[player] != 1 + pre.discardCount[player])
					errFlag = 1;
				if (post.discard[player][post.discardCount[player] - 1] != card)
					errFlag = 1;
				break;
			case 1:
				if (post.deckCount[player] != 1 + pre.deckCount[player])
					errFlag = 1;
				if (post.deck[player][post.deckCount[player] - 1] != card)
					errFlag = 1;
				break;
			case 2:
				if (post.handCount[player] != 1 + pre.handCount[player])
					errFlag = 1;
				if (post.hand[player][post.handCount[player] - 1] != card)
					errFlag = 1;
				break;
			default:
				return -1;
			}
		}

		if (errFlag)
		{
			fprintf( stdout, "numPlayers=%d, player=%d, card=%d, toFlag=%d: FAIL\n",
					numPlayers, player, card, toFlag );
			fprintf(stdout, "i=%d\n", i);
			anyError = 1;
		}

		memcpy( &pre, &post, sizeof(struct gameState) );
	}
	return anyError;
}
