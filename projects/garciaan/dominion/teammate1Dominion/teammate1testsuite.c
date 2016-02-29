/*
Testing Function: teammate1

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

  printf("\n-------------------- Testing Teammate1 --------------------\n\n");
  printf("\n-------------------- Testing Smithy --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    resetCards(&G,player);

    gainCard(adventurer,&G,1,player);
    gainCard(copper,&G,1,player);
    gainCard(silver,&G,1,player);
    gainCard(gold,&G,1,player);
    
    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
            Smithy
      ***************************************************/
      test[player_deck] = 0;
      test[player_deck_count] = 0;
      test[player_hand] = 0;
      test[player_hand_count] = 0;
      test[played_cards] = 0;
      test[played_card_count] = 0;
      G.playedCardCount = 0;
      

      alarm(2);
      checkError(gainCard(smithy,&G,2,player) == 0); 
      previousG = G;
      playSmithy(&G,G.handCount[player] - 1);
      alarm(0);

      printf("TEST1: Nothing else affected\n");
      alarm(2);
      checkError(checkStates(&previousG,&G,test,0));
      alarm(0);
      printResults();
      resetError();

      printf("TEST2: Smithy Deck Effects\n");
      alarm(2);
      checkError(previousG.deckCount[player] - 3 == G.deckCount[player]);
      alarm(0);
      printResults();
      resetError();

      printf("TEST3: Smithy Hand Effects\n");
      alarm(2);
      checkError(previousG.handCount[player] + 2 == G.handCount[player]);
      checkError(contains(G.deck[player],G.deckCount[player],copper) == 1);
      checkError(contains(G.deck[player],G.deckCount[player],silver) == 1);
      checkError(contains(G.deck[player],G.deckCount[player],gold) == 1);
      checkError(contains(G.deck[player],G.deckCount[player],adventurer) == 0);
      alarm(0);
      printResults();
      resetError();

      printf("TEST4: Played Cards Effected\n");
      alarm(2);
      checkError(previousG.playedCardCount + 1 == G.playedCardCount);
      checkError(G.playedCards[G.playedCardCount - 1] == smithy);
      alarm(0);
      printResults();
      resetError();

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing Smithy complete <<<<<<<<<<<\n\n");
  printf(">>>>>>>>>>> SUCCESS: Testing Teammate1 complete <<<<<<<<<<<\n\n");
  return 0;
}
