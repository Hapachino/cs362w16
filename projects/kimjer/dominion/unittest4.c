#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#define NUMCARDS 10

int main() {

	struct gameState G;

	int seed = 1000;
	int t1;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers, k, seed, &G);
	G.whoseTurn = 0;
	t1 = G.whoseTurn;

	endTurn(&G);
	t1 = G.whoseTurn;
	assert(t1 == 1);

	endTurn(&G);
	t1 = G.whoseTurn;
	assert(t1 == 2);

	endTurn(&G);
	t1 = G.whoseTurn;
	assert(t1 == 3);

	endTurn(&G);
	t1 = G.whoseTurn;
	assert(t1 == 0);
	return 0;
}


// int endTurn(struct gameState *state) {
//   int k;
//   int i;
//   int currentPlayer = whoseTurn(state);
  
//   //Discard hand
//   for (i = 0; i < state->handCount[currentPlayer]; i++){
//     state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
//     state->hand[currentPlayer][i] = -1;//Set card to -1
//   }
//   state->handCount[currentPlayer] = 0;//Reset hand count
    
//   //Code for determining the player
//   if (currentPlayer < (state->numPlayers - 1)){ 
//     state->whoseTurn = currentPlayer + 1;//Still safe to increment
//   }
//   else{
//     state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
//   }

//   state->outpostPlayed = 0;
//   state->phase = 0;
//   state->numActions = 1;
//   state->coins = 0;
//   state->numBuys = 1;
//   state->playedCardCount = 0;
//   state->handCount[state->whoseTurn] = 0;

//   //int k; move to top
//   //Next player draws hand
//   for (k = 0; k < 5; k++){
//     drawCard(state->whoseTurn, state);//Draw a card
//   }

//   //Update money
//   updateCoins(state->whoseTurn, state , 0);

//   return 0;
// }