#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>  // rand(), srand()
#include <math.h>
#define MAX_TESTS 1000

int checkAdventurer(struct gameState *post) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r = 0, j=0;


  /* Coint Count Before */
  int preCount = pre.handCount[0];
	int preCoins = pre.coins;
	int postCoins = 0;
		for(j = 0; j < pre.handCount[0]; j++){
			if(pre.hand[0][j] == copper){
				preCoins += 1;
				preCount++;
			}
			if(pre.hand[0][j] == silver){
				preCoins += 2;
				preCount++;
			}
			if(pre.hand[0][j] == gold){
				preCoins += 3;
				preCount++;
			}
		}

  cardEffect(adventurer, 1,1,1, post, 0 ,&r);

  /* Test supply count change */
  if( pre.supplyCount[copper] != post->supplyCount[copper] ) {
    printf("\n Fail copper: expected %d, got %d", pre.supplyCount[copper], post->supplyCount[copper] );
  }
  if( pre.supplyCount[silver] != post->supplyCount[silver] ) {
    printf("\n Fail silver: expected %d, got %d", pre.supplyCount[silver], post->supplyCount[silver] );
  }
  if( pre.supplyCount[gold] != post->supplyCount[gold] ) {
    printf("\n Fail gold: expected %d, got %d", pre.supplyCount[gold], post->supplyCount[gold] );
  }

  /* played card count */
  // if(post->playedCardCount != pre.playedCardCount + 1) {
  //   printf("failed card count");
  // }

  if(pre.handCount[0] + 2 != post->handCount[0])	 {
    printf("\n Fail: hand count: expected %d, got %d ",pre.handCount[0] + 2, post->handCount[0] );
  }

  /* count coins */


		for(j = 0; j < post->handCount[0]; j++){
			if(post->hand[0][j] == copper){
				postCoins += 1;
			}
			if(post->hand[0][j] == silver){
				postCoins += 2;
			}
			if(post->hand[0][j] == gold){
				postCoins += 3;
			}
		}

    if ( preCoins < postCoins){
      printf("\n coin count failed: expected %d to be > %d", preCoins, postCoins);
    }

  printf("\n");
  return 0;
}

//Random Tests For The Adventurer Card

int main() {

  int k[10] = {adventurer, duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, smithy};

  int i, j, n, p, r, players, handCount, deckCount, seed, address;
  //struct gameState state;
  struct gameState G;
  //G = malloc(sizeof(struct gameState));
  printf("Random Adventurer Test\n");
  for (i = 0; i < MAX_TESTS; i++) {

    players = (rand() % 3) + 2;
    p = 0;
    srand(time(NULL));		//pick random seed
    //newGame();

    players = (rand()%3)+2;						// random number of players within valid range
    //initializeGame(players, k, 1000, &G);


    initializeGame(players, k, 9999 , &G);	//initialize Gamestate
    int maxDeck = rand()%MAX_DECK + 1;					// random deck amount in valid range
    G.deckCount[p] = maxDeck;						// set for player in question
    G.handCount[p] = rand()%6 + 1;					// random starting hand, lower boundary
    int position = rand()%G.handCount[p] + 1;			// pick a hand location
    G.hand[p][position] = adventurer;				// make sure adventurer is present
    for(j = 0; j < maxDeck; j++){					// make sure deck is random
      if(j == position)
        continue;
      G.deck[p][j] = rand()%17+1;
    }
    G.playedCardCount = 0;
    G.whoseTurn = 0;
    //
    // //  //Initiate valid state variables
    // G.deckCount[p] = rand() % MAX_DECK + 1; //Pick random deck size out of MAX DECK size
    // G.discardCount[p] = rand() % MAX_DECK + 1;
    // G.handCount[p] = rand()%6 + 1;
    // G.numPlayers = 2;
    //
    // G.whoseTurn = p;
    // handCount = rand() % G.handCount[p] + 1;
    // deckCount = G.deckCount[p];
    //
    // G.deckCount[1-p] = rand() % MAX_DECK + 1; //Pick random deck size out of MAX DECK size
    // G.discardCount[1-p] = rand() % MAX_DECK + 1;
    // G.handCount[1-p] = rrand() % G.handCount[p] + 1;
    //
    // // // 	 //printf("\n hand count before %d", G.handCount[p]);
    for ( j=0; j< G.handCount[p]; j++)
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

    if (rand() % 3 == 0) {
      G.deckCount[p] = 0;
    }


    checkAdventurer(&G);
  }
  printf("Tests Complete\n");

  return 0;
}
