/*
 *test Smithy Card
       CARD: type Action
       effect +3 Cards
       cost 4 coins
  
  CODE:
   int smithyCard(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
   {
	
	int i;
	int currentPlayer = whoseTurn(state);
	
	//+3 Cards
       for (i = 0; i <= 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
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
#include <math.h>

int SmithyCheck(struct gameState *post, int handPos);
void RandomGameState(struct gameState *G,int p);

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

int main()
{
	printf("Testing Smithy Card cardtest1.\n");

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
		RandomCards(&G,1);
		G.numPlayers=2;
		smithyPosition = floor(Random() * G.handCount[player]);
		G.hand[0][smithyPosition] = smithy;
		SmithyCheck(&G, smithyPosition);
	}
	
	printf("END Testing Smithy Card cardtest1.\n");
	return 0;
}

int SmithyCheck(struct gameState *G, int handPos)
{
	G->whoseTurn = 0;
	G->numBuys = 2;
	G->numActions = 1;
	G->coins = 100;
	G->phase=0;
	struct gameState unmodified;
	memcpy(&unmodified, G, sizeof(struct gameState));
	
	smithyCard(0,0,0,G,handPos,0);
	
	//check if moved to played pile
	int d;
	int numAfterSmithys=0;
	for(d=0;d<G->handCount[0];d++){

		if(G->hand[0][d] == smithy){
			numAfterSmithys++;
		}		

	}

	if(G->handCount[0]+2 != unmodified.handCount[0]){
		printf("Error in Hand Count - Intentional Bug\n");
	}


	if(G->playedCards[G->playedCardCount-1]!=13){
		printf("Last played card is not Smithy");
	}

	int numUnmodifiedSmithys=0;
	for(d=0;d<unmodified.handCount[0];d++){

		if(unmodified.hand[0][d] == smithy){
			numUnmodifiedSmithys++;
		}		

	}
	if (numAfterSmithys + 1 != numUnmodifiedSmithys){
		printf ("Error Discarding Smithy\n");
		printf("before-%d after-%d\n",numAfterSmithys,numUnmodifiedSmithys);

	}
	

	//check state change of other players cards
	int y;
	for(y=0;y<G->handCount[1];y++){

		if(G->hand[1][y]!=unmodified.hand[1][y]){
			printf("ERROR: Othe players cards have changed!.\n");
			printf("before-%d after-%d",unmodified.hand[1][y],G->hand[1][y]);
		}

	}
	
       //check if no change in buys
       if(G->numBuys != unmodified.numBuys)
	{
		printf("ERROR: State Change for buys.\n");
	}

         //check if no change in action
       if(G->numActions != unmodified.numActions)
	{
		printf("ERROR: State change for actions.\n");
	}

	 //check if no change in coins
       if(G->coins != unmodified.coins)
	{
		printf("ERROR: State change for coins.\n");
	}	


	return 0;
}   