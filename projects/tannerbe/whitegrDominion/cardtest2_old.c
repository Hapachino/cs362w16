/* Adventurer Cards
   1. Player gets two treasure cards from their deck
   2. Drawn Cards are discarded
   3. No state changes
   
   CODE REFERENCE: 
   int adventurerCard(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
   {
	
   int z=0;
   int cardDrawn;
   int drawntreasure=1;
   int currentPlayer = whoseTurn(state);
   int temphand[MAX_HAND];
	
   while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
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


 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int AdventurerTest(struct gameState *post, int handPos);
void RandomGameState(struct gameState *G,int p);

void RandomCards(struct gameState *G,int p){

	G->whoseTurn = p;

	 G->deckCount[p] = floor(Random() * MAX_DECK)+1;
         G->discardCount[p] = floor(Random() * MAX_DECK)+1;
         G->handCount[p] = floor(Random() * MAX_HAND)+1;
	 G->playedCardCount = 6;
	
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
		G->playedCards[w] = curse;
	}

}

int main()
{
	printf("Testing Adventurer Card cardtest2.\n");

	struct gameState G;

	int i;
	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)&G)[i] = floor(Random() * 256);
	}
	
	SelectStream(2);
	PutSeed(3);

	int player = 0;
	int adventurerPosition,treasure1Position,treasure2Position;	
	treasure1Position = 0;
	treasure2Position = 0;
	
	for(i = 0; i < 3; i++)
	{
        
		RandomCards(&G,player);
		RandomCards(&G,player+1);
		G.whoseTurn = 0;
		G.numPlayers=2;
		while(treasure1Position != treasure2Position){
			treasure1Position = floor(Random() * G.deckCount[0]);
			treasure2Position = floor(Random() * G.deckCount[0]);
		}
		
		//make sure we have two treasures in the deck
		G.deck[player][treasure1Position] = treasure1Position;
		G.deck[player][treasure2Position] = treasure2Position;
		adventurerPosition = floor(Random() * G.handCount[0]);
		G.hand[0][adventurerPosition] = adventurer;
		AdventurerTest(&G,adventurerPosition);
	}
	
	printf("END Testing Adventurer Card cardtest2.\n");
	return 0;
}

int AdventurerTest(struct gameState *G, int handPos)
{
 
	int p = G->whoseTurn;
	G->whoseTurn=0;
	struct gameState unmodified;
	memcpy(&unmodified, G, sizeof(struct gameState));
	adventurerCard(0,0,0,G,handPos,0);

	int beforeHandTreasures = 0;
	int handTreasures = 0;
	int cardsInHands = G->handCount[p];
	int i;
	int cardDrawn;
	for (i=0;i<cardsInHands;i++){
		cardDrawn = G->hand[p][i];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
			handTreasures++;
		}
	}

	cardsInHands = unmodified.handCount[p];
	for (i=0;i<cardsInHands;i++){
		cardDrawn = unmodified.hand[p][i];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
			beforeHandTreasures++;
		}
	}
	
	if (beforeHandTreasures +2 !=handTreasures ){
		printf("Incorrect Number of Treasures in HAND!\n");
		printf("Before - %d\n",beforeHandTreasures);
		printf("After - %d\n\n",handTreasures);
	}

	

	int z;
	int pA=0;
	for(z=0;z<G->playedCardCount;z++){
		if(G->playedCards[z]==adventurer){
			pA++;
		}

	}
	printf("PA-%d",pA);
	if(pA!=1){
		printf("Error: Could Not find adventure card in played cards\n");
	}



        //check if discard not same
	if (unmodified.discardCount[p] == G->discardCount[p]) {
		printf("Card not discarded from hand!\n");
	}

	 //state change - check if no change in buys
        if(G->numBuys != unmodified.numBuys)
	{
		printf("ERROR: State Change for buys.\n");
	}

         //state change - check if no change in action
        if(G->numActions != unmodified.numActions)
	{
		printf("ERROR: State change for actions.\n");
	}	

	//Check state change of other players cards
	int y;
	for(y=0;y<G->handCount[1];y++){
		if(G->hand[1][y]!=unmodified.hand[1][y]){
			printf("ERROR: Othe players cards have changed!.\n");
			printf("before-%d after-%d",unmodified.hand[1][y],G->hand[1][y]);
		}

	}

		
	return 0;
}   