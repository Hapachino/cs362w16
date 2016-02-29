#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>  // rand(), srand()
#include <assert.h>

int checkSmithy(struct gameState* post, int handPos, int currentPlayer) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r = 0;
  int p2 = 1;

  cardEffect(smithy, 1,1,1, post, handPos ,&r);

  /* Lose smithy  and gain 3 cards: net + 2 cards */
  if ( pre.handCount[pre.whoseTurn] + 2 != post->handCount[post->whoseTurn] ) {
    printf("\nfail 1: expected %d, got %d", pre.handCount[pre.whoseTurn] + 2 , post->handCount[post->whoseTurn] );
  }

  /* Card supplies should have changed */
  if ( pre.supplyCount[copper] != post->supplyCount[copper] ) {
    printf("fail copper supply count: expected %d, got %d ", pre.supplyCount[copper] , post->supplyCount[copper]);
  }
  if ( pre.supplyCount[silver] != post->supplyCount[silver] ) {
    printf("fail silver supply count: expected %d, got %d ", pre.supplyCount[silver] , post->supplyCount[silver]);
  }
  if ( pre.supplyCount[gold] != post->supplyCount[gold] ) {
    printf("fail gold supply count: expected %d, got %d ", pre.supplyCount[gold] , post->supplyCount[gold]);
  }


  //remove card from player's hand
  if ( handPos == (pre.handCount[currentPlayer] - 1) ) 	//last card in hand array is played
  {
    if ( pre.handCount[currentPlayer] + 2  != post->handCount[currentPlayer] ) {
      printf("\nfail 2: expected %d, got %d ", pre.handCount[currentPlayer] + 2 , post->handCount[currentPlayer] );
    }
  }
  else if ( pre.handCount[currentPlayer] == 1 ) //only one card in hand
  {
    if ( pre.handCount[currentPlayer] + 2 != post->handCount[currentPlayer] ) {
      printf("\nfail 3: expected %d, got %d ", pre.handCount[currentPlayer] + 2, post->handCount[currentPlayer] );
    }
  }
  else
  {

    if ( post->hand[currentPlayer][post->handCount[currentPlayer]] != -1  ) {
      printf("\nfail 5: expected %d, got %d ", -1, post->hand[currentPlayer][post->handCount[currentPlayer]] );
    }

    if ( pre.handCount[currentPlayer] + 2 != post->handCount[currentPlayer] ){
      printf("\nfail 6: expected %d, got %d", pre.handCount[currentPlayer] + 2, post->handCount[currentPlayer]);
    }
  }

  return 0;
}

#define MAX_TESTS 1000

//This randomly tests Adventurer

int main() {

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int i, j, n, p, r, players, handPos, handCount, deckCount, seed, address;

  srand(time(NULL));		//pick random seed

	struct gameState G;

  printf("Smithy Test\n");

  for (i = 0; i < MAX_TESTS; i++) {
    seed = 0;
    players = ( rand() % 3 ) + 2; // new players
    p = 0;
	  initializeGame(players, k, rand() , &G);	//initialize Gamestate

    //Initiate valid state variables
    G.deckCount[p] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
    G.discardCount[p] = rand() % MAX_DECK;
    G.handCount[p] = rand() % MAX_HAND;
    G.numPlayers = 2;
    handPos = rand() % MAX_HAND;


  	G.whoseTurn = p;
  	handCount = G.handCount[p];
  	deckCount = G.deckCount[p];

  	G.deckCount[1-p] = rand() % MAX_DECK; //Pick random deck size out of MAX DECK size
  	G.discardCount[1-p] = rand() % MAX_DECK;
  	G.handCount[1-p] = rand() % MAX_HAND;
  	// G.whoseTurn = 1-p;
  	handCount = G.handCount[1-p];
  	deckCount = G.deckCount[1-p];
    // printf("\n hand count before %d", G.handCount[p]);
    for ( j=0; j< G.handCount[p] + 10; j++)
    {
      G.hand[p][j] = 1;
      int randomCard = floor(Random() * 6);
      switch (randomCard) {
        case 0:
          G.hand[p][j] = copper;
          break;
        case 1:
          G.hand[p][j] = silver;
          break;
        case 2:
          G.hand[p][j] = gold;
          break;
        case 3:
          G.hand[p][j] = adventurer;
          break;
        case 4:
          G.hand[p][j] = council_room;
          break;
        case 5:
          G.hand[p][j] = feast;
          break;
        case 6:
          G.hand[p][j] = gardens;
          break;
      }
    }
		for ( j=0; j< G.handCount[1-p] + 10; j++) {
       G.hand[1-p][j] = 0;
       int randomCard = floor(Random() * 6);
       switch (randomCard) {
         case 0:
           G.hand[1-p][j] = copper;
           break;
         case 1:
           G.hand[1-p][j] = silver;
           break;
         case 2:
           G.hand[1-p][j] = gold;
           break;
         case 3:
           G.hand[1-p][j] = adventurer;
           break;
         case 4:
           G.hand[1-p][j] = council_room;
           break;
         case 5:
           G.hand[1-p][j] = feast;
           break;
         case 6:
           G.hand[1-p][j] = gardens;
           break;
       }
     }

    if (rand() % 3 == 0) {
      G.deckCount[p] = 0;
      handPos = G.handCount[p] - 1;
    }
    if (rand() % 3 == 1) {
      G.handCount[p] = 1;
    }

    int handCountAfter =  G.handCount[p];
    int test2A = G.hand[p][ 0 ] ;

    int oiwe = checkSmithy( &G, handPos , p);

  }
  printf("\n\n\nTests Complete\n");

  return 0;
}
