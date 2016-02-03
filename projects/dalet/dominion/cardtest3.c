/*
*  Unit Test for council_room
*
* Business Requirements:
*
*	1. Current player should draw 4 cards
*   2. All cards drawn from the deck making the deck count go down 4 cards
*   3. All other players should draw 1 card
*	4. Each other players deck should be decremented by 1
*   5. Current player should get 1 more buy
*	6. The only parts of gameState that should change are handCount, deckCount, cardsPlayedCount, cardsPlayed
*
* cardTest3: cardTest3.c dominion.o rngs.o
*      gcc -o cardTest3 -g cardTest3.c dominion.o rngs.o $(FLAGS)
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
	//assert(pre.numBuys + 1 == post.numBuys);  //should add one buy
	if (pre.numBuys + 1 != post.numBuys)
	{
		printf("Num buys is incorrect TEST FAILED\n");
	}
	for (i = 0; i < pre.numPlayers; i++)
	{
		if (i == currentPlayer)
		{
			//assert(pre.handCount[currentPlayer] + 3 == post.handCount[currentPlayer]);    //should draw 4 cards into hand but counclin room was removed for net gain of 3
			if (pre.handCount[currentPlayer] + 3 != post.handCount[currentPlayer])
			{
				printf("Current Player hand count incorrect TEST FAILED\n");
			}
			//assert(pre.deckCount[currentPlayer] - 4 == post.deckCount[currentPlayer]);    //should remove 4 cards from deck
			if (pre.deckCount[currentPlayer] - 4 != post.deckCount[currentPlayer])
			{
				printf("Current player deck count incorrect TEST FAILED\n");
			}
		}
		else
		{
			//assert(pre.handCount[i] + 1 == post.handCount[i]);    //should draw 1
			if (pre.handCount[i] + 1 != post.handCount[i])
			{
				printf("Non current players hand count is incorrect TEST FAILED\n");
			}
			//assert(pre.deckCount[i] - 1 == post.deckCount[i]);    //should remove 1 card from deck
			if (pre.deckCount[i] - 1 != post.deckCount[i])
			{
				printf("Non current players deck count is incorrect TEST FAILED\n");
			}
		}
	}
	//assert(pre.discardCount[currentPlayer] == post.discardCount[currentPlayer]);  //should add nothing to discard
	if (pre.discardCount[currentPlayer] != post.discardCount[currentPlayer])
	{
		printf("Discard count changed TEST FAILED\n");
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
	//assert(post.playedCards[post.playedCardCount - 1] == council_room);									   //checks if the last card played is a council room
	if (post.playedCards[post.playedCardCount - 1] != council_room)
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

	printf("Running cardtest3 for play_Council_room()\n");

	for (n = 0; n < 20; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}

		p = rand() % 4 + 1;  //random player amount
		int handPos[p]; //create an array of positions of council room for each player

		G.numPlayers = p;

		//set up each players hands decks discards and playerd cards as well as put a council room in their hand
		for (j = 0; j < p; j++)
		{
			G.handCount[j] = rand() % 10 + 1;					//create a hand for a player
			for (m = 0; m < G.handCount[j]; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.hand[j][m] = k[randCard];
			}
			G.deckCount[j] = rand() % 51 + 10;	     			//creates a random deck of up to 10 - 50 cards to make sure there is enough to draw
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
			G.playedCardCount = rand() % 50	;			
			for (m = 0; m < G.playedCardCount; m++)
			{
				randCard = rand() % 10;							// random card from list of cards
				G.playedCards[m] = k[randCard];
			}

			//insert council room into random spot in hand so we know its hand pos
			handPos[j] = rand() % G.handCount[j];
			G.hand[j][handPos[j]] = council_room;

		}

		//have each player play their council_room
		for (j = 0; j < p; j++)
		{
			//have player play council_room
			G.whoseTurn = j;
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			//printf("\n Playing Council Room as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
			play_Council_room(j, &G, handPos[j]);
			//printf("Played   Council Room as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d \n", j, n + 1, G.handCount[j], G.deckCount[j], G.discardCount[j], G.playedCardCount);
			checkState(pre, G, j);
		}
	}
	return 0;

	printf("Finished running cardtest3 for play_Council_room()\n");
}