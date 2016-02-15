/*
 *
 * cardtest2.c
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
   int numPlayers = 2;
   int player = 0;
   int handpos = 2;//position of village card in hand
   int bonus = 0;
   int choice1 = 0, choice2 = 0, choice3 = 0;
   int seed = 1000;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

   initializeGame(numPlayers, k, seed, &G);
  
   printf("\n\n\n-------------------------Testing village-------------------\n\n");
   //TEST 1-------------------------------------------

   G.hand[player][0] = estate;
   G.hand[player][1] = duchy;
   G.hand[player][2] = village;
   G.hand[player][3] = province;
   G.hand[player][4] = curse;
   G.handCount[player] = 5;

   G.deck[player][0] = copper; 
   G.deck[player][1] = silver; 
   G.deck[player][2] = gold; 
   G.deck[player][3] = mine; 
   G.deck[player][4] = smithy; 
   G.deck[player][5] = -1; 
   G.deck[player][6] = -1; 
   G.deck[player][7] = -1; 
   G.deckCount[player] = 5;

   memcpy(&testG, &G, sizeof(struct gameState));
  
   cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);

   printf("\nTEST 1: DRAW 1 CARD - player has 1 new cards - 1 discard\n");

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player]);
   assert(testG.handCount[player] == G.handCount[player]);

   printf("\nTEST 2: CARD IS DRAWN FROM DECK - new card is same one from deck\n");


  printf("\tdeckCount = %d, expected = %d", testG.deckCount[player], G.deckCount[player] - 1);
  assert(testG.deckCount[player] == G.deckCount[player] - 1);

  printf("\thand card #1 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\thand card #2 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\thand card #3 = %d, expected = %d", testG.hand[player][2], G.deck[player][4]);
  assert(testG.hand[player][2] == G.deck[player][4]);

  printf("\thand card #4 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

  printf("\thand card #5 = %d, expected = %d", testG.hand[player][4], G.hand[player][4]);
  assert(testG.hand[player][4] == G.hand[player][4]);

  printf("\thand card #6 = %d, expected = %d", testG.hand[player][5], -1);
  assert(testG.hand[player][5] == -1);

   printf("\nTEST 3: ACTIONS ADDED - village earns +2 actions\n");

   printf("\tnumActions = %d, expected = %d", testG.numActions, G.numActions + 2);
   assert(testG.numActions == G.numActions + 2);

   printf("\nTEST 4: VILLAGE DISCARDED - village card added to discard pile\n");


  printf("\tdiscardCount = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1);
  assert(testG.playedCardCount == G.playedCardCount + 1);

  printf("\tdiscarded card = %d, expected = %d", testG.playedCards[0], village);
  assert(testG.playedCards[0] == village);

   printf("\n\n----------------------village test complete------------------------\n\n\n");

   return 0;
}
