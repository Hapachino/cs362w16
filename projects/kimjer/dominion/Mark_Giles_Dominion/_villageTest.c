#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


//random hand with smithy at the end
int createRandomHand(int *k, int max) 
{
	int j;
	for(j = 0; j < max-1; j++) 
	{
		k[j] = (rand()%15);
	}
	k[j] = smithy;
}

//random hand with smithy at the end
int createRandomDeck(int *k, int max) 
{
	int j;
	for(j = 0; j < max; j++) 
	{
		k[j] = (rand()%15);
	}
}

int setDiscardDeck(int *k, int max) {
	int i;
	for(i = 0; i < max; i++)
	{
		k[i] = -1;
	}
}

int main() {
	srand(time(NULL));
	struct gameState G;
	struct infosStruct infos;
	int k[] = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14};	
	int numPlayers = 4;
	int handCountBefore, handCountAfter;
	int deckCountBefore, deckCountAfter;
	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
	int i;
	int seed = 1000;
	initializeGame(numPlayers, k, seed, &G);
	G.numPlayers = numPlayers;
	G.whoseTurn = 0;
	infos.currentPlayer = 0;
	infos.handPos = 4;
	int numActions1, numActions2;
	int numCards1, numCards2;
	int numDeck1, numDeck2;
	int numHand1, numHand2;

	int handCount = 5;
	int deckCount = MAX_DECK - handCount;
	createRandomHand(G.hand[p1], handCount);
	createRandomHand(G.hand[p2], handCount);
	createRandomHand(G.hand[p3], handCount);
	createRandomHand(G.hand[p4], handCount);

	G.handCount[p1] = handCount;
	G.handCount[p2] = handCount;	
	G.handCount[p3] = handCount;	
	G.handCount[p4] = handCount;

	createRandomDeck(G.deck[p1], deckCount);
	createRandomDeck(G.deck[p2], deckCount);
	createRandomDeck(G.deck[p3], deckCount);
	createRandomDeck(G.deck[p4], deckCount);

	G.deckCount[p1] = deckCount;
	G.deckCount[p2] = deckCount;	
	G.deckCount[p3] = deckCount;	
	G.deckCount[p4] = deckCount;

	setDiscardDeck(G.discard[p1], MAX_DECK);
	setDiscardDeck(G.discard[p2], MAX_DECK);
	setDiscardDeck(G.discard[p3], MAX_DECK);
	setDiscardDeck(G.discard[p4], MAX_DECK);

	G.discardCount[p1] = 0;
	G.discardCount[p2] = 0;	
	G.discardCount[p3] = 0;	
	G.discardCount[p4] = 0;


//testing current player
	numActions1 = G.numActions;
	numHand1 = G.handCount[p1];
	numDeck1 = G.deckCount[p1];
	villageEffect(infos.currentPlayer, &G, infos.handPos);

	numHand2 = G.handCount[p1];
	numDeck2 = G.deckCount[p1];
	numActions2 = G.numActions;	
	assert(numActions1 +2 == numActions2);
	assert(numDeck1 -1 == numDeck2);
	//assert(numHand1 +1 == numHand2);
	
	endTurn(&G);
	assert(G.numActions == numActions1);

	//testing for player 2
	infos.currentPlayer = 0;
	numHand1 = G.handCount[p2];
	numDeck1 = G.deckCount[p2];
	villageEffect(infos.currentPlayer, &G, infos.handPos);

	numHand2 = G.handCount[p2];
	numDeck2 = G.deckCount[p2];
	assert(numDeck1 == numDeck2);
	assert(numHand1 == numHand2);

//testing for player 3
	infos.currentPlayer = 0;
	numHand1 = G.handCount[p3];
	numDeck1 = G.deckCount[p3];
	villageEffect(infos.currentPlayer, &G, infos.handPos);

	numHand2 = G.handCount[p3];
	numDeck2 = G.deckCount[p3];
	assert(numDeck1 == numDeck2);
	assert(numHand1 == numHand2);

//testing for player 4
	infos.currentPlayer = 0;
	numHand1 = G.handCount[p4];
	numDeck1 = G.deckCount[p4];
	villageEffect(infos.currentPlayer, &G, infos.handPos);

	numHand2 = G.handCount[p4];
	numDeck2 = G.deckCount[p4];
	assert(numDeck1 == numDeck2);
	assert(numHand1 == numHand2);


	return 0;
}



// int villageEffect(struct gameState *state, struct infosStruct *infos)
// {

//   int currentPlayer= infos->currentPlayer;

//   int handPos = infos->handPos;
//   //+1 Card
//   drawCard(currentPlayer, state);

//   //+2 Actions
//   state->numActions = state->numActions + 2;

//   //discard played card from hand
//   discardCard(handPos, currentPlayer, state, 0);
//   return 0;
// }

