/* -----------------------------------------------------------------------
	* Testing playAdventurer()
	* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testAdventurer(struct gameState *post)
{
	int p = post->whoseTurn;
	int preTreasure, postTreasure;
	int i, j;
	int card;
	struct gameState pre;
	
	memcpy(&pre, post, sizeof(struct gameState));
	
	adventurerCardFunc(post);
	//post deck + discard should be smaller now by 2 treasure cards
	//add these together because discard pile can be shuffled into the deck when drawing cards
	int preTotal = pre.deckCount[p] + pre.discardCount[p] - 2;
	int postTotal = post->deckCount[p] + post->discardCount[p];
	if(postTotal != preTotal)
	{
		printf("ERROR: post total is not 2 treasure cards less than pre total. Pre: %d Post: %d\n", preTotal, postTotal);
	}
	//post hand should 2 greater
	 pre.handCount[p] =  pre.handCount[p]+2;
	if(post->handCount[p] != pre.handCount[p])
	{
		printf("ERROR: pre hand count does not equal post hand count. Pre: %d Post: %d\n", pre.handCount[p], post->handCount[p]);
	}
	
	//should be more treasure cards in hand in post than pre
	for(i = 0; i < pre.handCount[p]; i++)
	{
		card = pre.hand[p][i];
		if (card == copper || card == silver || card == gold)
			preTreasure++;
	}
	for(j = 0; j < post->handCount[p]; j++)
	{
		card = post->hand[p][j];
		if (card == copper || card == silver || card == gold)
			postTreasure++;
	}
	
	if(!(postTreasure > preTreasure))
		printf("ERROR: Not enough treasure cards added to hand. Pre: %d Post: %d\n", preTreasure, postTreasure);
	//still current player?
	if(pre.whoseTurn != post->whoseTurn)
		printf("ERROR: Current player has changed from %i to %i", pre.whoseTurn, post->whoseTurn);
	
	//check coins
	if(pre.coins != post->coins)
		printf("ERROR: Number of coins changed from %i to %i", pre.coins, post->coins);
	//check number of buys
	if(pre.numBuys != post->numBuys)
		printf("ERROR: Number of buys has changed from %i, to %i", pre.numBuys, post->numBuys);
	//check number of actions
	if(pre.numActions != post->numActions)
		printf("ERROR: Number of actions has changed from %i to %i", pre.numActions, post->numActions);
	
	return 0;
}

int main()
{
	int p = 0;
	struct gameState G;
	int numTests = 500;
	int k, m, j, n, i;
	
	for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	G.whoseTurn = p;
	SelectStream(2);
	PutSeed(3);
	printf("Testing playAdventurer() cardtest2.\n");
	
	for(k = 0; k < numTests; k++)
	{
		//fill in random cards
		G.handCount[p] = floor(Random() * MAX_HAND)+1;//need at least one adventurer in our hand
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		for(m = 0; m < G.handCount[p]; m++)
		{
			G.hand[p][m] = floor(Random() * treasure_map) + 1;
		}
		
		for(j = 0; j < G.discardCount[p]; j++)
		{
			G.discard[p][j] = floor(Random() * treasure_map) + 1;
		}

		for(n = 0; n < G.deckCount[p]; n++)
		{
			G.deck[p][n] = floor(Random() * treasure_map) + 1;
		}
		
		testAdventurer(&G);
		
	}
	
	printf("PLAYADVENTURER TESTS FINISHED.\n\n");
	
	return 0;
}