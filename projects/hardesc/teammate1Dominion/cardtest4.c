/*
 *
 * unittest4.c
 *
 *
 *
 * Include the following lines in your makefile:
 *
 * 
 *
 *
 *
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include <stdlib.h>

int main() {

   struct gameState G, testG;
   int numPlayers = 4;
   int player = 0;
   int handpos = 2;
   int bonus = 0;
   int choice1 = 0, choice2 = 0, choice3 = 0;
   int seed = 1000;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

   initializeGame(numPlayers, k, seed, &G);

  
   printf("\n\n\n-------------------------Testing council_room-------------------\n\n");
   //TEST 1-------------------------------------------

   memcpy(&testG, &G, sizeof(struct gameState));
  
   cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

   printf("\nTEST 1: DRAW 4 CARDS - player has 4 new cards - 1 discard\n");

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] + 3);
   assert(testG.handCount[player] == G.handCount[player] + 3);

   printf("\nTEST 2: CARDS DRAWN FROM DECK - player's deck has 4 less cards \n");

   printf("\tdeckCount = %d, expected = %d", testG.deckCount[player], G.deckCount[player] - 4);
   assert(testG.deckCount[player] == G.deckCount[player] - 4);

   printf("\nTEST 3: COUNCIL_ROOM DISCARDED - player's played cards pile has 1 council_room card\n");

   printf("\tplayedCardCount = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
   assert(testG.playedCardCount == G.playedCardCount + 1);

   printf("\nTEST 4: BUYS INCREMENTED - additional buy \n");

   printf("\tnumBuys = %d, expected = %d", testG.numBuys, G.numBuys + 1);
   assert(testG.numBuys == G.numBuys + 1);


   printf("\nTEST 5: +1 CARD TO ALL - each additional player gets an additional card \n");

  printf("\tplayer #2 handCount =  %d, expected = %d", testG.handCount[1], G.handCount[1] + 1);
  assert(testG.handCount[1] == G.handCount[1] + 1);

  printf("\tplayer #3 handCount =  %d, expected = %d", testG.handCount[2], G.handCount[2] + 1);
  assert(testG.handCount[2] == G.handCount[2] + 1);

  printf("\tplayer #4 handCount =  %d, expected = %d", testG.handCount[3], G.handCount[3] + 1);
  assert(testG.handCount[3] == G.handCount[3] + 1);

   printf("\n\n----------------------council_room test complete------------------------\n\n\n");

   return 0;
}
