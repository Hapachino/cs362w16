/*
Testing card: great hall
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
  int k[10] = {adventurer, great_hall, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int* test = malloc(last_tester * sizeof(int));
  createCompareStateArray(test,1);
  test[player_deck] = 0;
  test[player_deck_count] = 0;
  test[num_actions] = 0;
  test[played_cards] = 0;
  test[played_card_count] = 0;
  test[player_hand] = 0;
  test[player_hand_count] = 0;

  int i=0;
  int j;
  int player = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing Great Hall --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    resetCards(&G,player);
    for (j = 0; j < 3; j++){ //put 3 smithys to deck
      gainCard(smithy,&G,1,player);
    }
    gainCard(gold,&G,1,player); //put a gold card on top

    //add the great hall card to hand
    gainCard(great_hall,&G,2,player);

    if (whoseTurn(&G) == 0) {
      player = 0;
    /***************************************************
    
      ***************************************************/
      printf("TEST1: Play Great Hall\n");
      alarm(2);
      previousG = G;
      play_great_hall(&G,player,G.handCount[player] - 1);
      printf("    TEST1.1: Hand Effects\n");
      checkError(previousG.handCount[player] == G.handCount[player] && G.handCount[player] == 1);
      checkError(G.hand[player][G.handCount[player] - 1] == gold);
      printResults();
      resetError();

      printf("    TEST1.2: Deck Effects\n");
      checkError(previousG.deckCount[player] - 1 == G.deckCount[player]);
      //smithy was underneath the gold, make sure it is now the top
      checkError(G.deck[player][G.deckCount[player] - 1] == smithy); 
      printResults();
      resetError();

      printf("    TEST1.3: Played Card Effects\n");
      checkError(previousG.playedCardCount + 1 == G.playedCardCount);
      checkError(G.playedCards[G.playedCardCount - 1] == great_hall);
      printResults();
      resetError();

      printf("    TEST1.4: Num Actions Effect\n");
      checkError(previousG.numActions + 1 == G.numActions);
      printResults();
      resetError();

      printf("    TEST1.5: Nothing else affected\n");
      checkError(checkStates(&previousG,&G,test,0) == 1);
      printResults();
      resetError();

      alarm(0);

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing CARD_NAME complete <<<<<<<<<<<\n\n");
  return 0;
}
