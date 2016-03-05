/* Testing scoreFor() unitTest1.c
 
   SUMMARY:
   For a the player calulate score from:
       1. hand
       2. the player discard pile
       3. and their deck

   FUNCTION TO TEST: 
   int scoreFor (int player, struct gameState *state) {

  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  return score;
}

 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int main() {

     printf("Testing scoreFor() unittest1.c\n");

     //Create Deck
     struct gameState G;
     int i;
     for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)&G)[i] = floor(Random() * 256);
     }

     int p = 0;
     G.whoseTurn = 0;
     G.deckCount[p] = 6;
     G.discardCount[p] = 6;
     G.handCount[p] = 6;  

     int k[10] = {curse, estate, duchy, province, great_hall,gardens,smithy,smithy,smithy};
     
       for(i=0;i<6;i++){
     		G.deck[p][i] = k[i];
     		G.discard[p][i] = k[i];
     		G.hand[p][i] = k[i];
		
       }
    
     struct gameState unmodified;
	memcpy(&unmodified, &G, sizeof(struct gameState));


     //Score from HAND
     int handSCORE;
     handSCORE = scoreFor(0, &G);
     printf("Player 1 Hand Score: %d\n",handSCORE);

     if (handSCORE != 30){
          printf("Check correct SCORE no garden...FALSE\n");
     }else {
	  printf("Check correct SCORE no garden...PASS\n");
     }
   
     p = 1;
     G.deckCount[p] = 0;
     G.discardCount[p] = 0;
     G.handCount[p] = 10;  
     G.whoseTurn = 1;
     for(i=0;i<10;i++){
     	//	G.deck[p][i] = k[i];
     	//	G.discard[p][i] = k[i];
     		G.hand[p][i] = k[i];		
       }

	
     handSCORE = scoreFor(1, &G);

     printf("Player 2 Hand Score: %d\n",handSCORE);
     
     if (handSCORE != 11){
          printf("Check correct SCORE garden card...FALSE\n");
     }else {
	  printf("Check correct SCORE garden card...PASS\n");
     }

     //check if no change in buys
       if(G.numBuys != unmodified.numBuys)
	{
		printf("ERROR: State Change for buys.\n");
	}

         //check if no change in action
       if(G.numActions != unmodified.numActions)
	{
		printf("ERROR: State change for actions.\n");
	}

	 //check if no change in coins
       if(G.coins != unmodified.coins)
	{
		printf("ERROR: State change for coins.\n");
	}

     printf("END Testing scoreFor() unittest1.c\n");

    return 0;
}
