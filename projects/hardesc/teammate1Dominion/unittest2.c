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
   int numPlayers = 2;
   int player = 0;
   int toFlag = 0;
   //int i;
   int seed = 1000;
   int returnVal = 133;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

   initializeGame(numPlayers, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   printf("\n\n\n-------------------------Testing gainCard()-------------------\n\n");
   //TEST 1-------------------------------------------
   printf("\nTEST 1: INVALID CARD - add feast to discard pile, but card not available\n");

   returnVal = gainCard(feast, &testG, toFlag, player);

   printf("\treturnVal = %d, expected = -1", returnVal);
   assert(returnVal == -1);  

   printf("\tdiscardCount = %d, expected = %d", testG.discardCount[player], G.discardCount[player]);
   assert(testG.discardCount[player] == G.discardCount[player]);

   printf("\tsupplyCount = %d, expected = %d", testG.supplyCount[feast], G.supplyCount[feast]);
   assert(testG.supplyCount[feast] == G.supplyCount[feast]);

   printf("\ttop discard pile card = %d, expected = %d", testG.discard[player][testG.discardCount[player]], G.discard[player][testG.discardCount[player]]);
   assert(testG.discard[player][testG.discardCount[player]] == G.discard[player][testG.discardCount[player]]);
   //TEST 2-------------------------------------------
  
   memcpy(&testG, &G, sizeof(struct gameState));
 
   printf("\nTEST 2: CARD TO DISCARD PILE - add village to discard pile\n");

   returnVal = gainCard(village, &testG, toFlag, player);
      
   printf("\treturnVal = %d, expected = 0\n", returnVal);
   assert(returnVal == 0);  

   printf("\ttop discard pile card = %d, expected = %d\n", testG.discard[player][testG.discardCount[player] - 1], village);
   assert(testG.discard[player][testG.discardCount[player] - 1] == village);

   printf("\tdiscardCount = %d, expected = %d\n", testG.discardCount[player], G.discardCount[player] + 1);
   assert(testG.discardCount[player] == G.discardCount[player] + 1);

   printf("\tsupplyCount = %d, expected = %d\n", testG.supplyCount[village], G.supplyCount[village] - 1);
   assert(testG.supplyCount[village] == G.supplyCount[village] - 1);

   //TEST 3-------------------------------------------
   printf("\nTEST 3: DECK ISOLATION - after successful add village to discard pile, check that deck and hand piles haven't changed\n");

            

   printf("\ttop deck pile card = %d, expected = %d", testG.deck[player][testG.deckCount[player]], G.deck[player][G.deckCount[player]]);
   assert(testG.deck[player][testG.deckCount[player]] == G.deck[player][G.deckCount[player]]);

   printf("\tdeckCount = %d, expected = %d", testG.deckCount[player], G.deckCount[player]);
   assert(testG.deckCount[player] == G.deckCount[player]);

   printf("\ttop hand card = %d, expected = %d", testG.hand[player][testG.handCount[player]], G.hand[player][G.handCount[player]]);
   assert(testG.hand[player][testG.handCount[player]] == G.hand[player][G.handCount[player]]);

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player]);  
   assert(testG.handCount[player] == G.handCount[player]);

   //TEST 4-------------------------------------------
   printf("\nTEST 4: PLAYER ISOLATION - after successful add village to discard pile, check that the other player's cards haven't changed\n");

                  

   printf("\ttop discard pile card = %d, expected = %d", testG.discard[player + 1][testG.discardCount[player + 1]], G.discard[player + 1][G.discardCount[player + 1]]);
   assert(testG.discard[player + 1][testG.discardCount[player + 1]] == G.discard[player + 1][G.discardCount[player + 1]]);

   printf("\tdiscardCount = %d, expected = %d", testG.discardCount[player + 1], G.discardCount[player + 1]);
   assert(testG.discardCount[player + 1] == G.discardCount[player + 1]);

   printf("\ttop deck pile card = %d, expected = %d", testG.deck[player + 1][testG.deckCount[player + 1]], G.deck[player + 1][G.deckCount[player + 1]]);
   assert(testG.deck[player + 1][testG.deckCount[player + 1]] == G.deck[player + 1][G.deckCount[player + 1]]);

   printf("\tdeckCount = %d, expected = %d", testG.deckCount[player + 1], G.deckCount[player + 1]);
   assert(testG.deckCount[player + 1] == G.deckCount[player + 1]);

   printf("\ttop hand card = %d, expected = %d", testG.hand[player + 1][testG.handCount[player + 1]], G.hand[player + 1][G.handCount[player + 1]]);
   assert(testG.hand[player + 1][testG.handCount[player + 1]] == G.hand[player + 1][G.handCount[player + 1]]);

   printf("\thandCount = %d, expected = %d", testG.handCount[player + 1], G.handCount[player + 1]);  
   assert(testG.handCount[player + 1] == G.handCount[player + 1]);

   //TEST 5-------------------------------------------
  
   memcpy(&testG, &G, sizeof(struct gameState));
   toFlag = 1;
 
   printf("\nTEST 5: CARD TO DECK PILE - add village to discard pile\n");

   returnVal = gainCard(village, &testG, toFlag, player);
            
   printf("\treturnVal = %d, expected = 0", returnVal);
   assert(returnVal == 0);  

   printf("\ttop deck pile card = %d, expected = %d", testG.deck[player][testG.deckCount[player] - 1], village);
   assert(testG.deck[player][testG.deckCount[player] - 1] == village);

   printf("\tdeckCount = %d, expected = %d", testG.deckCount[player], G.deckCount[player] + 1);
   assert(testG.deckCount[player] == G.deckCount[player] + 1);

   printf("\tsupplyCount = %d, expected = %d", testG.supplyCount[village], G.supplyCount[village] - 1);
   assert(testG.supplyCount[village] == G.supplyCount[village] - 1);

   //TEST 6-------------------------------------------
  
   memcpy(&testG, &G, sizeof(struct gameState));
   toFlag = 2;
 
   printf("\nTEST 6: CARD TO HAND - add village to hand\n");

   returnVal = gainCard(village, &testG, toFlag, player);

   printf("\treturnVal = %d, expected = 0", returnVal);
   assert(returnVal == 0);  

   printf("\ttop hand card = %d, expected = %d", testG.hand[player][testG.handCount[player] - 1], village);
   assert(testG.hand[player][testG.handCount[player] - 1] == village);

   printf("\thandCount = %d, expected = %d", testG.handCount[player], G.handCount[player] + 1);
   assert(testG.handCount[player] == G.handCount[player] + 1);

   printf("\tsupplyCount = %d, expected = %d", testG.supplyCount[village], G.supplyCount[village] - 1);
   assert(testG.supplyCount[village] == G.supplyCount[village] - 1);


   printf("\n\n----------------------gainCard() test complete------------------------\n\n\n");

   return 0;
}
