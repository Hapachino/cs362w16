/* Filename:  smithyTest.c
   Author:    Sam Ford
   Description:
     This is a simple test file to demonstrate the issue detailed in my related
     bug report for Assignment 5.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"

#define P1 0
#define P2 1

void testSmithy() {
  int handPos = 0;
  int result = 0;
  struct gameState pre = {0};
  struct gameState post = {0};

  /* Test Smithy, changing Smithy's handPos for each test */
  for (handPos = 0; handPos < 5; handPos++) {
    /* Reset the gameState structs on each iteration */
    bzero(&pre, sizeof(struct gameState));
    bzero(&post, sizeof(struct gameState));

    /* Set up state for two players */
    pre.whoseTurn = P1;
    pre.numPlayers = 2;
    pre.hand[P1][0] = baron;
    pre.hand[P1][1] = mine;
    pre.hand[P1][2] = duchy;
    pre.hand[P1][3] = copper;
    pre.hand[P1][4] = adventurer;
    pre.hand[P1][handPos] = smithy;
    pre.handCount[P1] = 5;
    pre.deck[P1][0] = estate;
    pre.deck[P1][1] = silver;
    pre.deck[P1][2] = mine;
    pre.deck[P1][3] = gardens;
    pre.deck[P1][4] = copper;
    pre.deckCount[P1] = 5;
    pre.discardCount[P1] = 0;
    memcpy(&post, &pre, sizeof(struct gameState));

    /* Play the card */
    result = smithyEffect(handPos, P1, &post);
    printf(
      "----- Test: handPos = %d, handCount = %d, deckCount = %d\n",
      handPos, pre.handCount[P1], pre.deckCount[P1]
    );

    /* Smithy should add 3 cards to player's hand, minus the played card */
    printf(
      "handCount: expected = %d, observed = %d\n\n",
      (pre.handCount[P1] + 3 - 1), post.handCount[P1]
    );
  }
}

int main() {
  testSmithy();
  return 0;
}
