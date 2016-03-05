/*
 *
 * cardtest3.c
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
  
   printf("\n\n\n-------------------------Testing adventurer-------------------\n\n");
   //TEST 1-------------------------------------------

   G.hand[player][0] = estate;
   G.hand[player][1] = duchy;
   G.hand[player][2] = adventurer;
   G.hand[player][3] = province;
   G.hand[player][4] = curse;
   G.handCount[player] = 5;

   G.deck[player][0] = estate; 
   G.deck[player][1] = duchy; 
   G.deck[player][2] = gold; 
   G.deck[player][3] = mine; 
   G.deck[player][4] = smithy; 
   G.deck[player][5] = adventurer; 
   G.deck[player][6] = silver; 
   G.deck[player][7] = estate;
   G.deck[player][8] = copper;
   G.deck[player][9] = village;
   G.deckCount[player] = 10;

   memcpy(&testG, &G, sizeof(struct gameState));
  
   cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

   printf("\nTEST 1: DRAW 2 TREASURE CARDS - player has 2 new cards - 1 discard\n");

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] + 1);
   assert(testG.handCount[player] == G.handCount[player] + 1);

   printf("\nTEST 2: TREASURE CARDS FROM DECK - new cards are the next treausre cards from deck\n");


  printf("\tdeckCount = %d, expected = %d", testG.deckCount[player], G.deckCount[player] - 4);
  assert(testG.deckCount[player] == G.deckCount[player] - 4);

  printf("\thand card #1 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\thand card #2 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\thand card #3 = %d, expected = %d", testG.hand[player][2], G.deck[player][6]);
  assert(testG.hand[player][2] == G.deck[player][6]);

  printf("\thand card #4 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

  printf("\thand card #5 = %d, expected = %d", testG.hand[player][4], G.hand[player][4]);
  assert(testG.hand[player][4] == G.hand[player][4]);

  printf("\thand card #6 = %d, expected = %d", testG.hand[player][5], G.deck[player][8]);
  assert(testG.hand[player][5] == G.deck[player][8]);

  printf("\thand card #7 = %d, expected = %d", testG.hand[player][6], -1);
  assert(testG.hand[player][6] == -1);
   
   printf("\nTEST 3: DISCARD PILE - number of non-treasure cards picked up + played card\n");



  printf("\tdiscardCount = %d, expected = %d", testG.discardCount[player], G.discardCount[player] + 3);
  assert(testG.discardCount[player] == G.discardCount[player] + 3);

  printf("\tdiscarded card #1 = %d, expected = %d", testG.discard[player][0], G.deck[player][9]);
  assert(testG.discard[player][0] == G.deck[player][9]);

  printf("\tdiscarded card #2 = %d, expected = %d", testG.discard[player][1], G.deck[player][7]);
  assert(testG.discard[player][1] == G.deck[player][7]);

  printf("\tdiscarded card #3 = %d, expected = %d", testG.discard[player][2], G.hand[player][2]);
  assert(testG.discard[player][2] == G.deck[player][2]);

   printf("\n\n----------------------adventurer test complete------------------------\n\n\n");

   return 0;
}
