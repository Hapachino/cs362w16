/*
 * cardtest2.c
 *
 * test of card Adventurer as implemented in function:
 *
 * void playAdventurer( int currentPlayer, struct gameState *state )
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Adventurer should add 2 cards to the player's hand, both of which should be
 * treasure cards.
 */

int testAdventurer( struct gameState *pre, int currentPlayer );
struct gameState* newGameState( int numPlayers, int seed );

int main()
{
	struct gameState *g = 0;
	int i, j, player, numPlayers, seed, testCount = 0, failCount = 0;

	fprintf( stdout, "\n**********\ncardtest2\n\nTesting Adventurer card:\n" );

	// test newly initialized game with 2 players

	for (i = 0; i < 1000; i++) {
		numPlayers = rand() % ( MAX_PLAYERS - 2 ) + 2;
		seed = time( 0 );
		g = newGameState( numPlayers, seed );
		player = rand() % numPlayers;

		for (j = 0; j < player; j++) {
			endTurn( g );
		}

		if (testAdventurer( g, player )) {
			failCount++;
			fprintf( stdout, "\tnumPlayers=%d, seed=%d, player=%d\n\n\n", numPlayers, seed,
					player );
		} else {
			fprintf( stdout, "Pass\tnumPlayers=%d, seed=%d, player=%d\n\n\n", numPlayers, seed,
					player );
		}
		/*
		 else
		 {
		 fprintf( stdout, "Pass\n" );
		 }
		 */
		testCount++;
	}
	fprintf( stdout, "\n%d tests, %d failures.\n\n**********\n\n", testCount, failCount );
	free( g );
	return 0;
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

int testAdventurer( struct gameState *pre, int player )
{
	struct gameState *post;
	int i, j, card, preCardCount, postCardCount, fail = 0;
	int *preCards, *postCards;

	post = (struct gameState*) malloc( sizeof(struct gameState) );
	memcpy( post, pre, sizeof(struct gameState) );

	int* th = (int*) malloc( MAX_HAND * sizeof(int) );

	playAdventurer( player, 0, -1, th, post );

	free( th );

	// player should have 2 additional treasure cards in hand
	if (post->handCount[player] != 2 + pre->handCount[player]) {
		if (fail == 0)
			fprintf( stdout, "FAILURE\n" );
		fail = 1;
		fprintf( stdout, "\tproblem: hand count incorrect\n" );
	} else {
		for (i = post->handCount[player] - 1; i >= post->handCount[player] - 2; i--) {
			card = post->hand[player][i];
			if (card == copper || card == silver || card == gold)
				continue;
			else {
				if (fail == 0)
					fprintf( stdout, "FAILURE\n" );
				fail = 1;
				fprintf( stdout, "\tproblem: last 2 cards in hand are not treasure\n" );
			}
		}
	}

	// all cards in the player's possession (among all piles) should not be changed
	preCardCount = pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player];
	postCardCount = post->deckCount[player] + post->discardCount[player] + post->handCount[player];
	if (preCardCount != postCardCount) {

		if (fail == 0)
			fprintf( stdout, "FAILURE\n" );
		fail = 1;
		fprintf( stdout, "\tproblem: player's total card count changed\n" );
		if(preCardCount > postCardCount)
			fprintf( stdout, "\tproblem: player has lost cards\n" );
		if(preCardCount < postCardCount)
			fprintf( stdout, "\tproblem: player has gained cards\n" );

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
			preCards[i] = post->discard[player][j];
			i++;
		}
		qsort( (void*) ( postCards ), postCardCount, sizeof(int), compare );
		qsort( (void*) ( preCards ), preCardCount, sizeof(int), compare );

		for (i = 0; i < postCardCount; i++) {
			if (preCards[i] != postCards[i]) {
				if (fail == 0)
					fprintf( stdout, "FAILURE\n" );
				fail = 1;
				fprintf( stdout, "\tproblem: post-game player's cards are different\n" );
			}
		}
		free( preCards );
		free( postCards );
		free( post );
	}

	if (fail) {
		printf( "FAIL\n" );
	} else {
		printf( "pass\n" );
	}
	fprintf( stdout, "Pre-game hand:\n\t" );
	for (i = 0; i < pre->handCount[player]; i++) {
		fprintf( stdout, "%d\t", pre->hand[player][i] );
	}
	fprintf( stdout, "Count: %d\n", pre->handCount[player] );

	fprintf( stdout, "Pre-game deck:\n\t" );
	for (i = 0; i < pre->deckCount[player]; i++) {
		fprintf( stdout, "%d\t", pre->deck[player][i] );
	}
	fprintf( stdout, "Count: %d\n", pre->deckCount[player] );

	fprintf( stdout, "Pre-game discard:\n\t" );
	for (i = 0; i < pre->discardCount[player]; i++) {
		fprintf( stdout, "%d\t", pre->discard[player][i] );
	}
	fprintf( stdout, "Count: %d\n", pre->discardCount[player] );

	return fail;
}
