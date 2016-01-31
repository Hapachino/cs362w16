/*
 * unittest4.c
 *
 * test of function:
 *
 * int fullDeckCount( int player, int card, struct gameState *state )
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 100

int testFullDeckCount( int numPlayers, int whichPlayer, int runs );

int main()
{
	int i, j, runReq = 1000, runCount = 0, failCount = 0;

	for (i = 2; i <= MAX_PLAYERS; i++)
	{
		for (j = 0; j < 100; j++)
		{
			failCount += testFullDeckCount( i, rand() % i, runReq );
			runCount += runReq;
		}
	}

	fprintf( stdout, "%d tests, %d failures\n", runCount, failCount );
	return 0;
}

int testFullDeckCount( int numPlayers, int whichPlayer, int runs )
{
	int i, j, pos, card, deck, hand, discard, runCount = 0, failCount = 0;
	const int r = treasure_map - adventurer;
	struct gameState g;

	for (i = 0; i < runs; i++)
	{
		memset( &g, -1, sizeof(struct gameState) );
		card = rand() % ( 1 + treasure_map );
		deck = rand() % 50;
		hand = rand() % 50;
		discard = rand() % 50;
		j = 0;
		for (j = 0; j < deck;)
		{
			pos = rand() % MAX_DECK;
			if (1 + pos > g.deckCount[whichPlayer])
			{
				g.deckCount[whichPlayer] = 1 + pos;
			}
			if (g.deck[whichPlayer][pos] != card)
			{
				g.deck[whichPlayer][pos] = card;
				//g.deckCount[whichPlayer]++;
				j++;
			}
		}
		for (j = 0; j < hand;)
		{
			pos = rand() % MAX_HAND;
			if (1 + pos > g.handCount[whichPlayer])
			{
				g.handCount[whichPlayer] = 1 + pos;
			}
			if (g.hand[whichPlayer][pos] != card)
			{
				g.hand[whichPlayer][pos] = card;
				//g.handCount[whichPlayer]++;
				j++;
			}
		}
		for (j = 0; j < discard;)
		{
			pos = rand() % MAX_DECK;
			if (1 + pos > g.discardCount[whichPlayer])
			{
				g.discardCount[whichPlayer] = 1 + pos;
			}
			if (g.discard[whichPlayer][pos] != card)
			{
				g.discard[whichPlayer][pos] = card;
				//g.discardCount[whichPlayer]++;
				j++;
			}
		}
		if (deck + hand + discard == fullDeckCount( whichPlayer, card, &g ))
			continue;
		else
		{
			fprintf( stdout, "card = %d, deck = %d, hand = %d, discard = %d: FAIL\n", card, deck,
					hand, discard );
			failCount++;
		}
	}
	return failCount;
}

