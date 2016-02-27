/*
Testing card: Smithy

Steps:
1. Draw 3 cards
2. Discard card //NULLED
2. Move card to played cards

Must check:
- Handcount increased by 2
- Deck decreased by 3 (check if reshuffled)
- Discard increased by 1 (check if reshuffled) ***INVALID***
  - NOTES: All discard happen at end of turn, does not happen when played
- All other states that should not be affected
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

  int seed = 5;
  int* test = malloc(last_tester * sizeof(int));
  createCompareStateArray(test,1);

  int i=0;
  int player = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

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
      play_smithy(&G,player,G.handCount[player] - 1);
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
  return 0;
}
