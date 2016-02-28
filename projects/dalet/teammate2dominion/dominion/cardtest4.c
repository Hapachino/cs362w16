/*
*  Unit Test for remodel
*
* Business Requirements:
*
*	1. Current player should pick a card from their hand (choice1)
*   2. Current player should pick a card from a valid supply (choice2)
*   3. If choice1 cost + 2 is <= choice2:
*		choice 1 should be trashed
*		choice 2 added to discard pile
*   4. Otherwise nothing should happen (no change in gameState, player doesnt use an action)
*   5. If successfull the only parts of gameState that should change are handCount, discardCount, cardsPlayedCount, cardsPlayed, supplyCount of choice2
*
* cardTest4: cardTest4.c dominion.o rngs.o
*      gcc -o cardTest4 -g cardTest4.c dominion.o rngs.o $(FLAGS)
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

void checkState(struct gameState pre, struct gameState post, int currentPlayer, int choice1, int choice2){
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
	//assert(pre.deckCount[currentPlayer] == post.deckCount[currentPlayer]);
	if (pre.deckCount[currentPlayer] != post.deckCount[currentPlayer])
	{
		printf("deck count changed TEST FAILED\n");
	}

	//not a valid remodel choice based on cost or supply count is 0
	if ( (getCost(choice1) + 2 < getCost(choice2)) || (supplyCount(choice2, &pre) < 1) )
	{
		//nothing should change in gameState
		for (i = 0; i < treasure_map; i++)
		{
			//assert(pre.supplyCount[i] == post.supplyCount[i]);
			if (pre.supplyCount[i] != post.supplyCount[i])
			{
				printf("Invalid remodel supply count changed TEST FAILED\n");
			}
			//assert(pre.embargoTokens[i] == post.embargoTokens[i]);
			if (pre.embargoTokens[i] != post.embargoTokens[i])
			{
				printf("Invalid remodel embargo tokens changed TEST FAILED\n");
			}
		}
		//assert(pre.handCount[currentPlayer] == post.handCount[currentPlayer]);
		if (assert(pre.handCount[currentPlayer] != post.handCount[currentPlayer]))
		{
			printf("Invalid remodel hand count changed TEST FAILED\n");
		}
		//assert(pre.discardCount[currentPlayer] == post.discardCount[currentPlayer]);
		if (pre.discardCount[currentPlayer] != post.discardCount[currentPlayer])
		{
			printf("Invalid remodel discard count changed TEST FAILED\n");
		}
	}
	else
	{
		//choice 2 supply count should go down by 1
		for (i = 0; i < treasure_map; i++)
		{
			if (i == choice2)
			{
				//assert(pre.supplyCount[i] - 1 == post.supplyCount[i]);
				//printf("Pre supply count %d for card %d\n", supplyCount(choice2, &pre), choice2);
				//printf("Post supply count %d for card %d\n", supplyCount(choice2, &post), choice2);
				//assert(supplyCount(choice2, &pre) - 1 == supplyCount(choice2, &post));
				if (supplyCount(choice2, &pre) - 1 != supplyCount(choice2, &post))
				{
					printf("Valid Remodel Supply Count of choice2 did not decrement correctly TEST FAILED\n");
				}
			}
			else
			{
				//assert(pre.supplyCount[i] == post.supplyCount[i]);
				if (pre.supplyCount[i] != post.supplyCount[i])
				{
					printf("Valid Remodel Supply count that was not choice 2 changed TEST FAILED\n");
				}
			}			
			//assert(pre.embargoTokens[i] == post.embargoTokens[i]);
			if (pre.embargoTokens[i] != post.embargoTokens[i])
			{
				printf("Valid Remodel Embardo Tokens changed TEST FAILED\n");
			}
		}
		//assert(pre.handCount[currentPlayer] - 2 == post.handCount[currentPlayer]);					//should remove remodel from hand + trashed card from hand
		if (pre.handCount[currentPlayer] - 2 != post.handCount[currentPlayer])
		{
			printf("Incorrect number of cards in hand after valid remodel TEST FAILED\n");
		}
		//assert(pre.discardCount[currentPlayer] + 1 == post.discardCount[currentPlayer]);			//should discard remodel
		if (pre.discardCount[currentPlayer] + 1 != post.discardCount[currentPlayer])
		{
			printf("Incorrect number of discard after valid remodel TEST FAILED\n");
		}
		//assert(post.discard[currentPlayer][post.discardCount[currentPlayer] - 1] == remodel);		//checks top of discard remodel
		if (post.discard[currentPlayer][post.discardCount[currentPlayer] - 1] != remodel)
		{
			printf("Last discard card not Remodel after valid remodel TEST FAILED\n");
		}
		//assert(pre.playedCardCount + 1 == post.playedCardCount);									//should have played 1 card
		if (pre.playedCardCount + 1 != post.playedCardCount)
		{
			printf("Card Played Count did not increment correctly after valid remodel TEST FAILED\n");
		}
		//assert(post.playedCards[post.playedCardCount - 1] == remodel);								//checks if the last card played is remodel
		if (post.playedCards[post.playedCardCount - 1] != remodel)
		{
			printf("Last played card is not remodel TEST FAILED\n");
		}
		
	}
}

int main() {

	int n, p, j, m, randCard, handPos, choice1, choice2, r;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState pre;
	
	int seed = 1000;
	srand(time(NULL));
	SelectStream(2);
	PutSeed(3);

	printf("Running cardtest4 for play_Remodel()\n");

	for (n = 0; n < 20; n++) {

		p = rand() % 4 + 1;									//random player amount
		memset(&G, 23, sizeof(struct gameState));			// clear the game state
		r = initializeGame(p, k, seed, &G);	         		// initialize a new game
					
		j = rand() % p;										//pick a random current player
		G.whoseTurn = j;

		//set up current player's hand, deck, discard, and playedCards with random cards
		G.handCount[j] = rand() % 10 + 2;					//create a hand for a player with at least 2 cards one for remodel and one to use remodel on
		for (m = 0; m < G.handCount[j]; m++)
		{
			randCard = rand() % 10;							// random card from list of cards
			G.hand[j][m] = k[randCard];
		}
		G.deckCount[j] = rand() % 51 + 10;	     			// creates a random deck of up to 10 - 50 cards
		for (m = 0; m < G.deckCount[j]; m++)
		{
			randCard = rand() % 10;							// random card from list of cards
			G.deck[j][m] = k[randCard];
		}
		G.discardCount[j] = rand() % 50;					// create random discard
		for (m = 0; m < G.discardCount[j]; m++)
		{
			randCard = rand() % 10;							// random card from list of cards
			G.discard[j][m] = k[randCard];
		}
		G.playedCardCount = rand() % 50;
		for (m = 0; m < G.playedCardCount; m++)
		{
			randCard = rand() % 10;							// random card from list of cards
			G.playedCards[m] = k[randCard];
		}
		
		//insert remodel into random spot in hand so we know its hand pos
		handPos = rand() % G.handCount[j];
		G.hand[j][handPos] = remodel;

		//pick a random card from hand for choice1
		choice1 = rand() % G.handCount[j];
		while (choice1 == handPos)							//make sure its not the remodel we added
		{
			choice1 = rand() % G.handCount[j];
		}
		//pick a random card from kingdom supply for choice2
		choice2 = k[rand() % 10];


		//have player play remodel
		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
		//printf("\nPlaying Remodel as Player %d Iteration %d choice1 cost %d choice2 cost %d hand %d deck %d discard %d played %d \n", j, n + 1, getCost(choice1), getCost(choice2), G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
		play_Remodel(j, &G, choice1, choice2, handPos);
		//printf("Played  Remodel as Player %d Iteration %d choice1 cost %d choice2 cost %d hand %d deck %d discard %d played %d \n", j, n + 1, getCost(choice1), getCost(choice2), G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
		checkState(pre, G, j, choice1, choice2);
	}

	printf("Finished running cardtest4 for play_Remodel()\n");

	return 0;
}