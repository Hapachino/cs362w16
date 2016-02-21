/*
* Unit Test for fullDeckCount()
*
* Business Requirements:
*	1. Should add every card in a players discard pile
*   2. Should add every card in a players deck pile
*	3. Should add every card in a players hand
*   4. No changes should be made to the game state
*
* unittest2: unittest2.c dominion.o rngs.o
*	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

void checkState(struct gameState pre, struct gameState post){
	int i;
	//assert(pre.numPlayers == post.numPlayers); //number of players
	if (pre.numPlayers != post.numPlayers)
	{
		printf("Num Players Changed TEST FAILED\n");
	}
	for (i = 0; i < treasure_map; i++)
	{
		//assert(pre.supplyCount[i] == post.supplyCount[i]);
		if (pre.supplyCount[i] != post.supplyCount[i])
		{
			printf("Supply Counts Changed TEST FAILED\n");
		}
		//assert(pre.embargoTokens[i] == post.embargoTokens[i]);
		if (pre.embargoTokens[i] != post.embargoTokens[i])
		{
			printf("Embargo Tokens Changed TEST FAILED\n");
		}
	}
	//assert(pre.outpostPlayed == post.outpostPlayed);
	if (pre.outpostPlayed != post.outpostPlayed)
	{
		printf("outpost played changed TEST FAILED\n");
	}
	//assert(pre.outpostTurn == post.outpostTurn);
	if (pre.outpostTurn != post.outpostTurn)
	{
		printf("outpost turn changed TEST FAILED\n");
	}
	//assert(pre.whoseTurn == post.whoseTurn);
	if (pre.whoseTurn != post.whoseTurn)
	{
		printf("whose turn changed TEST FAILED\n");
	}
	//assert(pre.phase == post.phase);
	if (pre.phase != post.phase)
	{
		printf("phase changed TEST FAILED\n");
	}
	//assert(pre.numActions == post.numActions);
	if (pre.numActions != post.numActions)
	{
		printf("num actions changed TEST FAILED\n");
	}
	//assert(pre.coins == post.coins);
	if (pre.coins != post.coins)
	{
		printf("num coins changed TEST FAILED\n");
	}
	//assert(pre.numBuys == post.numBuys);
	if (pre.numBuys != post.numBuys)
	{
		printf("num buys changed TEST FAILED\n");
	}
	//assert(pre.playedCardCount == post.playedCardCount);
	if (pre.playedCardCount != post.playedCardCount)
	{
		printf("num played cards changed TEST FAILED\n");
	}
}

int main(){

	printf("Running Unittest2 for fullDeckCount\n");

	int i, n, p, j, randCard;
	struct gameState G;
	struct gameState pre;

	int k[16] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall, copper, silver, gold, estate, duchy, province };

	//creates random seed
	srand(time(NULL));

	SelectStream(2);
	PutSeed(3);

	//create a random gamestate keeping deckCount discardCount and handCount inside MAX limits and random numPlayers
	for (n = 0; n < 20; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = rand() % 4 + 1;
		G.numPlayers = p;
		int manualCount[p];
		for (i = 0; i < p; i++)
		{
			//determine random deck count
			G.deckCount[i] = rand() % MAX_DECK + 1;
			//fill deck with random cards
			for (j = 0; j < G.deckCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.deck[i][j] = k[randCard];
			}

			//determine random discard count
			G.discardCount[i] = rand() % MAX_DECK + 1;
			//fill discard with random cards
			for (j = 0; j < G.discardCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.discard[i][j] = k[randCard];
			}

			//determine random hand count
			G.handCount[i] = rand() % MAX_HAND + 1;
			//fill hand with random cards
			for (j = 0; j < G.handCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.hand[i][j] = k[randCard];
			}
			
			//manual count of cards			
			manualCount[i] = G.deckCount[i] + G.discardCount[i] + G.handCount[i];
		}
		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
		for (i = 0; i < p; i++)
		{
			//assert(manualCount[i] == fullDeckCount(i, 0, &G));  // using 0 for fullDeckCount as this is how the function is called the only time its called in dominion.c
			if (manualCount[i] != fullDeckCount(i, 0, &G))
			{
				printf("Manual Count different than fullDeckCount TEST FAILED\n");
			}
		}		
		checkState(pre, G);										// check nothing changed in gameState
			
	}
	
	printf("Finished Unittest2 for fullDeckCount\n");

	return 0;
}