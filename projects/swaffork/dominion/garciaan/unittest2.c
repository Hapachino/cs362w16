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
#include <signal.h>
#include <unistd.h>

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState previousG;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int* test = malloc(last_tester * sizeof(int));
  createCompareStateArray(test,1);
  //update coins should only affect coins
  test[num_coins] = 0;

  int i=0;
  int player = 0;
  int bonus = 0; 
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing updateCoins --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
	  /***************************************************
		Play a single copper with another non treasure in hand
  	  ***************************************************/
      printf("TEST1: Play Copper\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(smithy,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 1);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
		Play a single silver with another non treasure in hand
      ***************************************************/
      printf("TEST2: Play Silver\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(curse,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(numHandCards(&G) == 2);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 2);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
		Play a single gold with nothing else in hand
      ***************************************************/
      printf("TEST3: Play Gold\n");
      alarm(2);
	    checkError(numHandCards(&G) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 1);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 3);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with another non treasure in hand
      ***************************************************/
      printf("TEST4: Play Two of Each Coin\n");
      alarm(2);
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(sea_hag,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 12);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play 2 of each coin with a bonus of (8) with another non treasure in hand
      ***************************************************/
      printf("TEST5: Play One of Each Coin with Bonus\n");
      alarm(2);
      bonus = 8;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(copper,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(silver,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(gainCard(gold,&G,2,player) == 0);
      checkError(numHandCards(&G) == 7);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 20);
      alarm(0);
      printResults();
      resetError();
      
      //reset
      discardAll(player,&G);

      /***************************************************
        Play no treasures with a non empty hand
      ***************************************************/
      printf("TEST6: Play No Treasures (Non-Empty Hand)\n");
      alarm(2);
      bonus = 0;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(province,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(numHandCards(&G) > 0);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 0);
      alarm(0);
      printResults();
      resetError();

      //reset
      discardAll(player,&G);

      /***************************************************
        Play no treasures with a non empty hand with bonus of (8)
      ***************************************************/
      printf("TEST7: Play No Treasures (Non-Empty Hand) with Bonus\n");
      alarm(2);
      bonus = 8;
      checkError(numHandCards(&G) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(province,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(minion,&G,2,player) == 0);
      checkError(gainCard(estate,&G,2,player) == 0);
      checkError(numHandCards(&G) > 0);
      previousG = G;
      updateCoins(player,&G,bonus);
      checkError(checkStates(&previousG,&G,test,0));
      checkError(G.coins == 8);
      alarm(0);
      printResults();
      resetError();
    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing updateCoins complete <<<<<<<<<<<\n\n");
  return 0;
}