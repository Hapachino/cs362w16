/* Filename:  councilRoomTest.c
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
#define HANDPOS 1

void testCouncilRoom() {
  int result = 0;
  struct gameState pre = {0};
  struct gameState post = {0};

  /* Set up state for the players */
  pre.whoseTurn = P1;
  pre.numPlayers = 2;
  pre.numBuys = 1;
  pre.deck[P1][0] = estate;
  pre.deck[P1][1] = silver;
  pre.deck[P1][2] = mine;
  pre.deck[P1][3] = gardens;
  pre.deck[P1][4] = copper;
  pre.deckCount[P1] = 5;
  pre.discardCount[P1] = 0;
  pre.hand[P1][0] = baron;
  pre.hand[P1][1] = council_room;
  pre.handCount[P1] = 2;
  pre.deck[P2][0] = treasure_map;
  pre.deck[P2][1] = salvager;
  pre.deckCount[P2] = 2;
  memcpy(&post, &pre, sizeof(struct gameState));

  /* Play the card */
  result = playCouncil_Room(&post, HANDPOS, pre.whoseTurn);
  printf(
    "----- Test: handCount = %d, deckCount = %d\n",
    pre.handCount[P1], pre.deckCount[P1]
  );

  /* Council Room should add 4 cards to player's hand, minus played card */
  printf(
    "handCount: expected = %d, observed = %d\n",
    (pre.handCount[P1] + 4 - 1), post.handCount[P1]
  );
}

int main() {
  testCouncilRoom();
  return 0;
}
