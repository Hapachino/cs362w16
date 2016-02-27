/*
Testing card: CARD_NAME

Steps:

Cases to check to ensure pass:

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

  printf("\n-------------------- Testing CARD_NAME --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
	  /***************************************************
		
  	  ***************************************************/
      printf("TEST1: \n");
      alarm(2);
      //TEST CASE HERE 
      alarm(0);
      printResults();
      resetError();

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing CARD_NAME complete <<<<<<<<<<<\n\n");
  return 0;
}
