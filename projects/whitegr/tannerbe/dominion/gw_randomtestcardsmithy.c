 /* Smithy Card
       1. effect +3 Cards
       2. Verify discard
      3. verify State Change
   
   CODE REFERENCE: 
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
   int drawCard(int player, struct gameState *state)
{	int count;
  int deckCounter;
  if (state->deckCount[player] <= 0){//Deck is empty
    
    //Step 1 Shuffle the discard pile back into a deck
    int i;
    //Move discard to deck
    for (i = 0; i < state->discardCount[player];i++){
      state->deck[player][i] = state->discard[player][i];
      state->discard[player][i] = -1;
    }

    state->deckCount[player] = state->discardCount[player];
    state->discardCount[player] = 0;//Reset discard

    //Shufffle the deck
    shuffle(player, state);//Shuffle the deck up and make it so that we can draw
   
    if (DEBUG){//Debug statements
      printf("Deck count now: %d\n", state->deckCount[player]);
    }
    
    state->discardCount[player] = 0;

    //Step 2 Draw Card
    count = state->handCount[player];//Get current player's hand count
    
    if (DEBUG){//Debug statements
      printf("Current hand count: %d\n", count);
    }
    
    deckCounter = state->deckCount[player];//Create a holder for the deck count

    if (deckCounter == 0)
      return -1;

    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  else{
    int count = state->handCount[player];//Get current hand count for player
    int deckCounter;
    if (DEBUG){//Debug statements
      printf("Current hand count: %d\n", count);
    }

    deckCounter = state->deckCount[player];//Create holder for the deck count
    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
    state->deckCount[player]--;
    state->handCount[player]++;//Increment hand count
  }

  return 0;
}

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from player's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else 	
    {
        //replace discarded card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
	
  return 0;
}



 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#include <stdlib.h>

#define MAX_HAND_ADV 6
#define MAX_DECK_ADV 20
#define DEBUG 0
#define NOISY_TEST 1

int  checkSmithyCard(int p, struct gameState *post);
void RandomCards(struct gameState *G);
void GameDetails(struct gameState *G);

int  checkSmithyCard(int p, struct gameState *post) {
  
                     struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

                    int who = post->whoseTurn;
  	printf("Who: %d\n",who);
  	int i;
  	int handPos;
  	for(i=0;i<post->handCount[who]; i++){
  	if(post->hand[who][i]== smithy){
		handPos = i;
	}       
 	 }
                     printf("HandPosition: %d",handPos);
  	printf("Pre:\n"); 
  	GameDetails(&pre);

	
	//smithyCard(0,0,0,post,handPos,0);
                    cardEffect(smithy, 0, 0, 0, post, handPos, 0); 

                   printf("Post:\n");
                   GameDetails(post); 
                   
	if(post->handCount[0]+2 != pre.handCount[0]){
		printf("Error in Hand Count \n");
	}


	return (0);
	int d;
	int numAfterSmithys=0;
	for(d=0;d<post->handCount[who];d++){
		if(post->hand[who][d] == smithy){
			numAfterSmithys++;
		}		
	}

                    	int numUnmodifiedSmithys=0;
	for(d=0;d<pre.handCount[who];d++){
		if(pre.hand[who][d] == smithy){
			numUnmodifiedSmithys++;
		}		
	}

	if (numAfterSmithys + 1 != numUnmodifiedSmithys){
		printf ("Error Discarding Smithy\n");
		printf("before-%d after-%d\n",numAfterSmithys,numUnmodifiedSmithys);
	}


	//Check got right cards from deck
                     int firstDeck;
     
                     firstDeck = pre.deck[who][pre.deckCount[who]-1];
             	firstDeck = pre.deck[who][pre.deckCount[who]-2];
	firstDeck = pre.deck[who][pre.deckCount[who]-3];
             
                     if(firstDeck!=post->hand[who][post->deckCount[who]-3]){
		printf("Incorrect Card Moved To Hand");
	}
             
	   if(firstDeck!=post->hand[who][post->deckCount[who]-2]){
		printf("Incorrect Card Moved To Hand");
	}

	   if(firstDeck!=post->hand[who][post->deckCount[who]-1]){
		printf("Incorrect Card Moved To Hand");
	}


	if(post->handCount[who]+2 != pre.handCount[who]){
		printf("Error in Hand Count - Intentional Bug\n");
	}


	if(post->playedCards[post->playedCardCount-1]!=13){
		printf("Last played card is not Smithy");
	}


  	//Check for state changes after playing smithy

  	//Check state change of other players cards
  	int check=0;
  	if (pre.numPlayers == 2){
	if(pre.whoseTurn==1){
	   check=0;
	} else{
	   check=1;
	}
 
	int y;
  	for(y=0;y<post->handCount[check];y++){

 	    if(post->hand[check][y]!=pre.hand[check][y]){
 	    	printf("ERROR: Othe players cards have changed!.\n");
 	     	printf("before-%d after-%d",pre.hand[1][y],post->hand[1][y]);
 	    }

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

   	//check if no change in coins
   	if(post->coins != pre.coins)
   	{	
	printf("ERROR: State change for coins.\n");
   	}

 	return 0;


}



int main () {

  int i, n, p;

  struct gameState G;

  printf ("Testing Smithy Card.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    printf("TEST: %d\n",n);
    p = floor(Random() * 2)+1;
    G.numPlayers = p;
    printf("Num Players: %d\n",G.numPlayers);
    G.whoseTurn = floor(Random() * p);
    printf("Player Turn: %d\n",G.whoseTurn);
    RandomCards(&G);
    //GameDetails(&G);
    checkSmithyCard(p, &G);
    printf("END TEST: %d\n\n\n",n);
  }

  exit(0);

}

void RandomCards(struct gameState *G){

	int p;
	int randomAdventurer;
        int treasure1Position = 0;
	int treasure2Position = 0;
	
	for(p=0;p<G->numPlayers;p++)
	{

		printf("player: %d",p);

		G->deckCount[p] = floor(Random() * MAX_DECK_ADV)+5;
		G->discardCount[p] = floor(Random() * MAX_DECK_ADV)+5;
    		G->handCount[p] = floor(Random() * MAX_HAND_ADV)+3;
		G->playedCardCount = 0;

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
	
		//int w;
		//for(w = 0; w < G->playedCardCount; w++)
		//{
		//	G->playedCards[w] = floor(Random() * treasure_map) + 1;
		//}

		randomAdventurer = floor(Random() * G->handCount[p]);

		printf("HandSize: %d\n",G->handCount[p]);
		printf("A location: %d\n",randomAdventurer);
		G->hand[p][randomAdventurer] = smithy;

                do{
			treasure1Position = floor(Random() * G->deckCount[p]);
			treasure2Position = floor(Random() * G->deckCount[p]);
		}while(treasure1Position == treasure2Position);

		printf("TreasurePosition1: %d\n",treasure1Position);
		printf("TreasurePosition2: %d\n",treasure2Position);

               		 G->deck[p][treasure1Position] =  4;
		G->deck[p][treasure2Position] =  6;

		G->numBuys = floor(Random() * 10);
		G->numActions = floor(Random() * 10);
		G->coins = floor(Random() * 10);

                

	}


}

void GameDetails(struct gameState *G){

	int p;
        p=G->whoseTurn;
	
	printf("Player: %d\n",p);
	printHand(p,G);
        printDeck(p,G);
        printPlayed(p,G);



}
