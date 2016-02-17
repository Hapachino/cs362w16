/*
 * randomtestcard.c
 * random testing feast card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int testFeastCard(int card, struct gameState *g, int curplayer, int streamIdx, int randomSeed);

int main(void) {
	puts("Random Testing Feast Card");

	int numOfIteration = 500;
	int streamidx = 2;
	int randomseed = 1 + floor(Random() * (treasure_map + 1));
	SelectStream(streamidx);
	PutSeed(randomseed);

	struct gameState G;
	int cnt, i, player;

	for (cnt = 0; cnt < numOfIteration; ++cnt) {
		//for (i = 0; i < sizeof(struct gameState); ++i)
			//((char*)&G)[i] = floor(Random()*256);

		// set a game
		G.numPlayers = 2;
		player = floor(Random() * 2); // number of players is 2

		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);

		// set cards on the deck
		for (i = 0; i < G.deckCount[player]; ++i)
			G.deck[player][i] = floor(Random() * (treasure_map + 1));
		// set cards discarded
		for (i = 0; i < G.discardCount[player]; ++i)
			G.discard[player][i] = floor(Random() * (treasure_map + 1));
		// set cards on hand
		for (i = 0; i < G.handCount[player]; ++i)
			G.hand[player][i] = floor(Random() * (treasure_map + 1));

		// test Feast Card
		testFeastCard(feast, &G, player, streamidx, randomseed);
	}

	printf("Random Testing Feast Card done..\n");

	return 0;
}


int testFeastCard(int card, struct gameState *g, int currentPlayer, int streamIdx, int randomSeed) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));

	SelectStream(streamIdx);
	PutSeed(randomSeed);

	int temphand[MAX_HAND]; // moved above the if statement
	int choice1 = -1, i;

	int result = cardEffect(card, choice1, 0, 0, g, 0, 0);

	PutSeed(randomSeed);
	// gain card with cost up to 5
	// backup hand
	for (i = 0; i <= g2.handCount[currentPlayer]; ++i) {
		temphand[i] = g2.hand[currentPlayer][i]; // backup card
		g2.hand[currentPlayer][i] = -1; // set to nothing
	}

	// update coins for buy
	updateCoins(currentPlayer, &g2, 5);

	int x = 1; // condition to loop on
	while (x == 1) { // buy one card
		if (supplyCount(choice1, &g2) <= 0) {
			if (DEBUG) printf("None of that card left, sorry!\n");
			if (DEBUG) printf("Cards Left: %d\n", supplyCount(choice1, &g2));
		}
		else if (g2.coins < getCost(choice1)) {
			printf("That card is too expensive!\n");
			if (DEBUG) printf("Coins: %d < %d\n", g2.coins, getCost(choice1));
		}
		else {
			if (DEBUG) printf("Deck Count: %d\n", g2.handCount[currentPlayer] +
					g2.deckCount[currentPlayer] + g2.discardCount[currentPlayer]);

			gainCard(choice1, &g2, 0, currentPlayer); // gain the card
			x = 0; // no more buying cards

			if (DEBUG) printf("Deck Count: %d\n", g2.handCount[currentPlayer] +
					g2.deckCount[currentPlayer] + g2.discardCount[currentPlayer]);
		}
	}

	// reset hand
	for (i = 0; i <= g2.handCount[currentPlayer]; ++i) {
		g2.hand[currentPlayer][i] = temphand[i];
		temphand[i] = -1;
	}

	// check if g and g2 are the same each other
	assert(g2.deckCount[currentPlayer] == g->deckCount[currentPlayer]);
	assert(g2.discardCount[currentPlayer] == g->discardCount[currentPlayer]);
	assert(g2.handCount[currentPlayer] == g->handCount[currentPlayer]);

	assert(memcmp(&g2, g, sizeof(struct gameState)) == 0);
	assert(result == 0);
	if (result != 0) printf("Feast Card test failed!\n");
	//else printf("Feast Card test passed!\n");

	return 0;
}
