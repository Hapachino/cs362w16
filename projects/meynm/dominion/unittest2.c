/*
 * unittest2.c
 *
 * unit test of function:
 *
 * int shuffle( int player, struct gameState *state )
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FAILURES 1000

int testShuffle( int numPlayers, int k[], int seed );

int main()
{
	const int t = treasure_map + 1;
	int i, j, s, numPlayers, card, used = 0;
	int k[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	const int r = treasure_map - adventurer;

	// use a random set of cards
	for (i = 0; i < 10;)
	{
		card = rand() % r + adventurer;
		for (j = 0; j < 10; j++)
		{
			if (k[j] == card)
			{
				used = 1;
				break;
			} else
				used = 0;
		}
		if (used)
			continue;
		else
		{
			k[i] = card;
			i++;
		}
	}

	for (i = 0; i < 10; i++)
	{
		s = rand();
		numPlayers = rand() % ( MAX_PLAYERS - 1 ) + 2;

		fprintf( stdout, "shuffle test with %d players: ", numPlayers );

		// test shuffle() with random # of players
		if (testShuffle( numPlayers, k, s ) == 0)
			fprintf( stdout, "PASS\n" );
		else
			fprintf( stdout, "FAIL\n" );
	}
	return 0;
}

int testShuffle( int numPlayers, int k[], int seed )
{
	int i, j, result, expectedResult, same = 1, oneCard = 1;
	struct gameState pre, post;

	initializeGame( numPlayers, k, seed, &pre );
	memcpy( &post, &pre, sizeof(struct gameState) );

	// shuffle all decks in post state
	for (i = 0; i < numPlayers; i++)
	{
		if (post.deckCount[i] < 1)
			expectedResult = -1;
		else
			expectedResult = 0;

		if (post.deckCount[i] > 1)
			oneCard = 0;

		result = shuffle( i, &post );
		if (result != expectedResult)
			return 1;
	}

	// if all the cards are in the same place, probably something wrong
	if (!oneCard)
	{
		for (i = 0; i < numPlayers; i++)
		{
			for (j = 0; j < pre.deckCount[i]; j++)
			{
				if (post.deck[i][j] != pre.deck[i][j])
					same = 0;
			}
		}
		if (same)
		{
			fprintf( stdout, "Probable Failure: The decks do not appear to have been shuffled.\n" );
			return 1;
		}
	}

	// sort decks in both states
	for (i = 0; i < numPlayers; i++)
	{
		qsort( (void*) ( &pre.deck[i] ), pre.deckCount[i], sizeof(int), compare );
	}
	for (i = 0; i < numPlayers; i++)
	{
		qsort( (void*) ( &post.deck[i] ), post.deckCount[i], sizeof(int), compare );
	}

	// test if the cards are all there
	for (i = 0; i < numPlayers; i++)
	{
		for (j = 0; j < pre.deckCount[i]; j++)
		{
			if (post.deck[i][j] != pre.deck[i][j])
				return 1;
		}
	}

	return 0;
}
