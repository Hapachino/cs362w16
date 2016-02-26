/* -----------------------------------------------------------------------
	* Testing playSmithy()
	* -----------------------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testSmithy(struct gameState *post, int handPos)
{
	int i;
	int p = post->whoseTurn;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	smithyCardFunc(post, handPos);
	
	pre.handCount[p] = pre.handCount[p] + 2; //net gain after discarding smithy
	pre.playedCardCount++; //a smithy was played
	
	//check if the discard pile was shuffled into the deck
	if(pre.deckCount[p] < 3)
	{
		pre.deckCount[p] = pre.deckCount[p] + pre.discardCount[p] - 3;
	}
	else
	{
		pre.deckCount[p] = pre.deckCount[p] - 3; //after drawing 3 cards
	}
	
	if(post->handCount[p] != pre.handCount[p])
	{
		printf("ERROR: handCount is incorrect. Expected: %d Actual: %d\n", pre.handCount[p], post->handCount[p]);
	}
	if(post->deckCount[p] != pre.deckCount[p])
	{
		printf("ERROR: deckCount is incorrect. Expected: %d Actual: %d\n", pre.deckCount[p], post->deckCount[p]);
	}
	if(pre.playedCardCount != post->playedCardCount)
	{
		printf("ERROR: playedCardCount is incorrect. Expected: %d Actual: %d\n", pre.playedCardCount, post->playedCardCount);
	}
	
	//check supply counts
	for(i = 0; i < treasure_map; i++)
	{
		if(pre.supplyCount[i] != post->supplyCount[i])
			printf("ERROR: Supply counts for card#%i are different. Pre: %i, Post: %i", i, pre.supplyCount[i], post->supplyCount[i]);
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
	//check number of actions
	if(pre.numActions != post->numActions)
		printf("ERROR: Number of actions has changed from %i to %i", pre.numActions, post->numActions);
	
	return 0;
}

int main()
{
	int p = 0;
	struct gameState G;
	int handPos;
	int i, j, k, m, n, q;
	
	for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing playSmithy() cardtest1.\n");
	
	G.whoseTurn = p;
	for(k = 0; k < 500; k++)
	{
		//fill in random cards
		G.handCount[p] = floor(Random() * MAX_HAND)+1;//need at least one smithy in our hand
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.playedCardCount = floor(Random() * MAX_DECK);
		//printf("handCount: %d, deckCount: %d, discardCount: %d.\n", G.handCount[p], G.deckCount[p], G.discardCount[p]);
		
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
		
		//place smithy in a random pos
		handPos = floor(Random() * G.handCount[p]);
		G.hand[p][handPos] = smithy;
		
		testSmithy(&G, handPos);
	}
	
	printf("PLAYSMITHY TESTS FINISHED.\n\n");
	return 0;
}