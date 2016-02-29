/*
Testing Function: buyCard

Steps:
1. Check if number of buys, supply count, and coins is enough
2. Change phase to buy phase? nonono.... but phase is affected in this function
3. Put card in discard
4. Subtract the coins
5. Decrement buys

Cases to check to ensure pass:
- Buy a card
- Buy 2 cards with 2 buys
- Attempt to buy 2 cards with only 1 buy
- Attempt to buy a card that is too expensive
- Attempt to buy a card with supply 0
- Attempt to buy a card not in game


Each case check:

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


  int i=0;
  int player = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing buyCard --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
	    /***************************************************
            Buy a card (province)		
  	  ***************************************************/
      printf("TEST1: Buy a card (province) \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(province,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-1] == province);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(previousG.supplyCount[province] - 1 == G.supplyCount[province]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Buy 2 cards with 2 buys (smithy,village)  
      ***************************************************/
      printf("TEST2: Buy a 2 cards with 2 buys (smithy,village) \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 2;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(smithy,&G) == 0); 
      checkError(buyCard(village,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-2] == smithy);
      checkError(G.discard[player][G.discardCount[player]-1] == village);
      checkError(previousG.discardCount[player] + 2 == G.discardCount[player]);
      checkError(previousG.supplyCount[smithy] - 1 == G.supplyCount[smithy]);
      checkError(previousG.supplyCount[village] - 1 == G.supplyCount[village]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy 2 cards (2 adventurer) with only 1 buy 
      ***************************************************/
      printf("TEST3: Attempt to buy 2 cards (2 adventurer) with only 1 buy \n");
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      test[num_phase] = 0; //don't check the phase change
      test[supply_count] = 0;
      test[num_buys] = 0;
      test[num_coins] = 0;
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(adventurer,&G) == 0); 
      checkError(buyCard(adventurer,&G) == -1); //second buy should fail
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(G.discard[player][G.discardCount[player]-1] == adventurer);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(previousG.supplyCount[adventurer] - 1 == G.supplyCount[adventurer]);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card that is too expensive
      ***************************************************/
      printf("TEST4: Attempt to buy a card that is too expensive \n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 1;
      alarm(2);
      previousG = G;
      checkError(buyCard(gardens,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card with supply 0
      ***************************************************/
      printf("TEST5: Attempt to buy a card with supply 0 \n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 100;
      G.supplyCount[minion] = 0;
      alarm(2);
      previousG = G;
      checkError(buyCard(minion,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
            Attempt to buy a card not in game (salvager)
      ***************************************************/
      printf("TEST6: Attempt to buy a card not in game (salvager)\n");
      test[num_phase] = 0; //don't check the phase change
      G.numBuys = 1;
      G.coins = 100;
      alarm(2);
      previousG = G;
      checkError(buyCard(salvager,&G) == -1); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();




    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing buyCard complete <<<<<<<<<<<\n\n");
  return 0;
}
