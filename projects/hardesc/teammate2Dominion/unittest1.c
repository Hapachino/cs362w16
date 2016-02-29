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
   int bonus = 0;
   int i;

   G.handCount[player] = 5;
   G.hand[player][0] = estate;
   G.hand[player][1] = estate;
   G.hand[player][2] = estate;
   G.hand[player][3] = estate;
   G.hand[player][4] = estate;
   G.coins = 8; 

   memcpy(&testG, &G, sizeof(struct gameState));

   printf("\n\n\n-------------------------Testing updateCoins()-------------------\n\n");
   //TEST 1-------------------------------------------
   printf("TEST 1: NO COINS - 5 cards in hand, 0 treasure cards, 8 coins to start, bonus = 0\n");

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins - 8);
   assert(testG.coins == G.coins - 8);  

   //TEST 2------------------------------------------- 
   printf("TEST 2: COPPER TEST - 5 cards in hand, 1 copper card, bonus = 0\n");

   G.hand[player][0] = copper;
   G.coins = 0;

   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 1);
   assert(testG.coins == G.coins + 1 );  

   //TEST 3------------------------------------------- 
   printf("TEST 3: SILVER TEST - 5 cards in hand, 1 silver card, bonus = 0\n");

   G.hand[player][0] = silver;

   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 2);
   assert(testG.coins == G.coins + 2);  

   //TEST 4------------------------------------------- 
   printf("TEST 4: GOLD TEST - 5 cards in hand, 1 gold card, bonus = 0\n");

   G.hand[player][0] = gold;

   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 3);
   assert(testG.coins == G.coins + 3);  

    //TEST 5------------------------------------------- 
   printf("TEST 5: BONUS TEST - 5 cards in hand, 0 treasure cards, bonus = 5\n");

   G.hand[player][0] = estate;
   bonus = 5;

   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 5);
   assert(testG.coins == G.coins + 5);  

   //TEST 6-------------------------------------------
   printf("TEST 6: ONE OF EACH COIN - 5 cards in hand, 3 treasure cards: 1 gold, 1 silver, 1 copper, bonus = 0\n");

   G.hand[player][1] = gold;
   G.hand[player][3] = silver;
   G.hand[player][4] = copper;
   G.coins = 0;
   bonus = 0;

   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 6);
   assert(testG.coins == G.coins + 6);  

   //TEST 7-------------------------------------------
   printf("TEST 7: ALL CARDS TEST - %d cards in hand, one of every available card including treasure cards\n", G.handCount[player]);

   G.handCount[player] = treasure_map + 1; 
   for (i = curse; i <= treasure_map; i++) {
      G.hand[player][i] = i;
   } 
   
   memcpy(&testG, &G, sizeof(struct gameState));

   updateCoins(player, &testG, bonus);
   printf("\tcoin count = %d, expected = %d", testG.coins, G.coins + 6);
   assert(testG.coins == G.coins + 6);  

   printf("\n\n----------------------updateCoins() test complete------------------------\n\n\n");

   return 0;
}
