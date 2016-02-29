#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void checkState(struct gameState pre, struct gameState post, int currentPlayer, bool willShuffle){
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
	
	if (willShuffle)
	{
		//discard will be emptied
		if (post.discardCount[currentPlayer] != 0)
		{
			printf("Deck shuffled discard should be 0 TEST FAILED\n");
		}

		//check if there are less than 3 cards to draw 
		if (pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] < 3)
		{
			//discard and deck should both be 0 because all remaining cards were drawn
			if (post.discardCount[currentPlayer] != 0)
			{
				printf("Discard should be 0 all reaminaing cards should have been drawn TEST FAILED\n");
			}
			if (post.deckCount[currentPlayer] != 0)
			{
				printf("Deck should be 0 all reamaing cards should have been drawn TEST FAILED\n");
			}
			//should only draw the remaining cards
			if (pre.handCount[currentPlayer] + pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] - 1 != post.handCount[currentPlayer])
			{
				printf("When shuffled, drawing remaining cards, did not add them all to hand TEST FAILED\n");
			}
		}
		//deck will be old deck + discard -3 cards from drawing
		else 
		{
			if (pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] - 3 != post.deckCount[currentPlayer])
			{
				printf("Deck Shuffled, deck count incorrect after draw TEST FAILED\n");
			}
			if (pre.handCount[currentPlayer] + 2 != post.handCount[currentPlayer])
			{
				printf("Deck Shuffled, Hand count incorrect after draw TEST FAILED\n");
			}
			
		}
	}

	else
	{
		if (pre.discardCount[currentPlayer] != post.discardCount[currentPlayer])
		{
			printf("Discard count changed TEST FAILED\n");
		}

		if (pre.deckCount[currentPlayer] - 3 != post.deckCount[currentPlayer])
		{
			printf("Deck Count incorrect after play TEST FAILED\n");
		}
		if (pre.handCount[currentPlayer] + 2 != post.handCount[currentPlayer])
		{
			printf("Deck NOT Shuffled, Hand count incorrect after draw TEST FAILED\n");
		}
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

	int i, n, p, j, m, randCard, r, q;

	int k[10];
	struct gameState G;
	struct gameState pre;
	int seed = 1000;

	srand(time(NULL));
	SelectStream(2);
	PutSeed(3);

	bool willShuffle;

	printf("Running random test for smithy()\n");

	//create random kingdom cards
	int counter = 0;
	bool use;
	while (counter < 10)
	{
		use = true;
		q = rand() % 20 + 7; //picks a random card from the kingdom cards
		//check to see if already used
		for (i = 0; i < counter; i++)
		{
			//if already used set that we will use to false
			if (k[i] == q)
			{
				use = false;
			}
		}
		if (use)
		{
			//if we are using set k card to q and incremenet counter
			k[counter] = q;
			counter++;
		}
	}

	//make sure test card is in the kingdom pile
	bool hasTest;
	hasTest = false;
	for (i = 0; i < 10; i++)
	{
		if (k[i] == smithy)
		{
			hasTest = true;
		}
	}
	if (!hasTest)
	{
		q = rand() % 10;
		k[q] = smithy;
	}


	//set up a card array to use for random card gen
	//will have the 10 picked cards + static cards
	int cards[17];
	//0 - 6 are cards 0-6 in CARD enum
	for (i = 0; i < 7; i++)
	{
		cards[i] = i;
	}
	//remaining 10 cards are the kingdom cards
	j = 0;
	for (i = 7; i < 17; i++)
	{
		cards[i] = k[j];
		j++;
	}

	for (n = 0; n < 100; n++) {

		p = rand() % 3 + 2;  //random player amount
		memset(&G, 23, sizeof(struct gameState));				// clear the game state
		r = initializeGame(p, k, seed, &G);	         			// initialize a new game

		//set up each players hands decks discards and playerd cards
		for (j = 0; j < G.numPlayers; j++)
		{
			G.handCount[j] = rand() % 6 + 1;				//create a hand with up to 1-5 cards
			for (m = 0; m < G.handCount[j]; m++)
			{
				randCard = rand() % 17;
				G.hand[j][m] = cards[randCard];
			}
			G.deckCount[j] = rand() % 11;	     			//creates a random deck of up to 0 - 10 cards
			for (m = 0; m < G.deckCount[j]; m++)
			{
				randCard = rand() % 17;
				G.deck[j][m] = randCard;
			}
			G.discardCount[j] = rand() % 11;				//creates random discard pile of 0 - 10 cards
			for (m = 0; m < G.discardCount[j]; m++)
			{
				randCard = rand() % 17;
				G.discard[j][m] = randCard;
			}
		}

		G.playedCardCount = 0;                		     // playedCardCount set to 0

		//pick random player to play
		G.whoseTurn = rand() % G.numPlayers;

		//make sure that player has smithy in hand track its handPos
		int handPos;
		hasTest = false;
		for (j = 0; j < G.handCount[G.whoseTurn]; j++)
		{
			if (G.hand[G.whoseTurn][j] == smithy)
			{
				hasTest = true;
				handPos = j;
			}
		}
		if (!hasTest)
		{
			q = rand() % G.handCount[G.whoseTurn];
			G.hand[G.whoseTurn][q] = smithy;
			handPos = q;
		}

		willShuffle = false;
		//if there are less than 3 cards will shuffle discard
		if (G.deckCount[G.whoseTurn] < 3)
		{
			willShuffle = true;
		}


		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate

		printf("\nPlaying Smithy Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", G.whoseTurn, n + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.playedCardCount);
		
		playSmithy(&G, handPos[j]);
		
		printf("Played  Smithy Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", G.whoseTurn, n + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.playedCardCount);

		checkState(pre, G, G.whoseTurn, willShuffle);										// check new gamestate vs old using modified checkState
	}

	printf("Finished running randomtest for play_smithy()\n");

	return 0;
}