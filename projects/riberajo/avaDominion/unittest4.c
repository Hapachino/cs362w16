/* -----------------------------------------------------------------------
 * Test gainCard function
 * Need to verify:
 *   - if supply pile is 0 or -1 then don't gain a cards
 *   - if the flag is set to:
 *      0 - add to discard
 *      1 - add to deck
 *      2 - add to hand
 *   - if the supply count's card decrements after adding to a pile
 *
 * --------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"


int unitTest(int supplyPos, struct gameState *post, int toFlag, int p) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int r =  gainCard(supplyPos, post, toFlag, p);

  if(pre.supplyCount[supplyPos] < 1) {

    assert(r == -1);
    printf("Should return -1: \n returned: %d\n", r);
    return 0;
  }

  if(toFlag == 1) {
    assert(pre.deckCount[p]+1 == post->deckCount[p]);
    printf("DECK (F1) gained card: %d\n", supplyPos);
  }
  else if(toFlag == 2) {
    assert(pre.handCount[p]+1 == post->handCount[p]);
    printf("HAND (F2) gained card: %d\n", supplyPos);
  }
  else {
    assert(pre.discardCount[p]+1 == post->discardCount[p]);
    printf("DISCARD (F0) gained card: %d\n", supplyPos);
  }

  assert(pre.supplyCount[supplyPos] -1 == post->supplyCount[supplyPos]);
  return 0;
}


int main() {
    int i, n, p,
       randomCardCount, randomSupplyPos, randomFlag;

    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf ("TESTING gainCard():\n");

    // initialize hand
    // taken from betterTestDrawCard.c
    for (n = 0; n < 10000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
      }
      // create a random but sane game state
      randomCardCount = floor(Random() * MAX_HAND);
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = randomCardCount;
      randomSupplyPos = floor(Random() * 27);
      randomFlag = floor(Random() * 3);

      // we now have semi random inputs for gain card
      printf("Testing card: %d   flag: %d   player:  %d \n", randomSupplyPos, randomFlag, p);
      unitTest(randomSupplyPos, &G, randomFlag, p);


  }

    printf("All tests passed!\n");

    return 0;
}
