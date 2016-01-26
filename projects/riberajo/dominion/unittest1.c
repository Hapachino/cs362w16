/* -----------------------------------------------------------------------
 * Test updateCoins function
 * Need to verify:
 *   - if a treasure card adds the proper value
 *   - if the bonus is calculated correctly
 *   - if the game state is changed post update coins
*  Inputs to generate randomly:
*    - gameState
 *      - treasure Cards
*       - coins
 *   - bonus
 *   - players
 * --------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define TEST_FAIL 0
// unit test for updateCoins function
int unitTest(int p, int bonus, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int r = updateCoins(p, post, bonus);

  // general test to see if function reaches the end
  assert(r == 0);
  // check to see if coins before and after are the same
  assert(pre.coins + bonus == post->coins);

#if (TEST_FAIL  == 1)
  // make test fail
  pre.coins = 0;
  assert(pre.coins + bonus == post->coins);
#endif

}


int main() {
    int i, p, n, j,
       randomCardCount, randomCard, bonus;

    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf ("TESTING updateCoins():\n");

    // initialize hand
    // taken from betterTestDrawCard.c
    for (n = 0; n < 10000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
      }
      randomCardCount = floor(Random() * MAX_HAND);
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = randomCardCount;


      // give players random Cards
      for(j = 0; j < randomCardCount; j++) {
        G.hand[p][j] = 0;
        randomCard = floor(Random() * 3);

        if(randomCard == 0) {
          G.hand[p][j] = copper;
        }
        else if (randomCard == 1) {
          G.hand[p][j] = silver;
        }
        else if (randomCard == 2) {
          G.hand[p][j] = gold;
        }
      }

      // add coins for the random Cards
      G.coins = 0;  // reset coins to 0
      for(j = 0; j < randomCardCount; j++) {
        if(G.hand[p][j] == copper) {
          G.coins +=1;
        }
        else if (G.hand[p][j] == silver) {
          G.coins +=2;
        }
        else if (G.hand[p][j] == gold) {
          G.coins +=3;
        }
      }

      // generate random bonus coins
      bonus = floor(Random() * 35);

      /* At this point we have generated random:
         - players, deckCount, discardCount, handCount
         - treasure cards, coins, bonus
      */
      unitTest(p, bonus, &G);
  }

    printf("All tests passed!\n");

    return 0;
}
