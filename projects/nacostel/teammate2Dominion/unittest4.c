/*
* Test for buyCard function.
* buyCard() returns 0 if shuffle was successful.
* testShuffle shuffles the post gamestate and compares results between
* pre and post to make sure the function works correctly.
* Some code has been sourced from lecture videos.
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Sends intentional errors to buyCard and tests return value against expected value.
// Replicates buyCard function. Uses pre/post state from lecture to compare
// expected results. result should == 0 for successful shuffle.
int testBuy(int player, int card, struct gameState *post, int test)
{
	struct gameState pre;
	// Copy current game state
	memcpy(&pre, post, sizeof(struct gameState));
	// Call buyCard on post game state
	int result = buyCard(card, post);

	// Emulate buyCard function
	pre.handCount[player]++;
	pre.coins = pre.coins - getCost(card);
	pre.numBuys--;
	pre.supplyCount[card]--;

	// Test results of buyCard call on post
	if (test == 1) // Test for correct numBuys
	{
		if (result != -1)
			printf("***Error found: player has no more buys left, function returned 0.\n");
	}
	else if (test == 2)	// Test for number of remaining cards
	{
		if (result != -1)
			printf("***Error found: supply count is 0, function returned 0.\n");
	}
	else if (test == 3)	// Test for having enough coins to purchase
	{
		if (result != -1)
			printf("***Error found: not enough of coins, function returned 0.\n");
	}
	else if (result != 0)	// Test for all other cases other than 1 or others returned
		printf("***Error found: function returned something other than 0 / -1.\n");
	else   // Tests to compare for pre/post condtions (buyCard returned 0)
	{
		if (post->handCount[player] != pre.handCount[player])	// handCount should increase
			printf("***Error found: number of cards in hand did not increase.\n");
		if (post->coins != pre.coins)	// coins should be decreased by cost of card
			printf("***Error found: number of coins not decreased.\n");
		if (post->numBuys != pre.numBuys)	// numBuys should be decreased
			printf("***Error found: number of buys not changed.\n");
		if (post->supplyCount[card] != pre.supplyCount[card])	// supplyCount should be decreased
			printf("***Error found: supply count was not reduced.\n");
	}

	return 0;
}

void fillCards(struct gameState *G)
{
	int i;
	for (i = 0; i < treasure_map; i++)
	{
		G->supplyCount[i] = 5;
	}
}

int main()
{
	int p = 0;
	struct gameState G;
	int i, j, k;
	int fail_condition;
	int card;

	SelectStream(2);
	PutSeed(3);

	printf("Testing...\n");

	for (i = 0; i < sizeof(struct gameState); i++) { // Create random game state
		((char*)&G)[i] = floor(Random() * 256);
	}

	// Fill cards in supplyCount
	fillCards(&G);
	
	//fill in some decks
	G.numPlayers = 2;
	G.whoseTurn = p;
	G.deck[p][0] = gold; //one card in deck
	G.deckCount[p] = 1;

	G.hand[p][0] = silver; //one card in hand
	G.handCount[p] = 1;

	G.discard[p][0] = copper; //one card discarded
	G.discardCount[p] = 1;

	G.coins = 5000;

	printf("===  numBuys = 0  ===\n\n");
	G.numBuys = 0;
	fail_condition = 1;
	testBuy(p, gold, &G, fail_condition);

	printf("===  supplyCount = 0  ===\n\n");
	for (k = 0; k < 100; k++)
	{
		card = floor(Random() * treasure_map) + 1;
		G.numBuys = 1000;//allow buys again
		G.supplyCount[card] = 0;
		fail_condition = 2;
		testBuy(p, card, &G, fail_condition);
	}

	for (j = 0; j <= treasure_map; j++)
	{
		G.supplyCount[j] = 100;
	}

	printf("===  coins = 0  ===\n\n");
	G.coins = 0;
	fail_condition = 3;
	testBuy(p, province, &G, fail_condition);

	printf("===  without intentional fail condition  ===\n\n");
	for (k = 0; k < 100; k++)
	{
		card = floor(Random() * sea_hag) + 1;
		//actually buy something now
		G.coins = 50;
		fail_condition = 0;
		testBuy(p, card, &G, fail_condition);
	}

	return 0;
}
