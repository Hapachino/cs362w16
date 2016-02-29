/* -----------------------------------------------------------------------
 * Test playAdventurer function
 * Need to verify:
 *   - if it reveals cards - testcase1
        - check his own deck to verify cards  were taken from there - testcase1
     - The function should stop after drawing two treasure cards - - testcase1
 *      - Check the pre and post function hand counts - - testcase1

 *   -  Once we have the treasure cards, the temp deck should be discarded
         - Compare pre and post deck hand
 *   - if deck is empty the discard pile should be shuffled and become the new
 *     deck
                  - compare pre shuffled deck with post shuffled deck

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
 #include <stdlib.h>

 // helper function prototypes
 int otherPlayerState(struct gameState *pre, struct gameState *post, int p1, int p2, int vc1, int vc2, int kc1, int kc2);
 int checkCounts(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2);
 int checkCounts2(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2);
 int getVictoryCount(struct gameState *post);
 int getKingdomCount(struct gameState *post);
 int printDeck(struct gameState *post, int p, char *n);
 int printHand(struct gameState *post, int p, char *n);
 int printCounts(struct gameState *post, int p);
 int stackDeck(struct gameState *post, int player, int start, int end, int card);
 int stackHand(struct gameState *post, int player, int start, int end, int card);
 int passOrFail(int r);
 int unitTest1(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[], int randomCard, int randomCard2);
 int unitTest2(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[]);




int main() {
   // initialize variables
   int p, p2, r,
       seed, numPlayer,
       kingdomCount, victoryCount, randomCard,randomCard2, randomCardCount,
       handPos;

   // set variables needed to initialize game state
   numPlayer = 2;
//   handPos = 5;
   p = 0;   // player 1
   p2 = 1;  // player 2

   int k[10] = {adventurer, great_hall, cutpurse, gardens, mine,
                remodel, smithy, village, sea_hag, embargo};

   struct gameState G, G2;
   int i;
   srand(time(NULL));

   for(i = 0; i < 1000; i ++) {
     seed = (rand() % 1000) + 1;
     handPos = (rand() % 5) + 1;
     randomCard = rand() % (25) + 4;
     randomCard2 = (rand() % 26) + 3;




    //   clear game state and initialize game
    printf("Seed: %d, numPlayer: %d, handPos %d, r1: %d, r2: %d\n", seed, numPlayer, handPos, randomCard, randomCard2);
     memset(&G, 23, sizeof(struct gameState));
     r = initializeGame(numPlayer, k, seed, &G);

     // used for test case 2
     memset(&G2, 23, sizeof(struct gameState));
     r = initializeGame(numPlayer, k, seed, &G2);

     randomCardCount = floor(Random() * MAX_HAND);
     p = floor(Random() * 2);
     G.deckCount[p] = floor(Random() * MAX_DECK);
     G.discardCount[p] = floor(Random() * MAX_DECK);
     G.handCount[p] = randomCardCount;

     // begin testing
     printf ("TESTING playAdventurer():\n");

     /* ---------- START TEST CASE 1  ---------------*/
     printf("---- STACKING DECKS ----\n");

     // stack the deck with random cards
     stackDeck(&G, p, 0, G.deckCount[p]-2, randomCard);

     stackDeck(&G, p, G.deckCount[p]-2, G.deckCount[p] , randomCard2);

     stackHand(&G, p, 0, G.handCount[p], randomCard);
     /* ---------- END TEST CASE 1  ---------------*/

     /* ---------- START TEST CASE 2  ---------------
      this case tests the functions ability to get cards from the discard pile
      because there is only 1 treasure card in the deck.
     */

     // stack the deck with 4 estates and 1 gold
     // add estates (1)
     stackDeck(&G2, p, 0, G2.deckCount[p]-1, estate);
     // add gold (6)
     stackDeck(&G2, p, G2.deckCount[p]-1, G2.deckCount[p] ,gold);
     G2.discardCount[p] = 4;
     G2.discard[p][0] = duchy;
     G2.discard[p][1] = copper;
     G2.discard[p][2] = duchy;
     G2.discard[p][3] = duchy;

     /* ---------- END TEST CASE 2  ---------------*/

     // Get some pre counts of cards to verify after function is called
     printf("---- DONE ----\n");
     char *pre = "Pre"; // name to differentiate pre and post calls


     // get kingdom and victory counts
     kingdomCount = getKingdomCount(&G);
     victoryCount = getVictoryCount(&G);

     int test2_kingdomCnt, test2_victoryCount;
     test2_kingdomCnt = getKingdomCount(&G2);
     test2_victoryCount = getVictoryCount(&G2);

    // run test
    int test1, test2;
    printf("---- TEST 1 ----\n");

    test1 = unitTest1(handPos, &G, p, victoryCount, kingdomCount, k, randomCard, randomCard2);
    passOrFail(test1);

    // printf("---- TEST 2 ----\n");
    // test2 = unitTest2(handPos, &G2, p, test2_victoryCount, test2_kingdomCnt, k);
    // passOrFail(test2);
  } // end loop


return 0;
}

/* unit test case 1 - deck has all treasure cards (player 0)
   - discard should be 0
   - hand should contain + 2 gold cards
   - deck should be -2 cards
*/
int unitTest1(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[], int randomCard, int randomCard2) {
  // make copy of game state before function is called
  struct gameState pre, pre2;
  memcpy(&pre, post, sizeof(struct gameState));

  // variables for post test
  int failedTests = 0;
  int j, victoryCount2, kingdomCount2;
//int adventurerCard(struct gameState *state, int currentPlayer)

  // run fucntion
  adventurerCard(post, p);
  victoryCount2 = getVictoryCount(post);
  kingdomCount2 = getKingdomCount(post);


   int r =  checkCounts(&pre, post, 0, victoryCount, victoryCount2, kingdomCount, kingdomCount2);
   if( r > 0) {
     failedTests++;
   }
  //  // last two cards added in hand should be gold
  //  int lastCard = post->handCount[p]-2;
  //  if(post->hand[p][lastCard] != randomCard2) {
  //    printf ("FAIL: Expected:%d in hand pos: %d\n", randomCard2, handPos);
  //    failedTests++;
  //  }

   j =  checkPlayer2(&pre, post, 1, victoryCount, victoryCount2, kingdomCount, kingdomCount2);

   if(j > 0 ) {
     failedTests++;
     // check player 2 counts before and after function call
     otherPlayerState(&pre, post, 0, 1, victoryCount, victoryCount2, kingdomCount, kingdomCount2);
   }

return failedTests;
}

/* unit test case 2 - deck has 1 treasure card (player 0)
   - discard should be 4
   - hand should contain + 1 gold card and + 1 copper
   - deck should be -2 cards
*/
int unitTest2(int handPos, struct gameState *post, int p, int victoryCount, int kingdomCount, int k[]) {
  // make copy of game state before function is called
  struct gameState pre, pre2;
  memcpy(&pre, post, sizeof(struct gameState));

  // variables for post test
  int failedTests = 0;
  int victoryCount2, kingdomCount2;

  // run fucntion
  //adventurerCard
  adventurerCard(post, p);
  victoryCount2 = getVictoryCount(post);
  kingdomCount2 = getKingdomCount(post);


   int r =  checkCounts2(&pre, post, 0, victoryCount, victoryCount2, kingdomCount, kingdomCount2);
   if(r > 0 ) {
     failedTests++;
   }

   // last two cards added in hand should be copper and gold
   if(post->hand[p][6] != copper && post->hand[p][5] != gold) {
     printf ("FAIL: Correct cards not added \n");
     printf ("Expected: %d & %d   Actual: %d and %d \n", gold, copper, post->hand[p][6], post->hand[p][5]);
     failedTests++;
   }

    int j =  checkPlayer2(&pre, post, 1, victoryCount, victoryCount2, kingdomCount, kingdomCount2);

    if(j > 0 ) {
      failedTests++;
      // check player 2 counts before and after function call
      otherPlayerState(&pre, post, 0, 1, victoryCount, victoryCount2, kingdomCount, kingdomCount2);
      }


return failedTests;
}

// helper function definitions //


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
  if(pre->playedCardCount != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] != post->deckCount[p] ) {
    printf("FAIL: deck count mismatch\n");
    failedTests++;
  }

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
  if(failedTests > 0) {
    printDeck(pre, p, n2);
    printCounts(pre, p);
    printDeck(post, p, n);
    printCounts(post, p);
  }
  return failedTests;
}

int otherPlayerState(struct gameState *pre, struct gameState *post, int p1, int p2, int vc1, int vc2, int kc1, int kc2) {
  printf("Player: 2 PRE FUNC COUNTS: \n");
  printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d, Kingdom Count: %d \n",
           pre->handCount[p2], pre->playedCardCount, pre->deckCount[p2], vc1, kc1);

  printf("\nPlayer: 2 POST FUNC COUNTS: \n");
  printf("Hand Count: %d Played Count: %d  Deck Count: %d Victory Count: %d  Kingdom Count: %d \n\n",
  post->handCount[p2], post->playedCardCount, post->deckCount[p2], vc2, kc2);
  return 0;

}


int checkCounts(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2) {
  char *n = "Post";
  char *n2 = "Pre";

  // check hand count
  int failedTests = 0;
  if(pre->handCount[p] + 2 != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n");
     printf("Expected: %d   Actual:%d \n",pre->handCount[p]+2,post->handCount[p]);

     failedTests++;
   }

  // check played count
  if(pre->playedCardCount != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] - 2 != post->deckCount[p] ) {
    printf("FAIL: deck count mismatch\n");
    printf("Expected: %d   Actual:%d \n",pre->deckCount[p]-2,post->deckCount[p]);

    failedTests++;
  }

  if(pre->discardCount[p] != post->discardCount[p]) {
    printf("FAIL: discard count mismatch\n");
    printf("Expected: %d   Actual:%d \n",pre->handCount[p], post->handCount[p]+3);

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
  //   printCounts(pre, p);
  //   printDeck(post, p, n);
  //   printCounts(post, p);
  // }
  return failedTests;
}

int checkCounts2(struct gameState *pre, struct gameState *post, int p, int victoryCount, int victoryCount2, int kingdomCount, int kingdomCount2) {
  char *n = "Post";
  char *n2 = "Pre";

  // check hand count
  int failedTests = 0;
  if(pre->handCount[p] + 2 != post->handCount[p]) {
     printf("FAIL: Handcount mismatch\n");
     failedTests++;
   }

  // check played count
  if(pre->playedCardCount != post->playedCardCount) {
     printf("FAIL: Played card amount mismatch\n");
     failedTests++;
  }

  // check deck count
  if(pre->deckCount[p] - 2 != post->deckCount[p] ) {
    printf("FAIL: deck count mismatch\n");
    failedTests++;
  }

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
  if(failedTests > 0) {
    printDeck(pre, p, n2);
    printDeck(post, p, n);

    printCounts(pre, p);
    printCounts(post, p);
  }
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
  printf("\n%s function call DECK Cards: \n", n);
  for (i = 0; i < post->deckCount[p]; i++) {
      printf("Index   %d      Card:   %d  \n", i, post->deck[p][i]);
  }
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

int printCounts(struct gameState *post, int p) {
     printf("\n FUNCTION COUNTS: \n");
     printf("   Hand Count:     %d \n", post->handCount[p]);
     printf("   Played Count:   %d \n", post->playedCardCount);
     printf("   Deck Count:     %d \n", post->deckCount[p]);
     printf("   Discard Count:  %d \n\n", post->discardCount[p]);
     return 0;
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
  printf("Added  %d cards of type %d \n", count, card);
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
