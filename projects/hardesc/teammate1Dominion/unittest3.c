/*
 *
 * unittest1.c
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
   int player = 0;
   int numPlayers = 2;
   int trashFlag = 0;
   int seed = 1000;
   int handPos = 4; 
   int returnVal;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

   initializeGame(numPlayers, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   printf("\n\n\n-------------------------Testing discardCard()-------------------\n\n");
   //TEST 1-------------------------------------------
   printf("\nTEST 1: DISCARD LAST CARD - last card in hand of 5 is discarded\n");

   returnVal = discardCard(handPos, player, &testG, trashFlag);


  printf("\treturnVal = %d, expected = 0\n", returnVal);
  assert(returnVal == 0);

  printf("\tplayedCard pile value = %d, expected = %d", testG.playedCards[testG.playedCardCount - 1], G.hand[player][handPos]); 
  assert(testG.playedCards[testG.playedCardCount - 1] == G.hand[player][handPos]); 

  printf("\tplayedCard count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1); 
  assert(testG.playedCardCount == G.playedCardCount + 1); 

  printf("\tplayed card value = %d, expected = -1", testG.hand[player][handPos]);
  assert(testG.hand[player][handPos] == -1);

  printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] - 1);
  assert(testG.handCount[player] == G.handCount[player] - 1);

  printf("\tcard at handPos 0 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\tcard at handPos 2 = %d, expected = %d", testG.hand[player][2], G.hand[player][2]);
  assert(testG.hand[player][2] == G.hand[player][2]);

  printf("\tcard at handPos 3 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

   //TEST 2-------------------------------------------
   printf("\nTEST 2: DISCARD WITH ONLY ONE CARD IN HAND - hand of one card is discarded\n");

   G.hand[player][1] = -1;    
   G.hand[player][2] = -1;    
   G.hand[player][3] = -1;   
   G.hand[player][4] = -1;
   G.handCount[player] = 1;
   handPos = 0;

   memcpy(&testG, &G, sizeof(struct gameState));

   returnVal = discardCard(handPos, player, &testG, trashFlag);



  printf("\treturnVal = %d, expected = 0", returnVal);
  assert(returnVal == 0);

  printf("\tplayedCard pile value = %d, expected = %d", testG.playedCards[testG.playedCardCount - 1], G.hand[player][handPos]); 
  assert(testG.playedCards[testG.playedCardCount - 1] == G.hand[player][handPos]); 

  printf("\tplayedCard count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1); 
  assert(testG.playedCardCount == G.playedCardCount + 1); 

  printf("\tplayed card value = %d, expected = -1", testG.hand[player][handPos]);
  assert(testG.hand[player][handPos] == -1);

  printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] - 1);
  assert(testG.handCount[player] == G.handCount[player] - 1);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\tcard at handPos 2 = %d, expected = %d", testG.hand[player][2], G.hand[player][2]);
  assert(testG.hand[player][2] == G.hand[player][2]);

  printf("\tcard at handPos 3 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

   //TEST 3-------------------------------------------
   printf("\nTEST 3: DISCARD FROM MIDDLE OF HAND - middlle card from hand of 55555 is discarded\n");

   initializeGame(numPlayers, k, seed, &G);

   handPos = 2;

   memcpy(&testG, &G, sizeof(struct gameState));

   returnVal = discardCard(handPos, player, &testG, trashFlag);


  printf("\treturnVal = %d, expected = 0", returnVal);
  assert(returnVal == 0);

  printf("\tplayedCard pile value = %d, expected = %d", testG.playedCards[testG.playedCardCount - 1], G.hand[player][handPos]); 
  assert(testG.playedCards[testG.playedCardCount - 1] == G.hand[player][handPos]); 

  printf("\tplayedCard count = %d, expected = %d", testG.playedCardCount, G.playedCardCount + 1); 
  assert(testG.playedCardCount == G.playedCardCount + 1); 

  printf("\tplayed card value = %d, expected = %d", testG.hand[player][handPos], G.hand[player][4]);
  assert(testG.hand[player][handPos] == G.hand[player][4]);

  printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] - 1);
  assert(testG.handCount[player] == G.handCount[player] - 1);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\tcard at handPos 3 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][4], -1);
  assert(testG.hand[player][4] == -1);

   //TEST 4-------------------------------------------
   printf("\nTEST 4: TRASH CARD - last card in hand of 5 is trashed\n");

   handPos = 4;
   trashFlag = 1;

   memcpy(&testG, &G, sizeof(struct gameState));

   returnVal = discardCard(handPos, player, &testG, trashFlag);


  printf("\treturnVal = %d, expected = 0", returnVal);
  assert(returnVal == 0);

  printf("\tplayedCard pile value = %d, expected = %d", testG.playedCards[testG.playedCardCount], G.playedCards[G.playedCardCount]); 
  assert(testG.playedCards[testG.playedCardCount] == G.playedCards[G.playedCardCount]); 

  printf("\tplayedCard count = %d, expected = %d", testG.playedCardCount, G.playedCardCount); 
  assert(testG.playedCardCount == G.playedCardCount); 

  printf("\tplayed card value = %d, expected = -1", testG.hand[player][handPos]);
  assert(testG.hand[player][handPos] == -1);

  printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] - 1);
  assert(testG.handCount[player] == G.handCount[player] - 1);

  printf("\tcard at handPos 0 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\tcard at handPos 2 = %d, expected = %d", testG.hand[player][2], G.hand[player][2]);
  assert(testG.hand[player][2] == G.hand[player][2]);

  printf("\tcard at handPos 3 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

   //TEST 5-------------------------------------------
   printf("\nTEST 5: INVALID DISCARD - handPos is greater than handCount - 1 \n");

   handPos = 5;
   trashFlag = 0;

   memcpy(&testG, &G, sizeof(struct gameState));

   returnVal = discardCard(handPos, player, &testG, trashFlag);


  printf("\treturnVal = %d, expected = -1", returnVal);
  assert(returnVal == -1);

  printf("\tplayedCard pile value = %d, expected = %d", testG.playedCards[testG.playedCardCount], G.playedCards[G.playedCardCount]); 
  assert(testG.playedCards[testG.playedCardCount] == G.playedCards[G.playedCardCount]); 

  printf("\tplayedCard count = %d, expected = %d", testG.playedCardCount, G.playedCardCount); 
  assert(testG.playedCardCount == G.playedCardCount); 

  printf("\tplayed card value = %d, expected = -1", testG.hand[player][handPos]);
  assert(testG.hand[player][handPos] == G.hand[player][handPos]);

  printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player]);
  assert(testG.handCount[player] == G.handCount[player]);

  printf("\tcard at handPos 0 = %d, expected = %d", testG.hand[player][0], G.hand[player][0]);
  assert(testG.hand[player][0] == G.hand[player][0]);

  printf("\tcard at handPos 1 = %d, expected = %d", testG.hand[player][1], G.hand[player][1]);
  assert(testG.hand[player][1] == G.hand[player][1]);

  printf("\tcard at handPos 2 = %d, expected = %d", testG.hand[player][2], G.hand[player][2]);
  assert(testG.hand[player][2] == G.hand[player][2]);

  printf("\tcard at handPos 3 = %d, expected = %d", testG.hand[player][3], G.hand[player][3]);
  assert(testG.hand[player][3] == G.hand[player][3]);

  printf("\tcard at handPos 4 = %d, expected = %d", testG.hand[player][4], G.hand[player][4]);
  assert(testG.hand[player][4] == G.hand[player][4]);

  printf("\tcard at handPos 5 = %d, expected = %d", testG.hand[player][5], G.hand[player][5]);
  assert(testG.hand[player][5] == G.hand[player][5]);

   printf("\n\n----------------------gainCard() test complete------------------------\n\n\n");

   return 0;
}
