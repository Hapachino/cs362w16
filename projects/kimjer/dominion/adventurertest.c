#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "cardFunctions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

//1. two treasure cards are put into player's hand
// 2. appropriate amount of cards detracted from deck
// 2.b and put into discard pile
// 3. other player's states are unchanged

int countTreasureCards(int *c, int size) {
	int i;
	int tCount = 0;
	for(i = 0; i < size; i++) {
		if(c[i] == copper || c[i] == silver || c[i] == gold)
			tCount++;
	}
	return tCount;
}

int decksAreTheSame(int *d1, int *d2, int size) {
	int i;
	for(i = 0; i < size; i++)
	{
		assert(d1[i] == d2[i]);
	}
	return 0;
}

int countDiscarded(int *c, int size) {
	int i;
	int dCount = 0;
	int tCount = 0;
	for(i = 0; i < size; i++) {
		if(c[i] == copper || c[i] == silver || c[i] == gold)
		{
			tCount++;
			printf("here\n");
			if(tCount == 2)
				break;
		}
		else
			dCount++;
	}
	return dCount;
}

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


int createRandomDecksHands(struct gameState* G) {

	int curPlayer, p1 = 0, p2 = 1, p3 = 2, p4 = 3;
	int handCount = 5;
	int deckCount = MAX_DECK - handCount;
	int i;
	createRandomHand(G->hand[p1], handCount);
	createRandomHand(G->hand[p2], handCount);
	createRandomHand(G->hand[p3], handCount);
	createRandomHand(G->hand[p4], handCount);

	G->handCount[p1] = handCount;
	G->handCount[p2] = handCount;	
	G->handCount[p3] = handCount;	
	G->handCount[p4] = handCount;

	createRandomDeck(G->deck[p1], deckCount);
	createRandomDeck(G->deck[p2], deckCount);
	createRandomDeck(G->deck[p3], deckCount);
	createRandomDeck(G->deck[p4], deckCount);

	G->deckCount[p1] = deckCount;
	G->deckCount[p2] = deckCount;	
	G->deckCount[p3] = deckCount;	
	G->deckCount[p4] = deckCount;
	
	setDiscardDeck(G->discard[p1], MAX_DECK);
	setDiscardDeck(G->discard[p2], MAX_DECK);
	setDiscardDeck(G->discard[p3], MAX_DECK);
	setDiscardDeck(G->discard[p4], MAX_DECK);

	G->discardCount[p1] = 0;
	G->discardCount[p2] = 0;	
	G->discardCount[p3] = 0;	
	G->discardCount[p4] = 0;
}

int effectAdventure2(struct gameState *state, struct infosStruct *infos);

int main() 
{

	srand(time(NULL));
	int INTSIZE = sizeof(int);
	struct gameState G;
	struct infosStruct infos;
	int numPlayers = 4;
	int hCount1, hCount2;
	int handCountBefore, handCountAfter;
	int deckCountBefore, deckCountAfter;
	int curPlayer;
	int tCount1, tCount2;
	int tCountDeck1, tCountDeck2;
	int deckCopy[MAX_DECK];

	createRandomDecksHands(&G);
	
	infos.drawntreasure = 0;
	infos.currentPlayer = 0;
	infos.z = 0;

	memcpy(&deckCopy, G.deck[0], sizeof(G.deck[0]));
	int i;


	int dCount = countDiscarded(deckCopy, 495);


	dCount += G.discardCount[0];

	printf("d %d\n", dCount);

	hCount1 = G.handCount[0];
	tCount1 = countTreasureCards(G.hand[0], G.handCount[0]);
	tCountDeck1 = countTreasureCards(G.deck[0], G.deckCount[0]);


	effectAdventure2(&G, &infos);


	//assert(dCount == G.discardCount[0]);
	printf("d %d\n", G.discardCount[0]);
	hCount2 = G.handCount[0];
	tCount2 = countTreasureCards(G.hand[0], G.handCount[0]);
	tCountDeck2 = countTreasureCards(G.deck[0], G.deckCount[0]);
	assert(hCount1 + 2 == hCount2);
	assert(tCount1 + 2 == tCount2);
	assert(tCountDeck1 - 2 == tCountDeck2);
	

}


int effectAdventure2(struct gameState *state, struct infosStruct *infos) {
  int drawntreasure2 = infos->drawntreasure;
  int currentPlayer = infos->currentPlayer;
  int cardDrawn = infos->cardDrawn;
  int *temphand = (infos->temphand);
  int z = infos->z;
  int handPos = infos->handPos;
  int i = infos->i;

  while(drawntreasure2<2) {
    if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
      drawntreasure2++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
      }
      while(z-1>=0){
  state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
  z=z-1;
      }
      return 0;
      
}

// struct gameState {
//   int numPlayers; //number of players
//   int supplyCount[treasure_map+1];  
//   int embargoTokens[treasure_map+1];
//   int outpostPlayed;
//   int outpostTurn;
//   int whoseTurn;
//   int phase;
//   int numActions; /* Starts at 1 each turn */
//   int coins; /* Use as you see fit! */
//   int numBuys; /* Starts at 1 each turn */
//   int hand[MAX_PLAYERS][MAX_HAND];
//   int handCount[MAX_PLAYERS];
//   int deck[MAX_PLAYERS][MAX_DECK];
//   int deckCount[MAX_PLAYERS];
//   int discard[MAX_PLAYERS][MAX_DECK];
//   int discardCount[MAX_PLAYERS];
//   int playedCards[MAX_DECK];
//   int playedCardCount;
// };