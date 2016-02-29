#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>
#define DEBUG 1
#define NOISY_TEST 1

//  //discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
int checkDiscardCard(int handPos,  int currentPlayer, struct gameState *post, int trashFlag) {

  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int r;

  r = discardCard(handPos, currentPlayer, post, trashFlag);

  if (trashFlag < 1)
  {
    assert(post->playedCards[pre.playedCardCount] ==  pre.hand[currentPlayer][handPos]);
    assert(pre.playedCardCount + 1 == post->playedCardCount);
  }

  assert(post->hand[currentPlayer][handPos] = -1);

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
    assert( pre.hand[currentPlayer][ (pre.handCount[currentPlayer])] == post->hand[currentPlayer][ (post->handCount[currentPlayer] + 1) ] );
    assert( post->hand[currentPlayer][post->handCount[currentPlayer]] == -1 );
    assert( pre.handCount[currentPlayer] - 1 == post->handCount[currentPlayer] );
  }

  assert( r == 0 );
  return 0;
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount, toFlag, supplyPos, handPos, trash;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing DISCARDCARD.\n");

  SelectStream(2);
  PutSeed(3);

  for (i = 0; i < sizeof(struct gameState); i++) {
    ((char*)&G)[i] = floor(Random() * 256);
  }
  int handCountConst = floor(Random() * MAX_HAND);
  p = 0;
  handPos = 5;

  G.deckCount[p] = 40;
  G.discardCount[p] = 10;
  G.handCount[p] = 8;
  G.discard[p][G.discardCount[p]] = 100;
  G.playedCardCount = 3;
  G.playedCards[ G.playedCardCount ] = G.hand[p][handPos-1];

  trash = 0;

  //discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
  checkDiscardCard(handPos, p , &G, trash);    // checking trash = 0
  trash = 1;
  handPos = 6;
  checkDiscardCard(handPos, p , &G, trash);    // checking trash = 1
  G.handCount[p] = 1;
  checkDiscardCard(handPos, p , &G, trash);    // checking trash = 1

  // checkDiscardCard(supplyPos, &G, 1, p); // checking toFlag = 1
  // checkDiscardCard(supplyPos, &G, 2, p); // checking toFlag = 2
  // checkDiscardCard(-1, &G, -1, p); ////check if supply pile is empty (0) or card is not used in game (-1)

  printf ("ALL TESTS OK FOR DISCARDCARD\n\n");
  exit(0);
  return 0;
}
