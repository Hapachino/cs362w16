/*
Testing Function: updateCoins

Steps:
1. Set coint count to 0
2. For each card in hand, check if copper, silver, or gold.
3. Add coin count accordingly for each
4. Add coin bonus

Cases to check to ensure pass:
- Play nothing (non-empty hand)
- Play copper == +1
- Play silver == +2
- Play gold == +3
- Play multiple (one of each) == +6
- Play bonus

Each case check:
- With other card(s) in hand
- Coins from other player not used
- No other state affected
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState previousG;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int* test = malloc(played_card_count * sizeof(int));
  createCompareStateArray(test,1);
  //update coins should only affect coins
  test[num_coins] = 0;
  test[player_hand] = 0;

  int i=0;
  int player = 0;
  int bonus = 0; 

  printf("\n-------------------- Testing updateCoins --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
	  /***************************************************
		Play a single copper with another non treasure in hand
  	  ***************************************************/
      printf("TEST1: Play Copper\n");
      assert(numHandCards(&G) == 0);
      assert(gainCard(smithy,&G,2,player) == 0);
      assert(gainCard(copper,&G,2,player) == 0);
      assert(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 1);
      printf("\t- RESULT: PASS\n\n");

      //reset
      discardAll(player,&G);

      /***************************************************
		Play a single silver with another non treasure in hand
      ***************************************************/
      printf("TEST2: Play Silver\n");
      assert(numHandCards(&G) == 0);
      assert(gainCard(curse,&G,2,player) == 0);
      assert(gainCard(silver,&G,2,player) == 0);
      assert(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 2);
      printf("\t- RESULT: PASS\n\n");

      //reset
      discardAll(player,&G);

      /***************************************************
		Play a single gold with another non treasure in hand
      ***************************************************/
      printf("TEST3: Play Gold\n");
	  assert(numHandCards(&G) == 0);
      assert(gainCard(province,&G,2,player) == 0);
      assert(gainCard(gold,&G,2,player) == 0);
      assert(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 3);
      printf("\t- RESULT: PASS\n\n");

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with another non treasure in hand
      ***************************************************/
      printf("TEST4: Play Two of Each Coin\n");
      assert(numHandCards(&G) == 0);
      assert(gainCard(sea_hag,&G,2,player) == 0);
      assert(gainCard(copper,&G,2,player) == 0);
      assert(gainCard(copper,&G,2,player) == 0);
      assert(gainCard(silver,&G,2,player) == 0);
      assert(gainCard(silver,&G,2,player) == 0);
      assert(gainCard(gold,&G,2,player) == 0);
      assert(gainCard(gold,&G,2,player) == 0);
      assert(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 12);
      printf("\t- RESULT: PASS\n\n");

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with a bonus of (8) with another non treasure in hand
      ***************************************************/
      printf("TEST4: Play One of Each Coin with Bonus\n");
      bonus = 8;
      assert(numHandCards(&G) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(gainCard(copper,&G,2,player) == 0);
      assert(gainCard(copper,&G,2,player) == 0);
      assert(gainCard(silver,&G,2,player) == 0);
      assert(gainCard(silver,&G,2,player) == 0);
      assert(gainCard(gold,&G,2,player) == 0);
      assert(gainCard(gold,&G,2,player) == 0);
      assert(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 20);
      printf("\t- RESULT: PASS\n\n");
      
      //reset
      discardAll(player,&G);

      /***************************************************
        Play no treasures with a non empty hand
      ***************************************************/
      printf("TEST5: Play No Treasures (Non-Empty Hand)\n");
      bonus = 0;
      assert(numHandCards(&G) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(gainCard(province,&G,2,player) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(gainCard(minion,&G,2,player) == 0);
      assert(numHandCards(&G) > 0);
      previousG = G;
      updateCoins(player,&G,bonus);
      assert(checkStates(&previousG,&G,test,0));
      assert(G.coins == 0);
      printf("\t- RESULT: PASS\n\n");
    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing updateCoins complete <<<<<<<<<<<\n\n");
  return 0;
}