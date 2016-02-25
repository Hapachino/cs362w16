/* -----------------------------------------------------------------------
 * Test isGameOver function
 * Need to verify:
 *   - if game ends when all province cards are empty
 *   - or when the 3 supply piles are empty
*  Inputs to generate randomly:
*    - gameState
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


int main() {
    int i, n, p, r,
       randomCardCount;

    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf ("TESTING isGameOver():\n");

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

      // test if game ends with 0 provices
      G.supplyCount[province] = 0;
      r = isGameOver(&G);
      assert(r == 1);

      // test if game ends with > 0 provinces
      G.supplyCount[province] = 1;
      r = isGameOver(&G);
      assert (r == 0);

      // test if game ends with 1 empty pile
      G.supplyCount[feast] = 0;
      r =  isGameOver(&G);
      assert(r == 0);
      
      // test if game ends with 2 empty pile
      G.supplyCount[smithy] = 0;
      r = isGameOver(&G);
      assert(r == 0);

      // test if game ends with 3 empty pile
      G.supplyCount[adventurer] = 0;
      r = isGameOver(&G);
      assert(r == 1);


  }

    printf("All tests passed!\n");

    return 0;
}
