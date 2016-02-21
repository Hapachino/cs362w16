/* -----------------------------------------------------------------------
	* Testing buyCard()
	* This function checks if the player meets conditions to buy a card
	* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testBuyCard(int player, int card, struct gameState *post, int test)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	int r = buyCard(card, post);
	
	pre.handCount[player]++;
	pre.coins = pre.coins - getCost(card);
	pre.numBuys--;
	pre.supplyCount[card]--;
	
	if(test == 1) //expecting a fail
	{
		if(r != -1)
		{
			printf("ERROR: buyCard should have failed from numBuys = 0.\n\n");
		}
	}
	else if(test == 2)
	{
		if(r != -1)
		{
			printf("ERROR: buyCard should have failed from supplyCount = 0.\n\n");
		}
	}
	else if(test == 3)
	{
		if(r != -1)
		{
			printf("ERROR: buyCard should have failed from coins < cost.\n\n");
		}
	}
	else if(r != 0 )
	{
		printf("ERROR: buyCard failed.\n\n");
	}
	else
	{
		if(post->handCount[player] != pre.handCount[player])
		{
			printf("ERROR: hand count did not increase with buy.\n\n");
		}
		if(post->coins != pre.coins)
		{
			printf("ERROR: Coins was not decremented by cost of card.\n\n");
		}
		if(post->numBuys != pre.numBuys)
		{
			printf("ERROR: numBuys was not decremented.\n\n");
		}
		if(post->supplyCount[card] != pre.supplyCount[card])
		{
			printf("ERROR: supply count for card not decremented.\n\n");
		}
	}
	
	return 0;
}

int main()
{
	int p = 0;
	struct gameState G;
	int i, j, k;
	int fail;
	int card;
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing buyCard() unittest4.\n");
	
	for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	//first fill up all cards
	for(j = 0; j <= treasure_map; j++)
	{
		G.supplyCount[j] = 5;
	}
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
	
	printf("Testing: numBuys = 0...\n");
	G.numBuys = 0;
	fail = 1;
	testBuyCard(p, gold, &G, fail);
	
	printf("Testing: supplyCount == 0...\n");
	for(k = 0; k < 100; k++)
	{
		card = floor(Random() * treasure_map) + 1;
		G.numBuys = 1000;//allow buys again
		G.supplyCount[card] = 0;
		fail = 2;
		testBuyCard(p, card, &G, fail);
	}
	
	for(j = 0; j <= treasure_map; j++)
	{
		G.supplyCount[j] = 100;
	}
	
	printf("Testing: coins == 0...\n");
	G.coins = 0;
	fail = 3;
	testBuyCard(p, province, &G, fail);
	
	printf("Testing: buying cards...\n");
	for(k = 0; k < 100; k++)
	{
		card = floor(Random() * sea_hag) + 1;
		//actually buy something now
		G.coins = 50;
		fail = 0;
		testBuyCard(p, card, &G, fail);
	}
	
	return 0;
}