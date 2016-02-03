/*
* Unit Test for updateCoins()
*
* Business Requirements:
*	1. The current game states coin count should be reset to 0
*   2. Should add 1 for each copper, 2 for each silver and 3 for each gold in a players hand to the game states coin count
		- These cards must only be checked from the cards in the current players hand
*	3. Should add the bonus correctly that is passed to updateCoins() 
*   4. No changes should be made to the game state besides the change of its coin count
*
* unittest1: unittest1.c dominion.o rngs.o
*	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

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
	//assert(pre.coins == post.coins);  will not use in this test as this should change
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

int main() {
	int i;
	int j;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState pre;
	int maxHandCount = 5;
	//arrays of all coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;

	}

	//creates random seed
	srand( time(NULL) );

	printf("Running unittest1 for updateCoins():\n");
//	printf("Testing if hand is only one type of coin with various bonuses");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 0; handCount <= maxHandCount; handCount++)
		{
			for (bonus = 0; bonus <= maxBonus; bonus++)
			{
//				printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
				memset(&G, 23, sizeof(struct gameState));				// clear the game state
				r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
				G.handCount[p] = handCount;								// set the number of cards on hand																			
				memcpy(G.hand[p], coppers, sizeof(int) * handCount);	// set all the cards to copper
				memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
				updateCoins(p, &G, bonus);
//				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 1 + bonus);
				//assert(G.coins == handCount * 1 + bonus);				// check if the number of coins is correct
				if (G.coins != handCount * 1 + bonus)
				{
					printf("Copper coins not added correctly TEST FAILED\n");
				}
				checkState(pre, G);										// check new gamestate vs old only g.coins should change
				
				
				memcpy(G.hand[p], silvers, sizeof(int) * handCount);	// set all the cards to silver
				memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
				updateCoins(p, &G, bonus);
//				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 2 + bonus);
				//assert(G.coins == handCount * 2 + bonus);				// check if the number of coins is correct
				if (G.coins != handCount * 2 + bonus)
				{
					printf("Silver coins not added correctly TEST FAILED\n");
				}

				checkState(pre, G);										// check new gamestate vs old only g.coins should change

				memcpy(G.hand[p], golds, sizeof(int) * handCount);		// set all the cards to gold
				memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
				updateCoins(p, &G, bonus);
//				printf("G.coins = %d, expected = %d\n", G.coins, handCount * 3 + bonus);
				//assert(G.coins == handCount * 3 + bonus);				// check if the number of coins is correct
				if (G.coins != handCount * 3 + bonus)
				{
					printf("Gold coins not added correctly TEST FAILED\n");
				}
				checkState(pre, G);										// check new gamestate vs old only g.coins should change

			}
		}
	}
//	printf("Testing if hand has no treasure cards but random other cards with various bonuses");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 0; handCount <= maxHandCount; handCount++)
		{
			for (bonus = 0; bonus <= maxBonus; bonus++)
			{
//				printf("Test player %d with 0 treasure card(s) and %d bonus.\n", p, bonus);
				memset(&G, 23, sizeof(struct gameState));				// clear the game state
				r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
				G.handCount[p] = handCount;								// set the number of cards on hand

				for (j = 0; j < handCount; j++)
				{
					int randCard = rand() % 10;							// random none treasure card from kingdom list
					G.hand[p][j] = k[randCard];
				}
				memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
				updateCoins(p, &G, bonus);
//				printf("G.coins = %d, expected = %d\n", G.coins, bonus);
				//assert(G.coins == bonus);								// check if the number of coins is correct
				if (G.coins != bonus)
				{
					printf("Bonus did not add correctly with no treasure cards TEST FAILED\n");
				}
				checkState(pre, G);										// check new gamestate vs old only g.coins should change

			}			
		}
	}
//	printf("Testing if hand has a mix of treasure and non-treasure cards with various bonuses");
	for (p = 0; p < numPlayer; p++)
	{
		for (handCount = 0; handCount <= maxHandCount; handCount++)
		{
			for (bonus = 0; bonus <= maxBonus; bonus++)
			{
				
				memset(&G, 23, sizeof(struct gameState));				// clear the game state
				r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
				G.handCount[p] = handCount;								// set the number of cards on hand
				int expectedCoin = 0;
				int tempCount = 0;

				//makes half hand non-treasure half treasure
				for (j = 0; j < handCount; j++)
				{
					if (j % 2 == 0) 
					{
						tempCount++;
						int randCard = rand() % 3 + 4;					// random treasure card (4: copper, 5: silver, 6:gold)
						G.hand[p][j] = randCard;
						if (randCard == 4)
						{
							expectedCoin += 1;
						}
						else if (randCard == 5)
						{
							expectedCoin += 2;
						}
						else
						{
							expectedCoin += 3;
						}
					}
					else
					{
						int randCard = rand() % 10;							// random none treasure card from kingdom list
						G.hand[p][j] = k[randCard];
					}
				}
//				printf("Test player %d with %d random treasure card(s) and %d bonus.\n", p, tempCount, bonus);
				memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
				updateCoins(p, &G, bonus);
//				printf("G.coins = %d, expected = %d\n", G.coins, expectedCoin + bonus);
				//assert(G.coins == expectedCoin + bonus);				// check if the number of coins is correct
				if (G.coins != expectedCoin + bonus)
				{
					printf("Random treasure + non tresure did not add correctly TEST FAILED\n");
				}
				checkState(pre, G);										// check new gamestate vs old only g.coins should change
			}
		}
	}
	
	printf("Finished running unittest1 for updateCoins():\n");
	return 0;
}

