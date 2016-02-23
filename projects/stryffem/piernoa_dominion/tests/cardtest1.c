#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 1
#define NOISY_TEST 1

int checkSmithy(struct gameState *post, int handPos, int currentPlayer) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;

  r = _goodSmithy(post, handPos);

  assert(pre.handCount[pre.whoseTurn] + 2 == post->handCount[post->whoseTurn]);
  //remove card from player's hand
  if ( handPos == (pre.handCount[currentPlayer] - 1) ) 	//last card in hand array is played
  {
    assert(pre.handCount[currentPlayer] - 1 == post->handCount[currentPlayer] );
  }
  else if ( pre.handCount[currentPlayer] == 1 ) //only one card in hand
  {
    assert( pre.handCount[currentPlayer] - 1 == post->handCount[currentPlayer] );
  }
  else
  {
    assert( pre.hand[currentPlayer][ (pre.handCount[currentPlayer])] + 1 == post->hand[currentPlayer][ (post->handCount[currentPlayer] + 1) ] );
    assert( post->hand[currentPlayer][post->handCount[currentPlayer]] == -1 );
    assert( pre.handCount[currentPlayer] + 2 == post->handCount[currentPlayer] );
  }

  assert( r == 0 );

  return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, handPos, randomCard, randomHandCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing CARD SMITHY.\n");

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
    G.handCount[p] = randomHandCount;

    /* initialize hand */

    // give the player real cards
    for ( j=0; j< randomHandCount; j++)
    {
      G.hand[p][j] = 0;
      randomCard = floor(Random() * 3);
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
      }
    }
    /* player two now has real cards */
    for ( j=0; j< randomHandCount; j++)
    {
      G.hand[1-p][j] = 0;
      randomCard = floor(Random() * 3);
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
      }
    }
    G.whoseTurn = 0;
    handPos = 0;

    handPos = 5;

    G.deckCount[p] = 40;
    G.discardCount[p] = 10;
    G.handCount[p] = 8;
    G.discard[p][G.discardCount[p]] = 100;
    G.playedCardCount = 3;
    G.playedCards[ G.playedCardCount ] = G.hand[p][handPos-1];

    r = checkSmithy(&G, handPos, p);


  }
  printf ("ALL TESTS OK FOR SMITHY \n\n");
  exit(0);
  return 0;
}
