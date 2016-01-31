/* -----------------------------------------------------------------------
 * Test scoreFor() function
 * Need to verify:
 *   - if score is calculated when player has curse, estate, duchy, province,
        great hall, or gardens cards
 *
*  Inputs to generate randomly:
*    - gameState
 *   - players
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

#define NOISY_TEST 1

int unitTest(int p, int score, struct gameState *post) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  // get supply of each card before and after function call
#if(NOISY_TEST == 1)

  printf("PRE-SCORE: %d \n", score);

#endif

  int r = scoreFor(p, post);

#if(NOISY_TEST == 1)
  printf("POST-SCORE: %d \n", r);
  if(r != score ) {
    printf("FAIL: Looks like we found an error in the calcuation of score\n ");
  }

#endif


  // general test to see if supply counts are the same pre/post function call
  assert(pre.supplyCount[curse] == post->supplyCount[curse]);
  assert(pre.supplyCount[estate] == post->supplyCount[estate]);
  assert(pre.supplyCount[duchy] == post->supplyCount[duchy]);
  assert(pre.supplyCount[province] == post->supplyCount[province]);
  assert(pre.supplyCount[great_hall] == post->supplyCount[great_hall]);
  assert(pre.supplyCount[gardens] == post->supplyCount[gardens]);

#if(NOISY_TEST == 1)
  printf("SUCCESS ->> pre supply counts  EQUAL post function call\n");
#endif
  // test to see if the handcounts are the same after calling function
  assert(pre.handCount[p] == post->handCount[p]);
  assert(pre.deckCount[p] == post->deckCount[p]);
  assert(pre.discardCount[p] == post->discardCount[p]);
  #if(NOISY_TEST == 1)
    printf("SUCCESS ->> pre hand,deck,discard counts  EQUAL post function call\n");
  #endif
  /*error is in either gardens card or fullDeckCount() */
  assert(r == score);
}

int main() {
    int i, n, j, p,
       randomCard, randomCardCount, randomDiscardCount, randomDeckCount;

    struct gameState G;

    SelectStream(2);
    PutSeed(3);

    printf ("TESTING isGameOver():\n");

    // initialize hand
    // taken from betterTestDrawCard.c
    for (n = 0; n < 2000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
        ((char*)&G)[i] = floor(Random() * 256);
      }
      // create a random but sane game state
      randomCardCount = floor(Random() * MAX_HAND);
      randomDiscardCount = floor(Random() * MAX_DECK);
      randomDeckCount = floor(Random() * MAX_DECK);
      p = floor(Random() * 2);
      G.deckCount[p] = randomDeckCount;
      G.discardCount[p] = randomDiscardCount;
      G.handCount[p] = randomCardCount;

      // For cards in hand
      // give players random scoring cards
      for (j = 0; j < randomCardCount; j++) {
        G.hand[p][j] = 0;
        randomCard = floor(Random() * 6);

           if (randomCard == 0) {
            G.hand[p][j] = curse;
          }

          else if (randomCard == 1) {
            G.hand[p][j] = estate;
          }

          else if (randomCard == 2) {
            G.hand[p][j] = duchy;
          }

          else if (randomCard == 3) {
            G.hand[p][j] = province;
          }

          else if (randomCard == 4) {
            G.hand[p][j] = great_hall;
          }

          else if(randomCard == 5) {
             G.hand[p][j] = gardens;
           }
      }

      // calculate player's score from hand cards
      int score;
      score = 0;
      for(j = 0; j < randomCardCount; j++) {
        if (G.hand[p][j] == curse) {
         score -= 1;
       }

       else if (G.hand[p][j] == estate) {
         score += 1;
       }

       else if (G.hand[p][j] == duchy) {
         score += 3;
       }

       else if (G.hand[p][j] == province) {
         score += 6;
       }

       else if (G.hand[p][j] == great_hall) {
         score += 1;
       }

       else if(G.hand[p][j] == gardens) {
         score = score + (fullDeckCount(p, 0, &G) / 10);
        }
      }
//printf("After hand Score is now %d\n", score);
      // For cards in hand
      // give players random discard cards
      for (j = 0; j < randomDiscardCount; j++) {
        G.discard[p][j] = 0;
        randomCard = floor(Random() * 6);

           if (randomCard == 0) {
            G.discard[p][j] = curse;
          }

          else if (randomCard == 1) {
            G.discard[p][j] = estate;
          }

          else if (randomCard == 2) {
            G.discard[p][j] = duchy;
          }

          else if (randomCard == 3) {
            G.discard[p][j] = province;
          }

          else if (randomCard == 4) {
            G.discard[p][j] = great_hall;
          }

          else if(randomCard == 5) {
             G.discard[p][j] = gardens;
           }
      }

      // calculate player's score from discard cards

      for(j = 0; j < randomDiscardCount; j++) {
        if (G.discard[p][j] == curse) {
         score -= 1;
       }

       else if (G.discard[p][j] == estate) {
         score += 1;
       }

       else if (G.discard[p][j] == duchy) {
         score += 3;
       }

       else if (G.discard[p][j] == province) {
         score += 6;
       }

       else if (G.discard[p][j] == great_hall) {
         score += 1;
       }

       else if(G.discard[p][j] == gardens) {
          score = score + (fullDeckCount(p, 0, &G) / 10);

        }
      }

//      printf("After discard Score is now %d\n", score);

      for (j = 0; j < randomDeckCount; j++) {
        G.deck[p][j] = 0;
        randomCard = floor(Random() * 6);

           if (randomCard == 0) {
            G.deck[p][j] = curse;
          }

          else if (randomCard == 1) {
            G.deck[p][j] = estate;
          }

          else if (randomCard == 2) {
            G.deck[p][j] = duchy;
          }

          else if (randomCard == 3) {
            G.deck[p][j] = province;
          }

          else if (randomCard == 4) {
            G.deck[p][j] = great_hall;
          }

          else if(randomCard == 5) {
             G.deck[p][j] = gardens;
           }
      }

      // calculate player's score from discard cards

      for(j = 0; j < randomDeckCount; j++) {
        if (G.deck[p][j] == curse) {
         score -= 1;
       }

       else if (G.deck[p][j] == estate) {
         score += 1;
       }

       else if (G.deck[p][j] == duchy) {
         score += 3;
       }

       else if (G.deck[p][j] == province) {
         score += 6;
       }

       else if (G.deck[p][j] == great_hall) {
         score += 1;
       }

       else if(G.deck[p][j] == gardens) {
          score = score + (fullDeckCount(p, 0, &G) / 10);
        }
      }
  //    printf("After deck Score is now %d\n", score);



      unitTest(p, score, &G);


  }

    printf("All tests passed!\n");

    return 0;
}
