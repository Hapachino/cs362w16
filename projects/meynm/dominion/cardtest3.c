/*
 * cardtest3.c
 *
 * test of card Mine as implemented in function:
 *
 * int playMine( int currentPlayer, struct gameState *state, int handPos, int choice1, int choice2 )
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SEED 1000

struct gameState* newGameState( int, int );
int testMine( struct gameState *, int, int, int, int );

int main()
{
	struct gameState *g = 0;
	int i, testCount = 0, failCount = 0, handPos, player, trashPos, gainCard;

	fprintf( stdout, "\n**********\n\ncardtest3\n\nTesting Mine card:\n" );

	// -------- Test 1 --------
	// test with 2 players, player 1 plays card properly
	fprintf( stdout, "2 players, player 1 exchanges copper in p.0 for silver. Mine in last pos: " );
	g = newGameState( 2, SEED );
	player = 1;
	// make it this player's turn
	for (i = 0; i < player; i++)
	{
		endTurn( g );
	}
	trashPos = 0;							// we will get rid of the first card in player's hand
	g->hand[player][trashPos] = copper;		// let that card be copper
	gainCard = silver;						// replace it with silver
	// last card in hand will be mine
	g->hand[player][g->handCount[player]] = mine;
	handPos = g->handCount[player]++;
	testCount++;
	if (testMine( g, player, handPos, trashPos, gainCard ))
	{
		failCount++;
		fprintf( stdout, "\tFAIL\n\n" );
	} else
		fprintf( stdout, "pass\n\n" );

	// -------- Test 2 --------
	// test with 4 players, player 3 plays card illegally
	fprintf( stdout,
			"4 players, player 3 exchanges copper in p.3 for treasure map. Mine in p.2: " );
	free( g );
	g = newGameState( 4, SEED );
	player = 3;
	for (i = 0; i < player; i++)
	{
		endTurn( g );
	}
	trashPos = 3;
	g->hand[player][trashPos] = copper;
	gainCard = treasure_map;
	g->hand[player][2] = mine;
	handPos = 2;
	testCount++;
	if (testMine( g, player, handPos, trashPos, gainCard ))
	{
		failCount++;
		fprintf( stdout, "\tFAIL\n\n" );
	} else
		fprintf( stdout, "pass\n\n" );

	// -------- Test 3 --------
	// test with 3 players, player 0 plays card legally, replacing silver with gold
	fprintf( stdout, "3 players, player 0 exchanges silver in p.4 for gold. Mine in p.0: " );
	free( g );
	g = newGameState( 3, SEED );
	player = 0;
	trashPos = 4;							// we will get rid of the first card in player's hand
	g->hand[player][trashPos] = silver;		// let that card be silver
	gainCard = gold;						// replace it with gold
	g->hand[player][0] = mine;
	handPos = 0;
	testCount++;
	if (testMine( g, player, handPos, trashPos, gainCard ))
		{
			failCount++;
			fprintf( stdout, "\tFAIL\n\n" );
		} else
			fprintf( stdout, "pass\n\n" );

	// -------- Test 4 --------
	// test with 2 players, player 0 plays card illegally
	fprintf( stdout, "2 players, player 0 exchanges silver in p.9 for gold. Mine in p.0: " );
	free( g );
	g = newGameState( 2, SEED );
	player = 0;
	trashPos = 9;							// should not be allowed: the player has only 5 cards
	g->hand[player][trashPos] = silver;
	gainCard = gold;						// replace it with gold
	g->hand[player][0] = mine;
	handPos = 0;
	testCount++;
	if (testMine( g, player, handPos, trashPos, gainCard ))
		{
			failCount++;
			fprintf( stdout, "\tFAIL\n\n" );
		} else
			fprintf( stdout, "pass\n\n" );

	// -------- Test 5 --------
	// test with 4 players, player 2 plays card illegally
	fprintf( stdout, "4 players, player 2 exchanges copper in p.1 for gold. Mine in p.4: " );
	free( g );
	g = newGameState( 4, SEED );
	player = 2;
	trashPos = 1;
	g->hand[player][trashPos] = copper;
	gainCard = gold;						// should not be allowed: costs too much
	g->hand[player][4] = mine;
	handPos = 4;
	testCount++;
	if (testMine( g, player, handPos, trashPos, gainCard ))
		{
			failCount++;
			fprintf( stdout, "\tFAIL\n\n" );
		} else
			fprintf( stdout, "pass\n\n" );

	fprintf( stdout, "\n%d tests, %d failures\n\n**********\n\n", testCount, failCount );
	return 0;
}

// choice1 is card position in player's hand, choice2 is card enum of desired card
int testMine( struct gameState *g, int player, int handPos, int trashPos, int gainCard )
{
	struct gameState *pre, *post;
	int i, j, trashCard, preTrashCount = 0, postTrashCount = 0, preGainCount = 0, postGainCount = 0,
			result, expectedResult = 0, fail = 0;

	pre = g;
	post = (struct gameState*) malloc( sizeof(struct gameState) );
	memcpy( post, pre, sizeof(struct gameState) );
	trashCard = pre->hand[player][trashPos];

	// card to get rid of must be a treasure card
	if (!( trashCard == copper || trashCard == silver || trashCard == gold ))
		expectedResult = -1;
	// card to gain must be a treasure card
	if (!( gainCard == copper || gainCard == silver || gainCard == gold ))
		expectedResult = -1;
	// card to gain must cost no more than 3 greater than card traded in
	if (getCost( gainCard ) > 3 + getCost( post->hand[player][trashPos] ))
		expectedResult = -1;
	// the mine must be in the player's hand
	if (handPos < 0 || handPos >= pre->handCount[player])
		expectedResult = -1;
	// so must the trash card
	if (trashPos < 0 || trashPos >= pre->handCount[player])
		expectedResult = -1;

	result = playMine( player, post, handPos, trashPos, gainCard );
	if (result != expectedResult)
	{
		fprintf( stdout,
				"\n\tproblem: unexpected return value\n\tparameters: player=%d, handPos=%d, trashPos=%d, gainCard=%d\n",
				player, handPos, trashPos, gainCard );
		return 1;
	}

	// ------------------------------
	// test the postconditions
	// if the card couldn't be played, the game state should not be altered
	if (result == -1)
	{
		if (memcmp( pre, post, sizeof(struct gameState) ) == 0)
			return 0;
		else
			return 1;
	}

	// otherwise, the player should have 1 fewer card in hand than before
	if (post->handCount[player] != pre->handCount[player] - 1)
		fail = 1;
	else
	{
		if (trashCard != gainCard)
		{
			// player should have 1 fewer of trashCard
			for (i = 0; i < pre->handCount[player]; i++)
				if (pre->hand[player][i] == trashCard)
					preTrashCount++;
			for (i = 0; i < post->handCount[player]; i++)
				if (post->hand[player][i] == trashCard)
					postTrashCount++;
			if (postTrashCount != preTrashCount - 1)
				fail = 1;

			// player should have 1 more of gainCard
			for (i = 0; i < pre->handCount[player]; i++)
				if (pre->hand[player][i] == gainCard)
					preGainCount++;
			for (i = 0; i < post->handCount[player]; i++)
				if (post->hand[player][i] == gainCard)
					postGainCount++;
			if (postGainCount != 1 + preGainCount)
				fail = 1;

			if (fail == 0)
			{
				// restore the hand to what it must have been before by exchanging cards
				for (i = 0; i < post->handCount[player]; i++)
				{
					if (post->hand[player][i] == gainCard)
					{
						post->hand[player][i] = trashCard;
						break;
					}
				}
			}
		}
		// and replace the played mine card: Now pre and post hands should contain same cards
		post->hand[player][post->handCount[player]] = mine;
		post->handCount[player]++;
		assert( pre->handCount[player] == post->handCount[player] );

		// sort the hand in pre and post to see if they are the same
		qsort( (void*) ( pre->hand[player] ), pre->handCount[player], sizeof(int), compare );
		qsort( (void*) ( post->hand[player] ), post->handCount[player], sizeof(int), compare );
		for (i = 0; i < pre->handCount[player]; i++)
			if (pre->hand[player][i] != post->hand[player][i])
				fail = 1;
	}

	// post->discard should have only 1 more than pre->discard, because the only the mine is kept
	// this was not originally implemented in dominion.c, but it should be according to the rules
	if (post->discardCount[player] != 1 + pre->discardCount[player])
		fail = 1;
	else
	{
		// restore previous state
		for (i = 0; i < post->discardCount[player]; i++)
		{
			if (post->discard[player][i] == mine)
			{
				post->discard[player][i] = post->discard[player][post->discardCount[player] - 1];
				post->discardCount[player]--;
				break;
			}
		}
		assert( pre->discardCount[player] == post->discardCount[player] );
		// sort and compare; should be the same
		qsort( (void*) ( pre->discard[player] ), pre->discardCount[player], sizeof(int), compare );
		qsort( (void*) ( post->discard[player] ), post->discardCount[player], sizeof(int),
				compare );
		for (i = 0; i < post->discardCount[player]; i++)
			if (pre->discard[player][i] != post->discardCount[player])
				fail = 1;
	}

	if (post->supplyCount[gainCard] != pre->supplyCount[gainCard] - 1)
		fail = 1;
	if (post->supplyCount[gainCard] < 0)
		fail = 1;

	// test the parts of the game state that should not have changed
	for (i = 0; i < treasure_map + 1; i++)
	{
		if (post->embargoTokens[i] != pre->embargoTokens[i])
			fail = 1;
		if (i == gainCard || i == trashCard)
			continue;
		if (post->supplyCount[i] != pre->supplyCount[i])
			fail = 1;
	}

	if (pre->numPlayers != post->numPlayers)
		fail = 1;
	if (pre->outpostPlayed != post->outpostPlayed)
		fail = 1;
	if (pre->whoseTurn != post->whoseTurn)
		fail = 1;
	if (pre->phase != post->phase)
		fail = 1;
	if (pre->numActions != post->numActions)
		fail = 1;
	if (pre->coins != post->coins)
		fail = 1;
	if (pre->numBuys != post->numBuys)
		fail = 1;

	// test other players' game state data
	for (i = 0; i < pre->numPlayers; i++)    // for each player
	{
		if (i == player)					// (except the current one)
			continue;

		// test for no changes
		if (post->handCount[i] != pre->handCount[i])
			fail = 1;
		if (post->deckCount[i] != pre->deckCount[i])
			fail = 1;
		if (post->discardCount[i] != pre->discardCount[i])
			fail = 1;

		for (j = 0; j < pre->handCount[i]; j++)
		{
			if (post->hand[i][j] != pre->hand[i][j])
				fail = 1;
		}
		for (j = 0; j < pre->deckCount[i]; j++)
		{
			if (post->deck[i][j] != pre->deck[i][j])
				fail = 1;
		}
		for (j = 0; j < pre->discardCount[i]; j++)
		{
			if (post->discard[i][j] != post->discard[i][j])
				fail = 1;
		}
	}

	if (fail)
	{
		fprintf( stdout,
				"\n\tproblem: postconditions not met:\n\tparameters: player=%d, handPos=%d, trashPos=%d, gainCard=%d\n",
				player, handPos, trashPos, gainCard );
		return 1;
	} else
		return 0;
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
