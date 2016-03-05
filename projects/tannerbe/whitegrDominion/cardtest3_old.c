/*
 * cardtest1.c Council_Room
   cost 5 coins
   Action +4 cards, +1 Buy, All other players draw a card

   int council_roomCard(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
	
	int i;
	int currentPlayer = whoseTurn(state);

	
	//+4 Cards
      for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //+1 Buy
      state->numBuys++;
			
      //Each other player draws a card
      for (i = 0; i < state->numPlayers; i++)
	{
	 
	      drawCard(i, state);
	}
			
      //put played card in played card pile
      discardCard(handPos, currentPlayer, state, 0);
			
      return 0;
		
}


 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>


void RandomCards(struct gameState *G,int p){

	G->whoseTurn = p;

	 G->deckCount[p] = floor(Random() * MAX_DECK)+1;
         G->discardCount[p] = floor(Random() * MAX_DECK)+1;
         G->handCount[p] = floor(Random() * MAX_HAND)+1;
	 G->playedCardCount = floor(Random() * MAX_DECK)+1;
	
	int x;	
	for(x = 0; x < G->handCount[p]; x++)
	{
		G->hand[p][x] = floor(Random() * treasure_map) + 1;
	}
		
        int y;
	for(y = 0; y < G->discardCount[p]; y++)
	{
		G->discard[p][y] = floor(Random() * treasure_map) + 1;
	}

	int z;
	for(z = 0; z < G->deckCount[p]; z++)
	{
		G->deck[p][z] = floor(Random() * treasure_map) + 1;
	}
	
	int w;
	for(w = 0; w < G->playedCardCount; w++)
	{
		G->playedCards[w] = floor(Random() * treasure_map) + 1;
	}

}


int testPlayCouncil_Room(struct gameState *post, int handPos)
{
	int i;
	int p = post->whoseTurn;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	council_roomCard(0,0,0,post, handPos,0);

	if(pre.numBuys + 1 != post->numBuys)
	{
		printf("ERROR: Incorrect Number of Buys.");
	}

	//Check if discarding
	if(pre.handCount[p] + 3 != post->handCount[p])
	{
		printf("ERROR (intentional): current player handcount is %d\n",post->handCount[p]);
		printf("Cards in hand should be: %d\n\n",pre.handCount[p] + 3);
	}

	//check if hasndpos still pointing to a Council_Room
	if(post->hand[0][handPos] == 8){

		printf("Possible Error: Handpos still pointing at Council_Room");
	}

	if(post->playedCards[post->playedCardCount-1]!=8){
		printf("Last played card is not Council_Room");
	}

	for(i = 0; i < pre.numPlayers; i ++)
	{
		if(i != p)
		{
			pre.handCount[i]++;
			if(pre.handCount[i] != post->handCount[i])
			{
				printf("ERROR: Other players didn't get a card");
			}
		}
	}

	if(pre.numActions != post->numActions)
		printf("ERROR: State change with Actions");

	
	if(post->whoseTurn != pre.whoseTurn)
		printf("ERROR: State change with player");
	
	if(pre.coins != post->coins)
		printf("ERROR: State change with player");
		
	return 0;
}

int main()
{
	printf("Testing Council Room Card cardtest3.c\n");

	struct gameState G;

	int i;
	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	SelectStream(2);
	PutSeed(3);

	int player = 0;
	int smithyPosition;	
	
	
	for(i = 0; i < 10; i++)
	{
        
		RandomCards(&G,player);
		RandomCards(&G,player+1);
		G.numPlayers=2;
		smithyPosition = floor(Random() * G.handCount[player]);
		G.hand[player][smithyPosition] = smithy;
		testPlayCouncil_Room(&G, smithyPosition);
	}
	
	printf("END Testing Council Room Card cardtest3.c\n");
	return 0;

	

}
   