/*
 * randomtestadventurer.c
 *
 * randomized test of card Adventurer as implemented in function:
 *
 * void playAdventurer( int currentPlayer, struct gameState *state )
 *
 * Adventurer should add 2 cards to the player's hand, both of which should be
 * treasure cards.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int testAdventurer( struct gameState *pre, int currentPlayer );
struct gameState* newGameState( int numPlayers, int seed );
int testOtherData( struct gameState *pre, struct gameState *post, int ignorePlayer );

int main()
{
	struct gameState *g = 0;
	int i, j, player, numPlayers, sizeHand, sizeDeck, seed, treasure, testCount = 0, failCount = 0;

	fprintf( stdout, "\n**********\nrandomtestadventurer\n\nTesting Adventurer card:\n" );

	// test newly initialized game with 2 players

	for (i = 0; i < 1000; i++) {
		numPlayers = rand() % ( MAX_PLAYERS - 1 ) + 2;
		seed = time( 0 );
		g = newGameState( numPlayers, seed );
		player = rand() % numPlayers;

		// create random player deck
		// test huge deck counts, completely random ones, and normal ones
		if (testCount % 4 == 0) {
			sizeDeck = rand() % MAX_DECK / 2;
		} else if (testCount % 4 == 1) {
			sizeDeck = rand() % ( MAX_DECK - 100 );
		} else if (testCount % 4 == 2) {
			sizeDeck = rand() % 50 + 5;
		} else {
			sizeDeck = 10;
		}
		if (sizeDeck < 10)
			sizeDeck = 10;
		g->deckCount[player] = sizeDeck;
		treasure = 0;
		for (j = 0; j < sizeDeck; j++) {
			if (j > sizeDeck / 2 && treasure < 2) {
				g->deck[player][j] = rand() % 3 + copper;
				treasure++;
			} else {
				g->deck[player][j] = rand() % ( treasure_map + 1 );
				if (g->deck[player][j] == copper || g->deck[player][j] == silver
						|| g->hand[player][j] == gold) {
					treasure++;
				}
			}
		}
		for (j = 0; j < numPlayers + player; j++)	// make it this player's turn
				{
			endTurn( g );
		}
		// test small hand counts, large hand counts, and completely random ones
		if (testCount % 3 == 0) {
			sizeHand = rand() % sizeDeck / 2;
		} else if (testCount % 3 == 1) {
			sizeHand = rand() % sizeDeck;
		} else {
			sizeHand = 5;
		}
		if (sizeHand < 5)
			sizeHand = 5;
		g->handCount[player] = sizeHand;
		for (j = g->handCount[player]; j < sizeHand; j++) {
			if (g->handCount[player] < sizeDeck)
				drawCard( player, g );
		}

		if (testAdventurer( g, player )) {
			failCount++;
			fprintf(
					stdout, "params: numPlayers=%d, player=%d, deck count=%d, hand count=%d\n"
					"***************************************\n\n",
					numPlayers, player, sizeDeck, sizeHand
			);
		}
		/*else
		 {
		 fprintf( stdout, "numPlayers=%d, player=%d, deck count=%d, hand count=%d: pass\n",
		 numPlayers, player, sizeDeck, sizeHand );
		 }*/
		testCount++;
		free( g );
	}
	fprintf( stdout, "\n\n%d test cases\n%d test cases failed.\n\n**********\n\n", testCount,
			failCount );
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

	int* th = (int*)malloc(MAX_HAND * sizeof(int));

	playAdventurer( player, 0, -1, th, post );

	free(th);

	// player should have 2 additional treasure cards in hand
	if (post->handCount[player] != 2 + pre->handCount[player]) {
		if (fail == 0)
			fprintf( stdout, "*************** FAILURE ***************.\n" );
		fail = 1;
		fprintf( stdout, "problem: player hand count is incorrect.\n" );
	} else {
		for (i = post->handCount[player] - 1; i >= post->handCount[player] - 2; i--) {
			card = post->hand[player][i];
			if (card == copper || card == silver || card == gold)
				continue;
			else {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: drawn cards are not of correct type.\n" );
			}
		}
	}
	// set of cards in the player's possession (union of all piles) should not be changed
	preCardCount = pre->deckCount[player] + pre->discardCount[player] + pre->handCount[player];
	postCardCount = post->deckCount[player] + post->discardCount[player] + post->handCount[player];
	if (preCardCount != postCardCount) {
		if (fail == 0)
			fprintf( stdout, "*************** FAILURE ***************.\n" );
		fail = 1;
		fprintf( stdout,
				"problem: pre- and post-gameState have different total player card count.\n" );
	} else {
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
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: Player has gained or lost cards.\n" );
			}
		}
	}
	if (testOtherData( pre, post, player )) {
		if (fail == 0)
			fprintf( stdout, "*************** FAILURE ***************.\n" );
		fail = 1;
		fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
	}

	free( preCards );
	free( postCards );
	free( post );
	if (fail)
		return 1;
	else
		return 0;
}

int testOtherData( struct gameState *pre, struct gameState *post, int ignorePlayer )
{
	int i, j, fail = 0;
	// test the parts of the game state that should not have changed
	for (i = 0; i < treasure_map + 1; i++) {
		if (post->embargoTokens[i] != pre->embargoTokens[i]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
		}
		if (post->supplyCount[i] != pre->supplyCount[i]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
		}
	}
	if (pre->numPlayers != post->numPlayers || pre->outpostPlayed != post->outpostPlayed
			|| pre->whoseTurn != post->whoseTurn || pre->phase != post->phase
			|| pre->numActions != post->numActions || pre->numBuys != post->numBuys) {
		if (fail == 0)
			fprintf( stdout, "*************** FAILURE ***************.\n" );
		fail = 1;
		fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
	}

	// test other players' game state data
	for (i = 0; i < pre->numPlayers; i++)	// for each player
			{
		if (i == ignorePlayer)				// (except the current one)
			continue;

		// test for no changes
		if (post->handCount[i] != pre->handCount[i] || post->deckCount[i] != pre->deckCount[i]
				|| post->discardCount[i] != pre->discardCount[i]) {
			if (fail == 0)
				fprintf( stdout, "*************** FAILURE ***************.\n" );
			fail = 1;
			fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
		}

		for (j = 0; j < pre->handCount[i]; j++) {
			if (post->hand[i][j] != pre->hand[i][j]) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
			}
		}
		for (j = 0; j < pre->deckCount[i]; j++) {
			if (post->deck[i][j] != pre->deck[i][j]) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
			}
		}
		for (j = 0; j < pre->discardCount[i]; j++) {
			if (post->discard[i][j] != post->discard[i][j]) {
				if (fail == 0)
					fprintf( stdout, "*************** FAILURE ***************.\n" );
				fail = 1;
				fprintf( stdout, "problem: Unrelated gameState data corrupted.\n" );
			}
		}
	}
	return fail;
}
