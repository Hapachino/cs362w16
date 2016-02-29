/*
*  Unit Test for adventurer Card
*
* Business Requirements:
*
*	1. cards are drawn from the deck until 2 treasure cards are added to players hand
*   2. all cards drawn that are not treasure cards are put into a temp area outside deck, discard, or playedcards
*   3. once 2 treausres are found the drawn cards should all be moved to discard
*   4. gamestate changes should only happen for handCount, deckCount, discardCount, playedCardCount, playedCards
*
* cardTest2: cardTest2.c dominion.o rngs.o
*      gcc -o cardTest2 -g cardTest2.c dominion.o rngs.o $(FLAGS)
*
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

void checkState(struct gameState pre, struct gameState post, int currentPlayer){
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
	//assert(pre.handCount[currentPlayer] + 1 == post.handCount[currentPlayer]);    //should draw 2 cards but lose adventurer for a net gain of 1
	if (pre.handCount[currentPlayer] + 1 != post.handCount[currentPlayer])
	{
		printf("hand count inccorect TEST FAILED\n");
	}
	//assert(pre.deckCount[currentPlayer] - post.discardCount[currentPlayer]  - 2 == post.deckCount[currentPlayer]);    //should remove cards from the deck equal to discard  2 (2 go into hand)
	if (pre.deckCount[currentPlayer] - post.discardCount[currentPlayer] - 2 != post.deckCount[currentPlayer])
	{
		printf("deck count incorrect TEST FAILED\n");
	}
	//assert(post.discardCount[currentPlayer] == (pre.deckCount[currentPlayer] - post.deckCount[currentPlayer] - 2));    //checks discard based on same princable as deck count
	if (post.discardCount[currentPlayer] != (pre.deckCount[currentPlayer] - post.deckCount[currentPlayer] - 2))
	{
		printf("discard count incorrect TEST FAILED\n");
	}
	//assert(pre.playedCardCount + 1 == post.playedCardCount); //should have played 1 card
	if (pre.playedCardCount + 1 != post.playedCardCount)
	{
		printf("Played card Count incorrect TEST FAILED\n");
	}
	//assert(pre.playedCards[pre.playedCardCount - 1] == post.playedCards[pre.playedCardCount - 1]);         //checks the card before the last card is the same to see only 1 card being played
	if (pre.playedCards[pre.playedCardCount - 1] != post.playedCards[pre.playedCardCount - 1])
	{
		printf("Last card played in pre is not second last card in post TEST FAILED\n");
	}
	//assert(post.playedCards[post.playedCardCount - 1] == adventurer);									   //checks if the last card played is a adventurer
	if (post.playedCards[post.playedCardCount - 1] != adventurer)
	{
		printf("Last card played is not correct TEST FAILED\n");
	}
}


int main() {
	
	int i, n, p, j, m, randCard, r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState pre;
	int seed = 1000;

	srand(time(NULL));
	SelectStream(2);
	PutSeed(3);

	int preTreasureCount, preCopperCount, preSilverCount, preGoldCount;
	int postTreasureCount, postCopperCount, postSilverCount, postGoldCount;

	printf("Running cardtest2 for play_adventurer()\n");

	for (n = 0; n < 20; n++) {
		
		p = rand() % 4 + 1;  //random player amount
		memset(&G, 23, sizeof(struct gameState));				// clear the game state
		r = initializeGame(p, k, seed, &G);	         			// initialize a new game
		
		//set up each players hands decks discards and playerd cards
		for (j = 0; j < p; j++)
		{
			G.handCount[j] = rand() % 6;					   //create a hand with up to 5 cards
			for (m = 0; m < G.handCount[j]; m++)
			{
				//fills hand with half treasure half non to make sure treasures in hand dont count
				if (m % 2 == 0)
				{
					randCard = rand() % 3 + 4;					// random treasure card (4: copper, 5: silver, 6:gold)
					G.hand[j][m] = randCard;
				}
				else
				{
					randCard = rand() % 10;					// random none treasure card from kingdom list
					G.hand[j][m] = k[randCard];
				}
			}
			G.deckCount[j] = rand() % 51 + 6;	     			//creates a random deck of up to 6 - 50 cards so we know at least 2 treasure cards will be added
			//printf("Deck Count: %d\n", G.deckCount[j]);
			for (m = 0; m < G.deckCount[j]; m++)
			{
				//printf("m: %d ", m);
				//fills deck with every 5th card being a treasure
				if (m % 5 == 0)									//every 5th card will be a treasure
				{
					randCard = rand() % 3 + 4;					// random treasure card (4: copper, 5: silver, 6:gold)
					//printf("Adding a treasure randCard %d\n", randCard);
					G.deck[j][m] = randCard;
				}
				else
				{
					randCard = rand() % 10;					// random none treasure card from kingdom list
					//printf("Adding a non treasure randCard %d\n", k[randCard]);
					G.deck[j][m] = k[randCard];
				}
			}
			G.discardCount[j] = 0;								// empty discard should be filled by number of non treasure cards drawm
			G.playedCardCount = 0;                				// playedCardCount set to 0
	
			//have player play smithy card
			G.whoseTurn = j;
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			
			//check hand for treasure cards
			preTreasureCount = 0;
			preCopperCount = 0;
			preSilverCount = 0;
			preGoldCount = 0;
			for (i = 0; i < G.handCount[j]; i++)
			{
				if (G.hand[j][i] == copper)
				{
					preCopperCount++;
					preTreasureCount++;
				}
				else if (G.hand[j][i] == silver)
				{
					preSilverCount++;
					preTreasureCount++;
				}
				else if (G.hand[j][i] == gold)
				{
					preGoldCount++;
					preTreasureCount++;
				}
			}

			/*
			printf("Printing Deck:");
			for (i = 0; i < G.deckCount[j]; i++)
			{
				printf(" %d ", G.deck[j][i]);
			}
			printf("\n");
			*/
			//printf("\n Playing Adventurer Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d , Treasures in Hand %d: Copper %d, Silver %d, Gold %d\n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount, preTreasureCount, preCopperCount, preSilverCount, preGoldCount);
			playAdventurer(&G);

			//check for treasure post adventurer
			//check hand for treasure cards
			postTreasureCount = 0;
			postCopperCount = 0;
			postSilverCount = 0;
			postGoldCount = 0;
			for (i = 0; i < G.handCount[j]; i++)
			{
				if (G.hand[j][i] == copper)
				{
					postCopperCount++;
					postTreasureCount++;
				}
				else if (G.hand[j][i] == silver)
				{
					postSilverCount++;
					postTreasureCount++;
				}
				else if (G.hand[j][i] == gold)
				{
					postGoldCount++;
					postTreasureCount++;
				}
			}

			//printf("Played   Adventurer Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d , Treasures in Hand %d: Copper %d, Silver %d, Gold %d\n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount, postTreasureCount, postCopperCount, postSilverCount, postGoldCount);

			//assert(preTreasureCount + 2 == postTreasureCount);				//checks that 2 treasures were added to hand
			if (preTreasureCount + 2 != postTreasureCount)
			{
				printf("Tresure count changed by an amount different than 2 TEST FAILED\n");
			}


			checkState(pre, G, j);										// check new gamestate vs old using modified checkState
		}
	}

	printf("Finished running cardtest2 for play_adventurer()\n");
	return 0;
}