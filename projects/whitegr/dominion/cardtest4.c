/*
 * cardtest4.c
      If you choose to trash 2 cards and have 2 or more cards in your hand after playing the Steward, then you must trash exactly 2 cards.
    You may choose to trash 2 cards, even if you only have 1 card left in your hand after playing the Steward; just trash the remaining card in your hand.
    You cannot mix and match - you either draw 2 cards, get Coin2.png, or trash 2 cards.  

 CODE:

 int stewardCard(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
    
	int currentPlayer = whoseTurn(state);

	if (choice1 == 1)
	{
	  //+2 cards
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state);
	}
      else if (choice1 == 2)
	{
	  //+2 coins
	  state->coins = state->coins + 2;
	}
      else
	{
	  //trash 2 cards in hand
	  discardCard(choice2, currentPlayer, state, 1);
	  discardCard(choice3, currentPlayer, state, 1);
	}
			
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

void RandomCards(struct gameState *G,int p);
void stewardTest (struct gameState *G, int handPos);


void stewardTest (struct gameState *post, int handPos) {

	int p = post->whoseTurn;
	post->coins = 5;
	post->numBuys = 2;
	post->numActions = 1;
	post->coins = 100;

	post->discardCount[p] = 1;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	stewardCard(1,0,0,post, handPos,0);
	if(pre.handCount[p] + 2 != post->handCount[p])
	{
		printf("ERROR: current player hand count\n");
	}

	stewardCard(2,0,0,post, handPos,0);
	if(pre.coins + 2 != post->coins)
	{
		printf("ERROR: coin problem\n");
	}
	

	stewardCard(3,1,2,post, handPos,0);
	if(pre.discardCount[p] + 2 != post->discardCount[p])
	{
		printf("ERROR: Intentional Problem - discard problem\n");
		printf("before-%d after-%d\n\n",pre.discardCount[p],post->discardCount[p]);

	}

	if(pre.numActions != post->numActions)
		printf("ERROR: State change with Actions\n");

	
	if(post->whoseTurn != pre.whoseTurn)
		printf("ERROR: State change with Player\n");

	//state change for other player
	int y;
	for(y=0;y<post->handCount[1];y++){

		if(post->hand[1][y]!=pre.hand[1][y]){
			printf("ERROR: Othe players cards have changed!.\n");
			printf("before-%d after-%d",pre.hand[1][y],post->hand[1][y]);
		}

	}
	
       //check if no change in buys
       if(post->numBuys != pre.numBuys)
	{
		printf("ERROR: State Change for buys.\n");
	}
	

         //check if no change in action
       if(post->numActions != pre.numActions)
	{
		printf("ERROR: State change for actions.\n");
	}

	
	
}

int main() {

    printf("Testing Steward Card cardtest4.\n");

        struct gameState G;

	int i;
	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	SelectStream(2);
	PutSeed(3);

	int player = 0;
	int stewardPosition;	

	
	for(i = 0; i < 10; i++)
	{
        
		RandomCards(&G,player);
		RandomCards(&G,player+1);
		stewardPosition = floor(Random() * G.handCount[player]);
		G.hand[player][stewardPosition] = steward;
		stewardTest(&G,stewardPosition);
	}

	
   printf("END Testing Steward Card cardtest4.\n");

	return 0;
}

void RandomCards(struct gameState *G,int p){

	G->whoseTurn = p;
	//G->numPlayers=2;
	G->whoseTurn=0;
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



  