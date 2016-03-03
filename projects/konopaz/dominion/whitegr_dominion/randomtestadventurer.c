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

int checkAdventurerCard(int p, struct gameState *post);
void RandomCards(struct gameState *G);
void GameDetails(struct gameState *G);

int checkAdventurerCard(int p, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int who = post->whoseTurn;
  printf("Who: %d\n",who);
  int i;
  int handPos;
  for(i=0;i<post->handCount[who]; i++){
  	if(post->hand[who][i]== adventurer){
		handPos = i;
	}       
  }
  printf("Pre:\n"); 
  GameDetails(&pre);

  adventurerCard(0,0,0,post,handPos,0);
  printf("Post:\n");
  GameDetails(post); 



   printf("Player Hand After Play:\n");
  printHand(who,post);



  //Check if Player gets two treasure cards from their deck
  int postHandCount = post->handCount[who];
  int newTreasure1 = post->hand[who][postHandCount-1];
  int newTreasure2 = post->hand[who][postHandCount-2];
  printf("New Treasuer1: %d\n",newTreasure1 );
  printf("New Treasuer2: %d\n",newTreasure2 );

  if (newTreasure1 < 4 &&  newTreasure1 > 6) {
	printf("Last card put in hand is not treasure\n");
  }
   if (newTreasure2 < 4 && newTreasure2 > 6 ) {
	printf("Second to last card put in hand is not treasure\n");
  }

if (pre.deckCount[who] >=3){



 
  //Check if retrieved the correct cards
  printDeck(pre.whoseTurn,&pre);
  int n;
  n = pre.deckCount[who]-1;
  int decktreasure1;
  int decktreasure2;
  printf("Deck Count: %d\n",n);
  while(n>=0){
	if(pre.deck[who][n]== copper || pre.deck[who][n]== silver || pre.deck[who][n]== gold){
		decktreasure2 = pre.deck[who][n];
                break;
	}  
   n--;    
  }
  n--;
  while(n>=0){
	if(pre.deck[who][n]== copper || pre.deck[who][n]== silver || pre.deck[who][n]== gold){
		decktreasure1 =  pre.deck[who][n];
                break;
	}     
   n--; 
  }

  printf("Next Deck Treasuer1: %d\n",decktreasure1 );
  printf("Next Deck Treasuer2: %d\n",decktreasure2 );
 
  


   if ( decktreasure2 != newTreasure2){
	printf("Deck Treasure2 not matching hand Treasure: deck: %d , hand: %d\n",decktreasure2, newTreasure2);
  }


  if ( decktreasure1 != newTreasure1){
	printf("Deck Treasure1 not matching hand Treasure: deck: %d , hand: %d\n",decktreasure1, newTreasure1);
  }





  //Drawn Cards are discarded
  if(pre.discard[who]==post->discard[who]){
      printf("Discard unchanged");
  }

  printf("Pre Discard Count: %d\n",pre.discardCount[who]);
  printf("Post Discard Count: %d\n",post->discardCount[who]);
  printf("pre deckCount %d",pre.deckCount[who]);

  if(pre.deckCount[who] - (n+2) != (post->discardCount[who]-pre.discardCount[who])){
     printf("Incorrect # discard cards\n");
  }
}

  //Check new hand count
  if(pre.handCount[who] +1 != post->handCount[who])
  	printf("Hand Count Incorrect! - pre: %d , post: %d\n",pre.handCount[who],post->handCount[who]);



  //No state changes
  //check state change of other players cards

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

  printf ("Testing Adventurer Card.\n");

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
    checkAdventurerCard(p, &G);
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

		G->deckCount[p] = floor(Random() * MAX_DECK_ADV)+0;
		G->discardCount[p] = floor(Random() * MAX_DECK_ADV)+5;
    		G->handCount[p] = floor(Random() * MAX_HAND_ADV)+3;

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
		G->hand[p][randomAdventurer] = adventurer;
         
	  if (G->deckCount[p] >=3){

                		do{
			treasure1Position = floor(Random() * G->deckCount[p]);
			treasure2Position = floor(Random() * G->deckCount[p]);
		}while(treasure1Position == treasure2Position);

		printf("TreasurePosition1: %d\n",treasure1Position);
		printf("TreasurePosition2: %d\n",treasure2Position);


               		 G->deck[p][treasure1Position] =  4;
		G->deck[p][treasure2Position] =  6;
	
	}else {

		do{
			treasure1Position = floor(Random() * G->discardCount[p]);
			treasure2Position = floor(Random() * G->discardCount[p]);
		}while(treasure1Position == treasure2Position);

		printf("TreasurePosition1: %d\n",treasure1Position);
		printf("TreasurePosition2: %d\n",treasure2Position);


               		 G->discard[p][treasure1Position] =  4;
		G->discard[p][treasure2Position] =  6;

	}

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
        printDiscard(p,G);



}



 