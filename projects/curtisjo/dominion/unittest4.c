/*
 * unittest4.c
 * unit test for the getCost function
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
   struct gameState gC;
   struct gameState testgC;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
   int numPlayers = 2;
   int seed = 1000;
   int result;
   // initialize the game state and player cards
   initializeGame(numPlayers, k, seed, &gC);
   printf("---------- Testing Function: getCost()----------\n"); 
   memcpy(&testgC, &gC, sizeof(struct gameState));
   // cardNum = curse 
   printf("cardNum = curse \n"); 
   result =  getCost(curse);
   printf("expected = 0\n");
   printf("result = %d\n\n", result);
   // cardNum = estate 
   printf("cardNum = estate \n"); 
   result =  getCost(estate);
   printf("expected = 2\n");
   printf("result = %d\n\n", result);
   // cardNum = duchy 
   printf("cardNum = duchy \n"); 
   result =  getCost(duchy);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = province 
   printf("cardNum = province \n"); 
   result =  getCost(province);
   printf("expected = 8\n");
   printf("result = %d\n\n", result);
   // cardNum = copper 
   printf("cardNum = copper \n"); 
   result =  getCost(copper);
   printf("expected = 0\n");
   printf("result = %d\n\n", result);
   // cardNum = silver 
   printf("cardNum = silver \n"); 
   result =  getCost(silver);
   printf("expected = 3\n");
   printf("result = %d\n\n", result);
   // cardNum = gold 
   printf("cardNum = gold \n"); 
   result =  getCost(gold);
   printf("expected = 6\n");
   printf("result = %d\n\n", result);
   // cardNum = adventurer 
   printf("cardNum = adventurer \n"); 
   result =  getCost(adventurer);
   printf("expected = 6\n");
   printf("result = %d\n\n", result);
   // cardNum = council_room 
   printf("cardNum = council_room \n"); 
   result =  getCost(council_room);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = feast 
   printf("cardNum = feast \n"); 
   result =  getCost(feast);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = gardens 
   printf("cardNum = gardens \n"); 
   result =  getCost(gardens);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = mine 
   printf("cardNum = mine \n"); 
   result =  getCost(mine);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = remodel 
   printf("cardNum = remodel \n"); 
   result =  getCost(remodel);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = smithy 
   printf("cardNum = smithy \n"); 
   result =  getCost(smithy);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = village 
   printf("cardNum = village \n"); 
   result =  getCost(village);
   printf("expected = 3\n");
   printf("result = %d\n\n", result);
   // cardNum = baron 
   printf("cardNum = baron \n"); 
   result =  getCost(baron);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = great_hall 
   printf("cardNum = great_hall \n"); 
   result =  getCost(great_hall);
   printf("expected = 3\n");
   printf("result = %d\n\n", result);
   // cardNum = minion 
   printf("cardNum = minion \n"); 
   result =  getCost(minion);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = steward 
   printf("cardNum = steward \n"); 
   result =  getCost(steward);
   printf("expected = 3\n");
   printf("result = %d\n\n", result);
   // cardNum = tribute 
   printf("cardNum = tribute \n"); 
   result =  getCost(tribute);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = ambassador 
   printf("cardNum = ambassador \n"); 
   result =  getCost(ambassador);
   printf("expected = 3\n");
   printf("result = %d\n\n", result);
   // cardNum = cutpurse 
   printf("cardNum = cutpurse \n"); 
   result =  getCost(cutpurse);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = embargo 
   printf("cardNum = embargo \n"); 
   result =  getCost(embargo);
   printf("expected = 2\n");
   printf("result = %d\n\n", result);
   // cardNum = outpost 
   printf("cardNum = outpost \n"); 
   result =  getCost(outpost);
   printf("expected = 5\n");
   printf("result = %d\n\n", result);
   // cardNum = salvager 
   printf("cardNum = salvager \n"); 
   result =  getCost(salvager);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = sea_hag 
   printf("cardNum = sea_hag \n"); 
   result =  getCost(sea_hag);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   // cardNum = treasure_map 
   printf("cardNum = treasure_map \n"); 
   result =  getCost(treasure_map);
   printf("expected = 4\n");
   printf("result = %d\n\n", result);
   return 0;
}
