/* -----------------------------------------------------------------------
	* Testing playVillage()
	* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testplayVillage(struct gameState *post, int handPos)
{
	int p = post->whoseTurn;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	playVillage(post, handPos);
	
	//post hand should have same net hand count. Plus a draw card, minus a village card
	if(pre.handCount[p] != post->handCount[p])
	{
		printf("ERROR: hand counts should match. Pre: %d, Post: %d\n", pre.handCount[p], post->handCount[p]);
	}
	//numActions should be 2 more
	pre.numActions = pre.numActions + 2;
	if(pre.numActions != post->numActions)
	{
		printf("ERROR: number of actions should match. Pre: %d, Post: %d\n", pre.numActions, post->numActions);
	}
	//still current player?
	if(pre.whoseTurn != post->whoseTurn)
		printf("ERROR: Current player has changed from %i to %i", pre.whoseTurn, post->whoseTurn);
	
	//check coins
	if(pre.coins != post->coins)
		printf("ERROR: Number of coins changed from %i to %i", pre.coins, post->coins);
	//check number of buys
	if(pre.numBuys != post->numBuys)
		printf("ERROR: Number of buys has changed from %i, to %i", pre.numBuys, post->numBuys);
	
	return 0;
}

int main()
{
	int p = 0;
	int numTests = 500;
	struct gameState G;
	int handPos;
	int i, j, k, m, n, q;
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing playVillage() cardtest3.\n");
	
	for(k = 0; k < numTests; k++)
	{
		for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.whoseTurn = p;
		G.numActions = 1;
		//fill in random cards
		G.handCount[p] = floor(Random() * MAX_HAND)+1;//need at least one village in our hand
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.playedCardCount = floor(Random() * MAX_DECK);
		
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
		for(q = 0; q < G.playedCardCount; q++)
		{
			G.playedCards[q] = floor(Random() * treasure_map) + 1;
		}
		
		//place village in a random pos
		handPos = floor(Random() * G.handCount[p]);
		G.hand[p][handPos] = village;
		
		testplayVillage(&G, handPos);
		
	}
	
	printf("PLAYVILLAGE TESTS FINISHED.\n\n");
	return 0;
}