/* -----------------------------------------------------------------------
 * Test council room card
 * Need to verify:
 *   - if player gains 4 cards
 *   - if player gains + 1 buy
 *   - if the player2 draws a card
 *   - state change should occur for other players.
 *   - No state change should occur to the victory card piles and kingdom card piles
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
 int unitTest(int handPos, struct gameState *post, int p);

int main() {
   int i, p, p2, r,
       seed, numPlayer,
       kingdomCount, victoryCount,
       handPos;

   seed = 1000;
   numPlayer = 2;
   handPos = 4;

   int k[10] = {adventurer, great_hall, cutpurse, gardens, mine,
                remodel, smithy, village, sea_hag, embargo};

   struct gameState G;
   p = whoseTurn(&G);
   p2 = 1;

   // clear game state and initialize game
   memset(&G, 23, sizeof(struct gameState));
   r = initializeGame(numPlayer, k, seed, &G);


   printf ("TESTING Council Room Card:\n\n");

   // stacking deck with copper (card 4)
   stackDeck(&G, p, 0, G.deckCount[p], copper);

   // stacking hand with silver (card 5)
   stackHand(&G, p, 0, G.handCount[p], silver);


   G.discardCount[p] = 2;
   G.discard[p][0] = copper;
   G.discard[p][1] = silver;
  // run test
  r = unitTest(handPos, &G, p);

  passOrFail(r);



return 0;
}

/* Test 1
     - Player gains 4 cards (net gain of 3)
     - Player gains + 1 buy
     - Player 2 draws card
     - Verify player 2 state has changed
     - No state change should occur to the victory card piles and kingdom card piles
*/

int unitTest(int handPos, struct gameState *post, int p) {
  struct gameState pre;
  memcpy(&pre, post, sizeof(struct gameState));
  int failedTests = 0;
  int p2 = 1; // player 2
  int r, j, victoryCount, victoryCount2, kingdomCount, kingdomCount2;

  // run fucntion
  // int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

  cardEffect(council_room, 0, 0, 0, post, handPos, 0);

  // count victory cards post function call
  victoryCount = getVictoryCount(&pre);
  victoryCount2 = getVictoryCount(post);

  // count all kingdom cards post function call
  kingdomCount2 = getKingdomCount(post);
  kingdomCount  = getKingdomCount(&pre);

  r =  checkCounts(&pre, post, 0, victoryCount, victoryCount2, kingdomCount, kingdomCount2);

  if (r > 0 ) {
    failedTests++;
  }
// card should be a silver because of our stacked deck/hand
 if(post->hand[p][6] != copper) {
   printf("FAIL: added card isn't copper. Actual: %d\n", post->hand[p][6]);
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
  int failedTests = 0;

  // check number of actions
  if(pre->numActions != post->numActions) {
    printf("FAIL: action count mismatch\n");
    failedTests++;
  }

  // check hand count
  // we gain 4 card then discard a card so net gain is 3
  if(pre->handCount[p] + 3 != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n", pre->handCount[p] + 4, post->handCount[p]);
     printf("Expected: %d,   Actual:  %d \n");
     failedTests++;
   }

  // check played count
  if(pre->playedCardCount + 1 != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] - 4 != post->deckCount[p]) {
    printf("FAIL: deck count mismatch\n");
    failedTests++;
  }
  // check discard count
  if(pre->discardCount[p] != post->discardCount[p]) {
    printf("FAIL: discard count mismatch\n");
    printf("Expected: %d   Actual:  %d\n", pre->discardCount[p]+1,post->discardCount[p] );

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
  return 0;

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
  if(pre->handCount[p] + 1 != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n");
     failedTests++;
   }

  // check played count
  // + 1 because playedcount is for both players
  if(pre->playedCardCount+1 != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     printf("Expected %d    Actual %d \n", pre->playedCardCount, post->playedCardCount);

     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] - 1 != post->deckCount[p] ) {
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
  if(failedTests == 0) {
    printf("PLAYER 2 PASS\n");
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
