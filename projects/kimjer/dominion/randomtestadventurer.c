
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#include <math.h>
#include "assert.h"
#define YES 1
#define NO 0 
#define NUMCARDS 10

void ASSERT2(int expVal, int realVal, char *s) 
{	
	if(expVal != realVal) 
	{
		printf("FAIL - %s\n", s);
		printf("EXPECTED value is %d; got %d", expVal, realVal);
		assert(expVal == realVal);
		exit(1);
	}
}

int isUnique(int k[]) {
	int i, j;
	for(i = 0; i < NUMCARDS; i++)
	{
		for(j = 1; j < NUMCARDS; j++)
		{	
			if(j!=i && k[i] == k[j])
				return NO;	
		}	
	}
	return YES;
}

void makeK(int k[])
{
	int i;
	for(i = 0; i < NUMCARDS; i++)
	{
		k[i] = rand()%NUMCARDS;
	}
}	

void initI(struct infosStruct *infos) 
{
	int i;

	(*infos).drawntreasure = 0;
	(*infos).drawntreasure = 0;
	(*infos).cardDrawn = 0; //random
	for(i = 0; i < MAX_HAND; i++)
		(*infos).temphand[i] = 0; //rand()%MAX_HAND
	(*infos).z = 0;
	(*infos).handPos = 0; //not used
	(*infos).i = 0; //not used either
	(*infos).currentPlayer = 0;
}

void func(int *x) 
{
	*x = 5;
}

int main() {

	srand(time(NULL));
	int i, j, ret;
	struct gameState *g;
	struct infosStruct infos;
	g = newGame();
	int k[NUMCARDS]; 
	int n;
	int handCount, deckCount, discardCount;
	int handCountExp, deckCountExp, discardCountExp;

	//Make sure draw card is working correctly
	for(n=0; n < 2000; n++)
	{
		//make unique kingdom cards
		do 
		{
			makeK(k);
		}
		while(!isUnique(k));

		initializeGame(2, k, 3, g);

		//randomize number of players
		int numPlayers = (rand()%MAX_PLAYERS)+1;
		g->numPlayers = numPlayers;

		//randomize unused properties
		g->outpostPlayed = rand();
		g->outpostTurn = rand();
		g->whoseTurn = rand(); //this may be important
		g->phase = rand();
		g->numActions = rand();
		g->coins = rand();
		g->numBuys = rand();

		//randomized player hands
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = floor(rand()%(MAX_HAND/3));
			}
			while(numCards < 13);

			for(j = 0; j < numCards; j++)
			{
				g->hand[i][j] = rand()%15;
			}
			g->handCount[i] = numCards;
		}

		//randomized player decks
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;

			numCards = rand()%(MAX_HAND/3);


			for(j = 0; j < numCards; j++)
			{
				g->deck[i][j] = rand()%15;
			}
			g->deckCount[i] = numCards;
		}
		deckCount = g->deckCount[numPlayers-1];

		//randomized player discard counts
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = rand()%(MAX_HAND/3);
			}
			while(numCards == 0 && g->deckCount[i] == 0);

			for(j = 0; j < numCards; j++)
			{
				g->discard[i][j] = rand()%15;
			}
			g->discardCount[i] = numCards;
		}
		discardCount = g->discardCount[numPlayers-1];
		//initialize infosStruct
		infos.drawntreasure = 0;
		infos.drawntreasure = 0;
		infos.cardDrawn = 0; //random
		for(i = 0; i < MAX_HAND; i++)
			infos.temphand[i] = rand(); //rand()%MAX_HAND
		infos.z = 0;
		infos.handPos = 0; //not used
		infos.i = 0; //not used either

		//randomly select current player
		do
		{
			infos.currentPlayer = rand()%MAX_PLAYERS;
		}
		while(infos.currentPlayer >= numPlayers);

		//get gameState values before calling drawCard()
		handCount = g->handCount[numPlayers-1];
		//handle case when deckCount is 0
		if(deckCount == 0)
		{
			deckCountExp = discardCount;
			deckCountExp--; //because draw card
			discardCountExp = 0;
		}
		else //discardCount is not affected
		{
			discardCountExp = discardCount;
			deckCountExp = deckCount - 1;
		}
		
		handCountExp = handCount + 1;

		drawCard(numPlayers-1, g);

		handCount = g->handCount[numPlayers-1];
		deckCount = g->deckCount[numPlayers-1];
		discardCount = g->discardCount[numPlayers-1];

		ASSERT2(handCountExp, handCount, "handCount after drawCard()");
		ASSERT2(deckCountExp, deckCount, "deckCount after drawCard()");
		ASSERT2(discardCountExp, discardCount, "discardCount after drawCard()");

	}
	puts("drawCard(): PASSED");
	//make sure player has two more cards after effectAdventurer
	for(n=0; n < 2000; n++)
	{
		//make unique kingdom cards
		do 
		{
			makeK(k);
		}
		while(!isUnique(k));

		initializeGame(2, k, 3, g);

		//randomize number of players
		int numPlayers = (rand()%MAX_PLAYERS)+1;
		g->numPlayers = numPlayers;
		//randomly select current player
		do
		{
			infos.currentPlayer = rand()%MAX_PLAYERS;
		}
		while(infos.currentPlayer >= numPlayers);

		//randomize unused properties
		g->outpostPlayed = rand();
		g->outpostTurn = rand();
		g->whoseTurn = rand(); //this may be important
		g->phase = rand();
		g->numActions = rand();
		g->coins = rand();
		g->numBuys = rand();

		//randomized player hands
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = floor(rand()%(MAX_HAND/3));
			}
			while(numCards < 13);

			for(j = 0; j < numCards; j++)
			{
				g->hand[i][j] = rand()%15;
			}
			g->handCount[i] = numCards;
		}

		//randomized player decks
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			int coinCount = 0;
			do
			{

			numCards = rand()%(MAX_HAND/3);
				for(j = 0; j < numCards; j++)
				{
					int coin = rand()%15;
					if(coin == copper)
						coinCount++;
					if(coin == silver)
						coinCount++;
					if(coin == gold)
						coinCount++;
					g->deck[i][j] = coin;
				}
			}
			while(coinCount < 2);
			g->deckCount[i] = numCards;
		}
		deckCount = g->deckCount[infos.currentPlayer];
		

		//randomized player discard counts
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = rand()%(MAX_HAND/3);
			}
			while(numCards == 0 && g->deckCount[i] == 0);

			for(j = 0; j < numCards; j++)
			{
				g->discard[i][j] = rand()%15;
			}
			g->discardCount[i] = numCards;
		}
		discardCount = g->discardCount[infos.currentPlayer];

		//initialize infosStruct
		infos.drawntreasure = 0;
		infos.drawntreasure = 0;
		infos.cardDrawn = 0; //random
		for(i = 0; i < MAX_HAND; i++)
			infos.temphand[i] = rand(); //rand()%MAX_HAND
		infos.z = 0;
		infos.handPos = 0; //not used
		infos.i = 0; //not used either

		//get gameState values before calling drawCard()
		handCount = g->handCount[infos.currentPlayer];
		//handle case when deckCount is 0
		if(deckCount == 0)
		{
			deckCountExp = discardCount;
			deckCountExp--; //because draw card
			discardCountExp = 0;
		}
		else //discardCount is not affected
		{
			discardCountExp = discardCount;
			deckCountExp = deckCount - 1;
		}

		handCountExp = handCount + 2;
		ret = effectAdventure(g, &infos);
		handCount = g->handCount[infos.currentPlayer];
		deckCount = g->deckCount[infos.currentPlayer];
		discardCount = g->discardCount[infos.currentPlayer];
		ASSERT2(handCountExp, handCount, "handCount" );
	}
	puts("effectAdventure(): Passed");
	return 0; 
}