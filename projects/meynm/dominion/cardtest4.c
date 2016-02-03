/*
 * cardtest4.c
 *
 * test of card Steward as implemented in function:
 *
 * void playSteward(int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2, int choice3)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SEED 1000

struct gameState* newGameState( int numPlayers, int seed );
int testSteward( int player, struct gameState *g, int handPos, int effect, int trash1, int trash2 );

int main()
{
	struct gameState *g = 0;
	int i, j, testCount = 0, failCount = 0, handPos, player, effect, trash1pos, trash2pos,
			numPlayers;

	fprintf( stdout, "\n**********\ncardtest4\n\nTesting Steward card:\n\n" );

	// Test 1: +2 cards
	fprintf( stdout, "Test 1: Player 3 chooses to draw 2 cards: " );
	g = newGameState( 4, SEED );
	player = 3;
	handPos = 3;
	effect = 1;
	trash1pos = 0;
	trash2pos = 0;

	// make it this player's turn
	for (i = 0; i < player; i++)
	{
		endTurn( g );
	}

	testCount++;
	if (testSteward( player, g, handPos, effect, trash1pos, trash2pos ))
	{
		fprintf( stdout, "\tFAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "pass\n" );
	}
	free( g );

	// Test 2: +2 coins
	fprintf( stdout, "Test 2: Player 0 chooses 2 coins: " );
	g = newGameState( 4, SEED );
	player = 0;
	handPos = 0;
	effect = 2;
	trash1pos = 0;
	trash2pos = 0;

	testCount++;
	if (testSteward( player, g, handPos, effect, trash1pos, trash2pos ))
	{
		fprintf( stdout, "\tFAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "pass\n" );
	}
	free( g );

	// Test 3: throw out 2 cards
	fprintf( stdout, "Test 3: Player 1 puts 2 cards in trash: " );
	g = newGameState( 4, SEED );
	player = 1;
	handPos = 0;
	effect = 3;
	trash1pos = 1;
	trash2pos = 2;

	// make it this player's turn
	for (i = 0; i < player; i++)
	{
		endTurn( g );
	}

	testCount++;
	if (testSteward( player, g, handPos, effect, trash1pos, trash2pos ))
	{
		fprintf( stdout, "\tFAIL\n" );
		failCount++;
	} else
	{
		fprintf( stdout, "pass\n" );
	}
	free( g );

	// random tests
	fprintf(stdout, "\nDoing random tests...\n");
	for (i = 0; i < 100000; i++)
	{
		numPlayers = rand() % ( MAX_PLAYERS - 2 ) + 2;
		g = newGameState( numPlayers, SEED );
		player = rand() % numPlayers;

		// make it this player's turn
		for (j = 0; j < player; j++)
		{
			endTurn( g );
		}

		handPos = rand() % ( g->handCount[player] );
		effect = rand() % 4;
		trash1pos = g->handCount[player];
		trash2pos = g->handCount[player] + 1;
		g->handCount[player] += 2;

		testCount++;
		if (testSteward( player, g, handPos, effect, trash1pos, trash2pos ))
		{
			fprintf( stdout, "player=%d, handPos=%d, effect=%d, trash1pos=%d, trash2pos=%d: FAIL\n",
					player, handPos, effect, trash1pos, trash2pos );
			failCount++;
		}
		free( g );
	}

	fprintf( stdout, "\n%d tests, %d failures.\n\n**********\n\n", testCount, failCount );
	return 0;
}

int testSteward( int player, struct gameState *g, int handPos, int effect, int trash1, int trash2 )
{
	struct gameState *pre, *post;
	int i, j, trashCard1, trashCard2, trash1Count, trash2Count, trash1PostCount, trash2PostCount,
			preCardCount, postCardCount, fail = 0;
	int *preCards, *postCards;

	pre = g;
	post = (struct gameState*) malloc( sizeof(struct gameState) );
	memcpy( post, pre, sizeof(struct gameState) );

	playSteward( player, post, handPos, effect, trash1, trash2 );

	switch ( effect ) {
	case 1:
		// should have drawn 2 cards and got rid of 1
		if (post->handCount[player] != 1 + pre->handCount[player])
		{
			fail = 1;
			fprintf( stdout, "\tproblem: hand count is wrong.\n" );
		}
		// should have 2 fewer cards in deck
		if (post->deckCount[player] != pre->deckCount[player] - 2)
		{
			fprintf( stdout, "\tproblem: deck count is wrong.\n" );
			fail = 1;
		}
		break;

	case 2:
		// should have same cards, should have 2 more coins
		if (post->handCount[player] != pre->handCount[player] - 1)
		{
			fail = 1;
			fprintf( stdout, "\tproblem: hand count is wrong.\n" );
		}
		// should have the same number of cards in deck
		if (post->deckCount[player] != pre->deckCount[player])
		{
			fprintf( stdout, "\tproblem: deck count is wrong.\n" );
			fail = 1;
		}
		break;

	default:
		// player should have 3 fewer cards in hand
		if (post->handCount[player] != pre->handCount[player] - 3)
		{
			fail = 1;
			fprintf( stdout, "\tproblem: hand count is wrong.\n" );
		}
		// should have 2 fewer total cards
		if (post->deckCount[player] + post->discardCount[player] + post->handCount[player]
				!= pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player] - 2)
		{
			fprintf( stdout, "\tproblem: incorrect total number of cards found.\n" );
			fail = 1;
		}
		// we'll look at which cards are missing in a moment
		break;
	}

	// add up all cards in player's possession
	preCardCount = pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player];
	postCardCount = post->deckCount[player] + post->discardCount[player] + post->handCount[player];
	preCards = (int*) malloc( preCardCount * sizeof(int) );
	postCards = (int*) malloc( postCardCount * sizeof(int) );
	// put every card in post player's possession in postCards
	for (i = 0; i < post->handCount[player]; i++)
	{
		postCards[i] = post->hand[player][i];
	}
	for (j = 0; j < post->deckCount[player]; j++)
	{

		postCards[i] = post->deck[player][j];
		i++;
	}
	for (j = 0; j < post->discardCount[player]; j++)
	{
		postCards[i] = post->discard[player][j];
		i++;
	}
	// put every card in pre player's possession in preCards
	for (i = 0; i < pre->handCount[player]; i++)
	{
		preCards[i] = pre->hand[player][i];
	}
	for (j = 0; j < pre->deckCount[player]; j++)
	{
		preCards[i] = pre->deck[player][j];
		i++;
	}
	for (j = 0; j < pre->discardCount[player]; j++)
	{
		preCards[i] = post->discard[player][j];
		i++;
	}
	qsort( (void*) ( postCards ), postCardCount, sizeof(int), compare );
	qsort( (void*) ( preCards ), preCardCount, sizeof(int), compare );

	// if one of the first two options was chosen, player's set of cards should not be changed
	if (effect == 1 || effect == 2)
	{
		if (postCardCount != preCardCount)
			fail = 1;
		else
		{
			for (i = 0; i < postCardCount; i++)
			{
				if (preCards[i] != postCards[i])
					fail = 1;
			}
		}
	} else
	{
		// if the last option chosen, there should be 1 fewer of each card put in the trash
		trashCard1 = pre->hand[player][trash1];
		trashCard2 = pre->hand[player][trash2];
		trash1Count = 0;
		trash2Count = 0;
		trash1PostCount = 0;
		trash2PostCount = 0;

		// count the occurrences of trash cards, pre and post
		for (i = 0; i < preCardCount; i++)
		{
			if (preCards[i] == trashCard1)
				trash1Count++;
			if (preCards[i] == trashCard2)
				trash2Count++;
		}
		for (i = 0; i < postCardCount; i++)
		{
			if (postCards[i] == trashCard1)
				trash1PostCount++;
			if (postCards[i] == trashCard2)
				trash2PostCount++;
		}
		if (trashCard1 != trashCard2)
		{
			if (trash1PostCount != trash1Count - 1)
				fail = 1;
			if (trash2PostCount != trash2Count - 1)
				fail = 1;
		} else
		{
			if (trash1PostCount != trash1Count - 2)
				fail = 1;
		}
	}

	free( preCards );
	free( postCards );
	free( post );
	return fail;
}

struct gameState* newGameState( int numPlayers, int seed )
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
	initializeGame( numPlayers, k, seed, g );
	return g;
}
