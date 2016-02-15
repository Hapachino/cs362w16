/*
 * randomtestadventurer.c
 * random testing adventurer card
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int testAdventurerCard(int card, struct gameState *g, int curplayer, int streamIdx, int randomSeed);

int main(void) {
	puts("Random Testing Adventurer Card");

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

		// test Adventurer Card
		testAdventurerCard(adventurer, &G, player, streamidx, randomseed);
	}

	printf("Random Testing Adventurer Card done..\n");

	return 0;
}


int testAdventurerCard(int card, struct gameState *g, int currentPlayer, int streamIdx, int randomSeed) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));

	int temphand[MAX_HAND]; // moved above the if statement
	int drawntreasure = 0, cardDrawn, z = 0; // this is the counter for the temp hand

	SelectStream(streamIdx);
	PutSeed(randomSeed);

	int result = cardEffect(card, 0, 0, 0, g, 0, 0);

	PutSeed(randomSeed);

	while (drawntreasure < 2) {
		if (g2.deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &g2);

		drawCard(currentPlayer, &g2);
		cardDrawn = g2.hand[currentPlayer][g2.handCount[currentPlayer] - 1]; // top card of hand is most recently drawn card

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			g2.handCount[currentPlayer]--; // this should just remove the top card (the most recently drawn one)
			z++;
		}
	}

	while (z - 1 >= 0) {
		g2.discard[currentPlayer][g2.discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
		z--;
	}

	// check if g and g2 are the same each other
	assert(g2.deckCount[currentPlayer] == g->deckCount[currentPlayer]);
	assert(g2.discardCount[currentPlayer] == g->discardCount[currentPlayer]);
	assert(g2.handCount[currentPlayer] == g->handCount[currentPlayer]);

	assert(memcmp(&g2, g, sizeof(struct gameState)) == 0);
	assert(result == 0);
	if (result != 0) printf("Adventurer Card test failed!\n");
	//else printf("Adventurer Card test passed!\n");

	return 0;
}
