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
	int p = post->whoseTurn;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	playSmithy(post, handPos);
	
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