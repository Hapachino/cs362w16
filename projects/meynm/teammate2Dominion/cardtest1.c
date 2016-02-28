/*
 * cardtest1.c
 *
 * test of card Smithy as implemented in function:
 *
 * void playSmithy( int currentPlayer, struct gameState *state, int handPos
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEED 100

int testSmithy( struct gameState *g, int player, int handPos );
struct gameState* newGameState( int numPlayers );

int main()
{
	struct gameState *g = 0;
	int i, testCount = 0, failCount = 0, handPos, player;

	fprintf( stdout, "\n**********\ncardtest1\n\nTesting Smithy card:\n" );

	// basic test with 2 players using newly initialized game state
	g = newGameState( 2 );
	player = 0;
	g->hand[player][g->handCount[player]] = smithy;
	handPos = ( g->handCount[player] )++;
	fprintf( stdout, "Standard game with 2 players: Player 0 plays Smithy: " );
	if (testSmithy( g, player, handPos ))
	{
		fprintf( stdout, "FAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "Pass\n" );
	}
	testCount++;

	// basic test with 4 players using newly initialized game state
	fprintf( stdout, "Standard game with 4 players: Player 2 plays Smithy: " );
	free( g );
	g = newGameState( 4 );
	player = 2;
	g->hand[player][g->handCount[player]] = smithy;
	handPos = ( g->handCount[player] )++;
	if (testSmithy( g, player, handPos ))
	{
		fprintf( stdout, "FAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "Pass\n" );
	}
	testCount++;

	// basic test with 3 players using newly initialized game state
	fprintf( stdout, "Standard game with 3 players: Player 1 plays Smithy: " );
	free( g );
	g = newGameState( 3 );
	player = 1;
	g->hand[player][g->handCount[player]] = smithy;
	handPos = ( g->handCount[player] )++;
	if (testSmithy( g, player, handPos ))
	{
		fprintf( stdout, "FAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "Pass\n" );
	}
	testCount++;

	// test with 3 players, current player has to reshuffle
	fprintf( stdout, "game with 3 players, current player has to reshuffle: " );
	free( g );
	g = newGameState( 3 );
	player = 1;
	g->deckCount[player] = 1;
	g->discardCount[player] = 5;
	for (i = 0; i < 5; i++)
	{
		g->discard[player][i] = rand() % treasure_map;
	}
	g->hand[player][g->handCount[player]] = smithy;
	handPos = ( g->handCount[player] )++;
	if (testSmithy( g, player, handPos ))
	{
		fprintf( stdout, "FAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "Pass\n" );
	}
	testCount++;

	// test with 4 players, current player has too few cards
	fprintf( stdout, "game with 4 players, current player has 2 total cards to draw: " );
	free( g );
	g = newGameState( 4 );
	player = 2;
	g->deckCount[player] = 1;
	g->discardCount[player] = 1;
	for (i = 0; i < 5; i++)
	{
		g->discard[player][i] = rand() % treasure_map;
	}
	g->hand[player][g->handCount[player]] = smithy;
	handPos = ( g->handCount[player] )++;
	if (testSmithy( g, player, handPos ))
	{
		fprintf( stdout, "FAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "Pass\n" );
	}
	testCount++;

	fprintf( stdout, "\n%d tests, %d failures.\n\n**********\n\n", testCount, failCount );
	return 0;
}

struct gameState* newGameState( int numPlayers )
{
	struct gameState *g;
	int i, j, card, used = 0;
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

	g = (struct gameState*) malloc( sizeof(struct gameState) );
	initializeGame( numPlayers, k, SEED, g );
	return g;
}

int testSmithy( struct gameState *g, int player, int handPos )
{
	int noDif = -1;
	struct gameState *pre, *post;
	int *preCards, *postCards;
	int i, j, preCardCount = 0, postCardCount = 0, found, failFlag = 0;
	const int MAX_CARDS = MAX_HAND + MAX_DECK;
	pre = g;
	post = (struct gameState*) malloc( sizeof(struct gameState) );
	memcpy( post, pre, sizeof(struct gameState) );

	//cardEffect(smithy, -1, -1, -1, post, handPos, &noDif);

	smithyEffect(handPos, player, post);

	// new hand count should be old count + 3 new cards - 1 for the smithy
	if (pre->discardCount[player] + pre->deckCount[player] >= 3)
	{
		if (post->handCount[player] != 2 + pre->handCount[player])
			failFlag = 1;
	}
	preCardCount = pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player];
	postCardCount = post->deckCount[player] + post->discardCount[player] + post->handCount[player];

	if (preCardCount != postCardCount)
	{
		failFlag = 1;
	} else
	{
		preCards = (int*) malloc( preCardCount * sizeof(int) );
		postCards = (int*) malloc( postCardCount * sizeof(int) );
		// put every card in post player's possession in postCards
		for (i = 0; i < post->handCount[player]; i++)
		{
			postCards[i] = post->hand[player][i];
		}
		for (j = 0; j < post->deckCount[player]; j++)
		{
			i++;
			postCards[i] = post->deck[player][j];
		}
		for (j = 0; j < post->discardCount[player]; j++)
		{
			i++;
			postCards[i] = post->discard[player][j];
		}
		// put every card in pre player's possession in preCards
		for (i = 0; i < pre->handCount[player]; i++)
		{
			preCards[i] = pre->hand[player][i];
		}
		for (j = 0; j < pre->deckCount[player]; j++)
		{
			i++;
			preCards[i] = pre->deck[player][j];
		}
		for (j = 0; j < pre->discardCount[player]; j++)
		{
			i++;
			preCards[i] = post->discard[player][j];
		}
		qsort( (void*) ( postCards ), postCardCount, sizeof(int), compare );
		qsort( (void*) ( preCards ), preCardCount, sizeof(int), compare );

		for (i = 0; i < postCardCount; i++)
		{
			if (preCards[i] != postCards[i])
				failFlag = 1;
		}
	}

	// test the parts of the game state that should not have changed
	if (memcmp( post, pre, (void*) &post->hand[player][0] - (void*) post ) != 0)
		failFlag = 1;

	if (memcmp( &post->playedCards, &pre->playedCards,
			(void*) &post->playedCardCount - (void*) &post->discardCount[post->numPlayers - 1] )
			!= 0)
	{
		failFlag = 1;
	}

	// test other players' game state data
	for (i = 0; i < pre->numPlayers; i++)    // for each player
	{
		if (i == player)					// (except the current one)
			continue;

		// test for no changes
		if (post->handCount[i] != pre->handCount[i])
			failFlag = 1;
		if (post->deckCount[i] != pre->deckCount[i])
			failFlag = 1;
		if (post->discardCount[i] != pre->discardCount[i])
			failFlag = 1;

		for (j = 0; j < pre->handCount[i]; j++)
		{
			if (post->hand[i][j] != pre->hand[i][j])
				failFlag = 1;
		}
		for (j = 0; j < pre->deckCount[i]; j++)
		{
			if (post->deck[i][j] != pre->deck[i][j])
				failFlag = 1;
		}
		for (j = 0; j < pre->discardCount[i]; j++)
		{
			if (post->discard[i][j] != post->discard[i][j])
				failFlag = 1;
		}
	}

	if (failFlag)
		return 1;
	else
		return 0;
}
