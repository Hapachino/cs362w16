/*
* Unit Test for getCost()
*
* Business Requirements:
*
*   1. A card should be passed in and its cost returned
*   2. The correct cost should be returned
*   3. No change to gameState
*
* unittest4: unittest4.c dominion.o rngs.o
*	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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

	int i, n, manualCost, randCard;
	struct gameState G;
	struct gameState pre;

	//creates random seed
	srand(time(NULL));

	SelectStream(2);
	PutSeed(3);

	printf("Running unittest4 for getCost()\n");

	//create a random gamestate keeping deckCount discardCount and handCount inside MAX limits and random numPlayers
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		manualCost = 0;
		randCard = rand() % 27; //creates a random card from 0-27 the enumerations of cards in dominion.h
		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
		//curse
		if (randCard == 0)
		{
			manualCost = 0;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//estate
		else if (randCard == 1)
		{
			manualCost = 2;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//duchy
		else if (randCard == 2)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//province
		else if (randCard == 3)
		{
			manualCost = 8;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//copper
		else if (randCard == 4)
		{
			manualCost = 0;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//silver
		else if (randCard == 5)
		{
			manualCost = 3;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//gold
		else if (randCard == 6)
		{
			manualCost = 6;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//adventurer
		else if (randCard == 7)
		{
			manualCost = 6;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//council_room
		else if (randCard == 8)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//feast
		else if (randCard == 9)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//gardens
		else if (randCard == 10)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//mine
		else if (randCard == 11)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//remodel
		else if (randCard == 12)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//smithy
		else if (randCard == 13)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//village
		else if (randCard == 14)
		{
			manualCost = 3;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//baron
		else if (randCard == 15)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//great_hall
		else if (randCard == 16)
		{
			manualCost = 3;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//minion
		else if (randCard == 17)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//steward
		else if (randCard == 18)
		{
			manualCost = 3;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//tribute
		else if (randCard == 19)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//ambassador
		else if (randCard == 20)
		{
			manualCost = 3;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//cutpurse
		else if (randCard == 21)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//embargo
		else if (randCard == 22)
		{
			manualCost = 2;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//outpost
		else if (randCard == 23)
		{
			manualCost = 5;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//salvager
		else if (randCard == 24)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//sea_hag
		else if (randCard == 25)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		//treasure_map
		else if (randCard == 26)
		{
			manualCost = 4;
			//assert(manualCost == getCost(randCard));
			if (manualCost != getCost(randCard))
			{
				printf("Failed Test at Card #%d\n", randCard);
			}
		}
		checkState(pre, G);										// check nothing changed in gameState

	}

	printf("Finished running unittest4 for getCost()\n");

	return 0;
}