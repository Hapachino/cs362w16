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
	int i, j, s, numPlayers;
	int k[10];

	for(i = 0; i < 10; i++)
	{
		// play with a random set of cards, random # of players
		for(j = 0; j < 10; j++)
		{
			k[j] = rand() % t;
		}
		s = rand();
		numPlayers = rand() % MAX_PLAYERS + 1;

		fprintf(stdout, "shuffle test with %d players: ", numPlayers);

		// test shuffle()
		if(testShuffle(numPlayers, k, s) == 0)
			fprintf(stdout, "PASS\n");
		else
			fprintf(stdout, "FAIL\n");
	}
	return 0;
}

int testShuffle( int numPlayers, int k[], int seed )
{
	int i, j;
	struct gameState pre, post;

	initializeGame( numPlayers, k, seed, &pre );
	memcpy( &post, &pre, sizeof(struct gameState) );

	// shuffle all decks in post state
	for(i = 0; i < numPlayers; i++)
	{
		shuffle(i, &post);
	}

	// sort decks in both states
	for(i = 0; i < numPlayers; i++)
	{
		qsort( (void*)(&pre.deck[i]), pre.deckCount[i], sizeof(int), compare );
	}
	for(i = 0; i < numPlayers; i++)
	{
		qsort( (void*)(&post.deck[i]), post.deckCount[i], sizeof(int), compare );
	}

	// test if the cards are all there
	for(i = 0; i < numPlayers; i++)
	{
		for(j = 0; j < pre.deckCount[i]; j++)
		{
			if(post.deck[i][j] != pre.deck[i][j])
				return 1;
		}
	}

	return 0;
}
