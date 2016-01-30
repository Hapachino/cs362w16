#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 1
#define NOISY_TEST 1

int checkCouncilRoom(struct gameState *post, int handPos) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int p2 = 1- pre.whoseTurn;

  printf("\n * 1 \n ");

  int r;
  r = _goodCouncilRoom(post, handPos);

  printf("\n * 2 \n ");


  // assert this current player has +3 cards ( +4 cards -1 for discard )
  assert( pre.handCount[0] + 3 == post->handCount[0] );

  printf("\n * 3 \n ");


  // assert incremented numBuys
  assert( pre.numBuys + 1 == post->numBuys);

  printf("\n * 4 \n ");


  // assert player 2 has drawn a card;
  assert( pre.handCount[p2] + 1 == post->handCount[p2] );


  printf("\n * 5 \n ");


  // assert played card cound increments
  assert(pre.playedCardCount + 1 == post->playedCardCount );


  printf("\n * 6 \n ");


  return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, handPos, randomCard, randomHandCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing CARD councilRoom.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 1; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    randomHandCount = floor(Random() * MAX_HAND);

    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[1-p] = floor(Random() * MAX_DECK);
    G.handCount[p] = randomHandCount;
    G.numBuys = 0;
    G.numPlayers = 2;

    /* initialize hand */

    //give the player real cards
    for ( j=0; j< randomHandCount; j++)
    {
      G.hand[p][j] = 0;
      randomCard = floor(Random() * 3);
      switch (randomCard) {
        case 0:
          G.hand[p][j] = adventurer;
          break;
        case 1:
          G.hand[p][j] = silver;
          break;
        case 2:
          G.hand[p][j] = gold;
          break;
      }
    }


    int p2 = 1-p;
    for ( j=0; j< randomHandCount; j++)
    {
      G.hand[p2][j] = 0;
      randomCard = floor(Random() * 6);
      switch (randomCard) {
        case 0:
          G.hand[p2][j] = adventurer;
          break;
        case 1:
          G.hand[p2][j] = silver;
          break;
        case 2:
          G.hand[p2][j] = gold;
          break;
        case 3:
          G.hand[p2][j] = adventurer;
          break;
        case 4:
          G.hand[p2][j] = council_room;
          break;
        case 5:
          G.hand[p2][j] = feast;
          break;
        case 6:
          G.hand[p2][j] = gardens;
          break;
      }
    }

    // /* player two now has real cards */
    // for ( j=0; j< randomHandCount; j++)
    // {
    //   G.hand[1-p][j] = 0;
    //   randomCard = floor(Random() * 3);
    //   switch (randomCard) {
    //     case 0:
    //       G.hand[1-p][j] = copper;
    //       break;
    //     case 1:
    //       G.hand[1-p][j] = silver;
    //       break;
    //     case 2:
    //       G.hand[1-p][j] = gold;
    //       break;
    //   }
    // }
    G.whoseTurn = 0;
    handPos = 0;

    handPos = 5;

    G.deckCount[p] = 40;
    G.discardCount[p] = 10;
    G.handCount[p] = 8;
    G.discard[p][G.discardCount[p]] = 100;
    G.playedCardCount = 3;
    G.playedCards[ G.playedCardCount ] = G.hand[p][handPos-1];

    r = checkCouncilRoom( &G, handPos );


  }
  printf ("ALL TESTS OK FOR councilRoom \n\n");
  exit(0);
  return 0;
}
