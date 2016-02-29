/*
*  Unit Test for Smithy Card
*
* Business Requirements:
*
*	1. Current player should recieve 3 cards
*   2. Drawn cards should come from his deck
*   3. gameState should change for players hand, deck, playedCards, and playedCard 
*   4. No other changes to gameState
*  
* cardTest1: cardTest1.c dominion.o rngs.o
*      gcc -o cardTest1 -g cardTest1.c dominion.o rngs.o $(FLAGS)
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
	//assert(pre.handCount[currentPlayer] + 2 == post.handCount[currentPlayer]);    //should draw 3 cards into hand but smithy was removed for net gain of 2
	if (pre.handCount[currentPlayer] + 2 != post.handCount[currentPlayer])
	{
		printf("Hand Count incorrect after play TEST FAILED\n");
	}
	//assert(pre.deckCount[currentPlayer] - 3 == post.deckCount[currentPlayer]);    //should remove 3 cards from deck
	if (pre.deckCount[currentPlayer] - 3 != post.deckCount[currentPlayer])
	{
		printf("Deck Count incorrect after play TEST FAILED\n");
	}
	//assert(pre.discardCount[currentPlayer] == post.discardCount[currentPlayer]);  //should add nothing to discard
	if (pre.discardCount[currentPlayer] != post.discardCount[currentPlayer])
	{
		printf("Discard count changed TEST FAILED\n");
	}
	//assert(pre.playedCardCount + 1 == post.playedCardCount); //should have played 1 card
	if (pre.playedCardCount + 1 != post.playedCardCount)
	{
		printf("Played card Count incorrect after play TEST FAILED\n");
	}
	//assert(pre.playedCards[pre.playedCardCount - 1] == post.playedCards[pre.playedCardCount - 1]);    //checks the card before the last card is the same to see only 1 card being played
	if (pre.playedCards[pre.playedCardCount - 1] != post.playedCards[pre.playedCardCount - 1])
	{
		printf("Last card played in pre is not second last card in post TEST FAILED\n");
	}
	//assert(post.playedCards[post.playedCardCount - 1] == smithy);									   //checks if the last card played is a smithy
	if (post.playedCards[post.playedCardCount - 1] != smithy)
	{
		printf("Last card played is not correct TEST FAILED\n");
	}
}


int main() {

	int i, n, p, j, m, randCard;
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState G;
	struct gameState pre;
	
	srand(time(NULL));
	SelectStream(2);
	PutSeed(3);

	printf("Running cardtest1 for play_smithy()\n");


	for (n = 0; n < 20; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) { 
			((char*)&G)[i] = floor(Random() * 256);
		}
		
		p = rand() % 4 + 1;  //random player amount
		int handPos[p]; //create an array of positions of smithy for each player

		G.numPlayers = p;

		//set up each players hands decks discards and playerd cards as well as put a smithy in their hand
		for (j = 0; j < p; j++)
		{
			G.handCount[j] = rand() % MAX_DECK + 1;
			while (G.handCount[j] > 498)                       //this is to make sure handCount is not too large since it will overflow in a real game there is only 500 max for everything combined
			{
				G.handCount[j] = rand() % MAX_DECK + 1;
			}
			for (m = 0; m < G.handCount[j]; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.hand[j][m] = k[randCard];
			}
			G.deckCount[j] = rand() % MAX_DECK + 1;
			while (G.deckCount[j] < 3)                       //this is to make sure deckCount is not too small since it will overflow in a real game there is only 500 max for everything combined
			{
				G.deckCount[j] = rand() % MAX_DECK + 1;
			}
			for (m = 0; m < G.deckCount[j]; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.deck[j][m] = k[randCard];
			}
			G.discardCount[j] = rand() % MAX_DECK + 1;
			for (m = 0; m < G.discardCount[j]; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.discard[j][m] = k[randCard];
			}
			G.playedCardCount = rand() % MAX_DECK;				//removed the plus 1 so it never hits 500
			for (m = 0; m < G.playedCardCount; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.playedCards[m] = k[randCard];
			}

			//insert smithy card into random spot in hand so we know its hand pos
			handPos[j] = rand() % G.handCount[j];
			G.hand[j][handPos[j]] = smithy;

			//have player play smithy card
			G.whoseTurn = j;
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			//printf("\n Playing Smithy Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
			playSmithy(&G, handPos[j]);
			//printf("Played   Smithy Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
			checkState(pre, G, j);										// check new gamestate vs old using modified checkState
		}
	}

	printf("Finished running cardtest1 for play_smithy()\n");

	return 0;
}