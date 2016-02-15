/*
 * randomtestcard.c
 *
 * random testing of card Steward as implemented in function:
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
int testOtherData( struct gameState *pre, struct gameState *post, int ignorePlayer );

int main()
{
	struct gameState *g = 0;
	int i, j, testCount = 0, failCount = 0, handPos, player, effect, trash1pos, trash2pos, tmpPos =
			0, numPlayers;

	fprintf( stdout, "\n**********\nrandomtestcard\n\nTesting Steward card:\n\n" );

	for (i = 0; i < 1000; i++) {
		numPlayers = rand() % ( MAX_PLAYERS - 1 ) + 2;
		g = newGameState( numPlayers, SEED );
		player = rand() % numPlayers;

		// make it this player's turn
		for (j = 0; j < numPlayers + player; j++) {
			endTurn( g );
		}
		handPos = rand() % ( g->handCount[player] );
		g->hand[player][handPos] = steward;
		effect = rand() % 3;
		trash1pos = -1;
		trash2pos = -1;
		while ( trash1pos == -1 ) {
			tmpPos = rand() % g->handCount[player];
			if (tmpPos != handPos)
				trash1pos = tmpPos;
		}
		while ( trash2pos == -1 ) {
			tmpPos = rand() % g->handCount[player];
			if (tmpPos != handPos && tmpPos != trash1pos)
				trash2pos = tmpPos;
		}

		//trash1pos = g->handCount[player];
		//trash2pos = g->handCount[player] + 1;
		//g->handCount[player] += 2;

		testCount++;
		if (testSteward( player, g, handPos, effect, trash1pos, trash2pos )) {
			fprintf( stdout,
					"PARAMS: player=%d, handPos=%d, effect=%d, trash1pos=%d, trash2pos=%d\n"
							"***************************************\n\n", player, handPos, effect,
					trash1pos, trash2pos );
			failCount++;
		} /*else {
		 fprintf(
		 stdout,
		 "pass\nparams: player=%d, handPos=%d, effect=%d, trash1pos=%d, trash2pos=%d\n\n",
		 player, handPos, effect, trash1pos, trash2pos
		 );
		 }*/
		free( g );
	}

	fprintf( stdout, "\n%d test cases, %d failed test cases.\n\n**********\n\n", testCount, failCount );
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
		// should have drawn 2 cards and got rid of 1 from hand
		if (post->handCount[player] != 1 + pre->handCount[player]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: hand count is wrong.\n" );
		}
		// should have 2 fewer cards in deck
		//if (post->deckCount[player] != pre->deckCount[player] - 2)
		if (post->deckCount[player] + post->handCount[player] + post->discardCount[player]
				!= pre->deckCount[player] + pre->handCount[player] + pre->discardCount[player]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fprintf( stdout, "problem: deck count is wrong.\n" );
			fail = 1;
		}
		break;

	case 2:
		// should have same cards, should have 2 more coins
		if (post->handCount[player] != pre->handCount[player] - 1) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: hand count is wrong.\n" );
		}
		// should have the same number of cards in deck
		if (post->deckCount[player] != pre->deckCount[player]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fprintf( stdout, "problem: deck count is wrong.\n" );
			fail = 1;
		}
		if (post->coins != 2 + pre->coins) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
		}
		break;

	default:
		// player should have 3 fewer cards in hand
		if (post->handCount[player] != pre->handCount[player] - 3) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: hand count is wrong.\n" );
		}
		// should have 2 fewer total cards
		if (post->deckCount[player] + post->discardCount[player] + post->handCount[player]
				!= pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player] - 2)
		{
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fprintf( stdout, "problem: incorrect total number of cards found.\n" );
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
	for (i = 0; i < post->handCount[player]; i++) {
		postCards[i] = post->hand[player][i];
	}
	for (j = 0; j < post->deckCount[player]; j++) {

		postCards[i] = post->deck[player][j];
		i++;
	}
	for (j = 0; j < post->discardCount[player]; j++) {
		postCards[i] = post->discard[player][j];
		i++;
	}
	// put every card in pre player's possession in preCards
	for (i = 0; i < pre->handCount[player]; i++) {
		preCards[i] = pre->hand[player][i];
	}
	for (j = 0; j < pre->deckCount[player]; j++) {
		preCards[i] = pre->deck[player][j];
		i++;
	}
	for (j = 0; j < pre->discardCount[player]; j++) {
		preCards[i] = pre->discard[player][j];
		i++;
	}
	qsort( (void*) ( postCards ), postCardCount, sizeof(int), compare );
	qsort( (void*) ( preCards ), preCardCount, sizeof(int), compare );

	// if one of the first two options was chosen, player's set of cards should not be changed
	if (effect == 1 || effect == 2) {
		if (postCardCount != preCardCount) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout,
					"problem: option 1 or 2 chosen, but player has different number of cards.\n" );
		} else {
			for (i = 0; i < postCardCount; i++) {
				if (preCards[i] != postCards[i]) {
					if (fail == 0)
						fprintf( stdout, "*************** FAILURE ***************.\n" );
					fail = 1;
					fprintf( stdout,
							"problem: option 1 or 2 chosen, but player has different cards.\n" );
				}
			}
		}
	} else {
		// if the last option chosen, there should be 1 fewer of each card put in the trash
		trashCard1 = pre->hand[player][trash1];
		trashCard2 = pre->hand[player][trash2];
		trash1Count = 0;
		trash2Count = 0;
		trash1PostCount = 0;
		trash2PostCount = 0;

		// count the occurrences of trash cards, pre and post
		for (i = 0; i < preCardCount; i++) {
			if (preCards[i] == trashCard1)
				trash1Count++;
			if (preCards[i] == trashCard2)
				trash2Count++;
		}
		for (i = 0; i < postCardCount; i++) {
			if (postCards[i] == trashCard1)
				trash1PostCount++;
			if (postCards[i] == trashCard2)
				trash2PostCount++;
		}
		if (trashCard1 != trashCard2) {
			if (trash1PostCount != trash1Count - 1) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: option 3-->incorrect count for first trash card.\n" );
			}
			if (trash2PostCount != trash2Count - 1) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout,
						"problem: option 3-->incorrect count for second trash card.\n" );
			}
		} else {
			if (trash1PostCount != trash1Count - 2) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: option 3-->incorrect count for trash cards.\n" );
			}
		}
	}
	if (testOtherData( pre, post, player )) {
		if (fail == 0)
			fprintf( stdout, "*************** FAILURE ***************.\n" );
		fail = 1;
		fprintf( stdout, "problem: unrelated game state data has been corrupted.\n" );
	}

	free( preCards );
	free( postCards );
	free( post );
	return fail;
}

int testOtherData( struct gameState *pre, struct gameState *post, int ignorePlayer )
{
	int i, j, fail = 0;
	// test the parts of the game state that should not have changed
	for (i = 0; i < treasure_map + 1; i++) {
		if (post->embargoTokens[i] != pre->embargoTokens[i])
			fail = 1;
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
	if (pre->numBuys != post->numBuys)
		fail = 1;

	// test other players' game state data
	for (i = 0; i < pre->numPlayers; i++)		// for each player
			{
		if (i == ignorePlayer)					// (except the current one)
			continue;

		// test for no changes
		if (post->handCount[i] != pre->handCount[i])
			fail = 1;
		if (post->deckCount[i] != pre->deckCount[i])
			fail = 1;
		if (post->discardCount[i] != pre->discardCount[i])
			fail = 1;

		for (j = 0; j < pre->handCount[i]; j++) {
			if (post->hand[i][j] != pre->hand[i][j])
				fail = 1;
		}
		for (j = 0; j < pre->deckCount[i]; j++) {
			if (post->deck[i][j] != pre->deck[i][j])
				fail = 1;
		}
		for (j = 0; j < pre->discardCount[i]; j++) {
			if (post->discard[i][j] != post->discard[i][j])
				fail = 1;
		}
	}
	return fail;
}

struct gameState* newGameState( int numPlayers, int seed )
{
	struct gameState *g;
	int i, j, card, used = 0;
	int k[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	const int r = treasure_map - adventurer;

// use a random set of cards
	for (i = 0; i < 10;) {
		card = rand() % r + adventurer;
		for (j = 0; j < 10; j++) {
			if (k[j] == card) {
				used = 1;
				break;
			} else
				used = 0;
		}
		if (used)
			continue;
		else {
			k[i] = card;
			i++;
		}
	}

	g = (struct gameState*) malloc( sizeof(struct gameState) );
	initializeGame( numPlayers, k, seed, g );
	return g;
}
