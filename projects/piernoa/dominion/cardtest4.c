#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 1
#define NOISY_TEST 1

int checkRemodel(struct gameState *post, int handPos, int choice1, int choice2) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  int p2 = 1- pre.whoseTurn;
  int j = pre.hand[pre.whoseTurn][choice1];  //store card we will trash
  int preCount = 0;
  int postCount = 0;
  int i;

  for ( i = 0; i < pre.handCount[pre.whoseTurn]; i++)
  {
    if (pre.hand[pre.whoseTurn][i] == j)
    {
      preCount++;
    }
  }

  int r;
  r = _remodel(post, handPos, choice1, choice2);

  //if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
  if (getCost(post->hand[pre.whoseTurn][choice1]) + 2 > getCost(choice2) )
  {
    assert(r == -1);
    return 0;
  }

  for (i = 0; i < post->handCount[pre.whoseTurn]; i++)
  {
    if (post->hand[pre.whoseTurn][i] == j)
    {
      postCount++;
    }
  }

  assert( preCount > postCount);

  assert(r == 0); // success exit;

  return 0;
}

int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount, handPos, randomCard, randomHandCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing CARD remodel.\n");

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

    G.whoseTurn = 0;
    handPos = 0;

    handPos = 5;

    G.deckCount[p] = 40;
    G.discardCount[p] = 10;
    G.handCount[p] = 8;
    G.discard[p][G.discardCount[p]] = 100;
    G.playedCardCount = 3;
    G.playedCards[ G.playedCardCount ] = G.hand[p][handPos-1];

    int choice1 = 5;
    int choice2 = 3;

    r = checkRemodel( &G, handPos, choice1, choice2 );

    choice1 = 3;
    choice2 = 5;

    r = checkRemodel( &G, handPos, choice1, choice2 );


  }
  printf ("ALL TESTS OK FOR remodel \n\n");
  exit(0);
  return 0;
}
