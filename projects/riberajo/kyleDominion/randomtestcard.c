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
#include <time.h>

#define TEST_RUNS 100
 // helper function prototypes
 int otherPlayerState(struct gameState *pre, struct gameState *post, int p1, int p2, int vc1, int vc2, int kc1, int kc2);
 int checkCounts(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2);
 int getVictoryCount(struct gameState *post);
 int getKingdomCount(struct gameState *post);
 int printDeck(struct gameState *post, int p, char *n);
 int printHand(struct gameState *post, int p, char *n);
 int printCounts(struct gameState *post, int p);
 int stackDeck(struct gameState *post, int player, int start, int end, int card);
 int stackHand(struct gameState *post, int player, int start, int end, int card);
 int passOrFail(int r);
 int unitTest(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[]);

int main() {
   int p, r, p2,
       seed, numPlayer,
       kingdomCount, victoryCount, randomCardCount, randomCard,
       handPos;

   seed = 1000;
   handPos = 5;

   int k[10] = {adventurer, great_hall, cutpurse, gardens, mine,
                remodel, smithy, village, sea_hag, embargo};

   struct gameState G;
   p = whoseTurn(&G);
   p2 = 1;
   numPlayer = 2;
   int i;
   for (i = 0; i < TEST_RUNS; i++) {
     // clear game state
     memset(&G, 23, sizeof(struct gameState));


     // generate game state inputs randomly
     seed = floor(Random() * 1000);
     handPos = floor(Random() * 5);

     // initialize game
     r = initializeGame(numPlayer, k, seed, &G);


     printf ("TESTING playSmithy():\n\n");

     // generate random hand, deck, discard cards/piles
     randomCard =  floor(Random() * 26);
     randomCardCount = floor(Random() * MAX_HAND);
     p = floor(Random() * 2);
     G.deckCount[p] = floor(Random() * MAX_DECK);
     G.discardCount[p] = floor(Random() * MAX_DECK);
     G.handCount[p] = randomCardCount;


     stackDeck(&G, p, 0, G.deckCount[p], randomCard);

     // stacking hand with silver (card 5)
     stackHand(&G, p, 0, G.handCount[p], randomCard);

     // count all victory cards
     victoryCount = getVictoryCount(&G);
     kingdomCount = getKingdomCount(&G);
   // run test
   
    r = unitTest(handPos, &G, p, victoryCount, kingdomCount, k);

    passOrFail(r);
  } // end loop


return 0;
}


int unitTest(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[]) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int failedTests = 0;
  int p2 = 1; // player 2
  int r, j, victoryCount2, kingdomCount2;

//int smithyCard(struct gameState *state, int currentPlayer, int handPos)

  // run fucntion
  smithyCard(post, p, handPos);

  // count victory cards post function call
  victoryCount2 = getVictoryCount(post);

  // count all kingdom cards post function call
  kingdomCount2 = getKingdomCount(post);

  r =  checkCounts(&pre, post, 0, victoryCount, victoryCount2, kingdomCount, kingdomCount2);

  if (r > 0 ) {
    failedTests++;
  }
  int oldCard;
  oldCard = pre.hand[p][handPos];

// card should be a silver because of our stacked deck/hand
 if(post->hand[p][handPos]-3 != oldCard) {
   printf("Card mismatch - Old card %d, new card %d\n",oldCard, post->hand[p][handPos]);
   failedTests++;
 }

 // check player 2 state
 printf("Checking Player %d: \n", p2+1);
 j =  checkPlayer2(&pre, post, p2, victoryCount, victoryCount2, kingdomCount, kingdomCount2);

 if(j > 0 ) {
   failedTests++;
   // check player 2 counts before and after function call
   otherPlayerState(&pre, post, 0, 1, victoryCount, victoryCount2, kingdomCount, kingdomCount2);
   printf("\nERROR: PLAYER 2 STATE HAS CHANGED \n");

   }
   else {
     printf("\n PLAYER 2 PASS\n");
   }
return failedTests;
}

int otherPlayerState(struct gameState *pre, struct gameState *post, int p1, int p2, int vc1, int vc2, int kc1, int kc2) {
  printf("Player: 2 PRE FUNC COUNTS: \n");
  printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d, Kingdom Count: %d \n",
           pre->handCount[p2], pre->playedCardCount, pre->deckCount[p2], vc1, kc1);

  printf("\nPlayer: 2 POST FUNC COUNTS: \n");
  printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d  Kingdom Count: %d \n\n",
  post->handCount[p2], post->playedCardCount, post->deckCount[p2], vc2);
  return 0;

}

int checkCounts(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2) {
  char *n = "Post";
  char *n2 = "Pre";

  // check hand count
  int failedTests = 0;
  if(pre->handCount[p]+3 != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n");
     printf("Expected: %d   Actual:%d \n",pre->handCount[p]+3,post->handCount[p]);

     failedTests++;
   }

  // check played count
  if(pre->playedCardCount+1 != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");

     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] != post->deckCount[p] + 3) {
    printf("FAIL: deck count mismatch\n");
    printf("Expected: %d   Actual:%d \n",pre->handCount[p], post->handCount[p]+3);

    failedTests++;
  }
  // check discard count
  if(pre->discardCount[p] != post->discardCount[p]) {
    printf("FAIL: discard count mismatch\n");
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
  // if(failedTests > 0) {
  //   printDeck(pre, p, n2);
  //   printDeck(post, p, n);
  //
  //   printHand(pre, p, n2);
  //   printHand(post, p, n);
  //
  //   printCounts(pre, p);
  //   printCounts(post, p);
  // }
  return failedTests;
}


int getVictoryCount(struct gameState *post) {
  return post->supplyCount[estate] + post->supplyCount[province] +
         post->supplyCount[duchy] + post->supplyCount[curse];
}

int getKingdomCount(struct gameState *post) {
  int kingdomCount, i;
  kingdomCount = 0;

  int k[10] = {adventurer, great_hall, cutpurse, gardens, mine,
              remodel, smithy, village, sea_hag, embargo};


  for(i = 0; i < 10; i++) {
    kingdomCount += post->supplyCount[k[i]];
  }

return kingdomCount;
}

int printDeck(struct gameState *post, int p, char *n) {
  int i;
  printf("%s DECK Cards: \n", n);
  for (i = 0; i < post->deckCount[p]; i++) {
      printf("Index   %d      Card:   %d  \n", i, post->deck[p][i]);
  }
}

int printCounts(struct gameState *post, int p) {
     printf(" FUNCTION COUNTS: \n");
     printf("   Hand Count: %d \n", post->handCount[p]);
     printf("   Played Count: %d \n", post->playedCardCount);
     printf("   Deck Count: %d \n", post->deckCount[p]);
     printf("   Discard Count: %d \n\n", post->discardCount[p]);
     return 0;
}


int passOrFail(int r) {
  if( r < 1) {
    printf("TEST: PASS \n");
  }

  else {
    printf("TEST: FAIL\n");
  }
  return 0;
}


int checkPlayer2(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2) {
  char *n = "Post";
  char *n2 = "Pre";

  // check hand count
  int failedTests = 0;
  if(pre->handCount[p] != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n");
     failedTests++;
   }

  // check played count
  if(pre->playedCardCount + 1 != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     printf("Expected %d    Actual %d \n", pre->playedCardCount, post->playedCardCount);

     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] != post->deckCount[p] ) {
    printf("FAIL: deck count mismatch\n");
    failedTests++;
  }

  if(pre->discardCount[p] != post->discardCount[p]) {
    printf("FAIL: discard count mismatch\n");
    printf("Expected %d    Actual %d \n", pre->discardCount[p], post->discardCount[p]);
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

  return failedTests;
}

// stacking deck with card
int stackDeck(struct gameState *post, int player, int start, int end, int card) {
  int count = 0;
  int i;
  for( i = start; i < end; i++) {
    post->deck[player][i] = card;
    count++;
  }
//  printf("Added  %d cards of type %d \n", count, card);
  return 0;
}

// stacking hand with card
int stackHand(struct gameState *post, int player, int start, int end, int card) {
  int count = 0;
  int i;
  for( i = start; i < end; i++) {
    post->hand[player][i] = card;
    count++;
  }
  //printf("Added  %d cards of type %d \n", count, card);
  return 0;
}

int printHand(struct gameState *post, int p, char *n) {
  int i;
  printf("\n%s function call HAND Cards: \n", n);
  for (i = 0; i < post->handCount[p]; i++) {
      printf("Index   %d      Card:   %d  \n", i, post->hand[p][i]);
  }
  return 0;
}
