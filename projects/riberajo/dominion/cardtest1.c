/* -----------------------------------------------------------------------
 * Test playSmithy function
 * Need to verify:
 *   - if player actually gets +3 cards
        - check his own deck to verify cards  were taken from there
 *   - if the the card discards from the hand
 *   - No state change should occur for other players.
 *   - No state change should occur to the victory card piles and kingdom card piles

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

int unitTest(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[]) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));

  int p2 = 0; // player 2
  int failedTests = 0; // holds if any test fail

  int r, i, victoryCount2, kingdomCount2;
  // run fucntion
  playSmithy(handPos, post);

  // count victory cards post function call
  victoryCount2 = post->supplyCount[estate] + post->supplyCount[province] +
                  post->supplyCount[duchy] + post->supplyCount[curse];

  // count all kingdom cards post function call
  for(i = 0; i < 9; i++) {
    kingdomCount2 += post->supplyCount[k[i]];
  }

  printf("POST FUNCTION COUNTS: \n");
   printf("   Hand Count: %d \n", post->handCount[p]);
   printf("   Played Count: %d \n", post->playedCardCount);
   printf("   Deck Count: %d \n", post->deckCount[p]);
   printf("   Discard Count: %d \n\n", post->discardCount[p]);

    // printf("DECK Cards After Stacking\n");
    // for (i = 0; i < post->handCount[p]; i++) {
    //     printf("Index   %d      Card:   %d  \n", i, post->hand[p][i]);
    // }

   printf("Player: 2 PRE FUNC COUNTS: \n");
   printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d, Kingdom Count: %d \n",
            pre.handCount[p2], pre.playedCardCount, pre.deckCount[p], victoryCount, kingdomCount);

   printf("\nPlayer: 2 POST FUNC COUNTS: \n");
   printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d  Kingdom Count: %d \n\n",
   post->handCount[p2], post->playedCardCount, post->deckCount[p2], victoryCount2);

 // check hand count
 if(pre.handCount[p]+2 != post->handCount[p]) {
    printf("FAIL: Handcount mismatch\n");
    failedTests++;
  }

// check played count
 if(pre.playedCardCount+1 != post->playedCardCount) {
    printf("FAIL: Played card amount mismatch\n");
    failedTests++;
 }

 // check deck count
 if(pre.deckCount[p] != post->deckCount[p] + 3) {
   printf("FAIL: deck count mismatch\n");
   failedTests++;
 }

 // check victory count
 if(victoryCount != victoryCount2) {
   printf("FAIL: victory count mismatch\n");
   failedTests++;
 }

 // check kingdom count
 if(kingdomCount != kingdomCount2) {
   printf("FAIL: kingdom count mismatch\n");
   failedTests++;
 }

// card should be a silver because of our stacked deck/hand
 if(pre.hand[p][0] != 5) {
   printf("FAIL: added card isn't silver\n");
   failedTests++;
 }



  return failedTests;
}

int main() {
   int i, p, p2, r,
       seed, numPlayer,
       kingdomCount, victoryCount,
       handPos;

   seed = 1000;
   numPlayer = 2;
   handPos = 5;

   int k[10] = {adventurer, great_hall, cutpurse, gardens, mine,
                remodel, smithy, village, sea_hag, embargo};

   struct gameState G;
   p = whoseTurn(&G);
   p2 = 1;

   // clear game state and initialize game
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(numPlayer, k, seed, &G);


   printf ("TESTING playSmithy():\n");

   // stacking deck with copper (card 4)
   for( i = 0; i < G.deckCount[p]; i++) {
     G.deck[p][i] = copper;
   }

   // stacking hand with silver (card 5)
   for( i = 0; i < G.handCount[p]; i++) {
     G.hand[p][i] = silver;
   }

   // count all the kindom cards
   for(i = 0; i < 9; i++) {
     kingdomCount += G.supplyCount[k[i]];
   }

   // count all victory cards
   victoryCount = G.supplyCount[estate] + G.supplyCount[province]
                + G.supplyCount[duchy] + G.supplyCount[curse];

   printf("Player: %d PRE FUNCTION COUNTS: \n", p);
   printf("   Hand Count: %d \n", G.handCount[p]);
   printf("   Played Count: %d \n", G.playedCardCount);
   printf("   Deck Count: %d \n", G.deckCount[p]);
   printf("   Discard Count: %d \n", G.discardCount[p]);
   printf("   Victory Count %d  \n\n", victoryCount);

 // run test
  r = unitTest(handPos, &G, p, victoryCount, kingdomCount, k);
  if( r < 1) {
    printf("TEST: PASS \n");
  }

  else {
    printf("TEST: FAIL\n");
  }



return 0;
}
