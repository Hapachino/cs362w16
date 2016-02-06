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
   int seed = 1000;
   int returnVal;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

   initializeGame(numPlayers, k, seed, &G);

   memcpy(&testG, &G, sizeof(struct gameState));

   printf("\n\n\n-------------------------Testing isGameOver()-------------------\n\n");
   //TEST 1-------------------------------------------
   printf("\nTEST 1: GAME NOT OVER - when 0, 1, or 2 piles are depleted \n");

   returnVal = isGameOver(&testG);
   printf("\t0 piles depleted returnVal = %d, expected = 0", returnVal);
   assert(returnVal == 0);

   testG.supplyCount[adventurer] = 0;

   returnVal = isGameOver(&testG);
   printf("\t1 pile depleted returnVal = %d, expected = 0", returnVal);
   assert(returnVal == 0);

   testG.supplyCount[embargo] = 0;

   returnVal = isGameOver(&testG);
   printf("\t2 piles depleted returnVal = %d, expected = 0", returnVal);
   assert(returnVal == 0);

   //TEST 2-------------------------------------------
   printf("\nTEST 2: GAME IS OVER - when 3 piles are depleted \n");

   testG.supplyCount[village] = 0;

   returnVal = isGameOver(&testG);
   printf("\t2 piles depleted returnVal = %d, expected = 1", returnVal);
   assert(returnVal == 1);

   //TEST 3-------------------------------------------
   printf("\nTEST 3: GAME IS OVER - when province pile is depleted \n");

   memcpy(&testG, &G, sizeof(struct gameState));

   testG.supplyCount[province] = 0;
   returnVal = isGameOver(&testG);
   printf("\tprovince pile is depleted returnVal = %d, expected = 1", returnVal);
   assert(returnVal == 1);


   printf("\n\n----------------------isGameOver() test complete------------------------\n\n\n");

   return 0;
}
