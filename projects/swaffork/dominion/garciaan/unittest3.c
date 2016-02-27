/*
Testing Function: gainCard

Steps:
1. Check supply pile or if card in game
2. Add card to deck/hand/discard accordingly
3. Increment deck/hand/discard count accordingly
4. Decerement supply count

Cases to check to ensure pass:
- Gain card to hand
- Gain card to deck
- Gain card to discard
- Gain card with no supply
- Gain a card not in the game

Each case check:
- Only hand and/or deck/discard and supplycount is modified
- Card is actually gained

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

  int discard = 0;
  int deck = 1;
  int hand = 2;
  int i=0;
  int player = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing gainCard --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);

    
    if (whoseTurn(&G) == 0) {
      player = 0;
	  /***************************************************
		        Gain a card to discard
  	  ***************************************************/
      printf("TEST1: Gain a card to discard\n");
      test[supply_count] = 0;
      test[player_discard] = 0;
      test[player_discard_count] = 0;
      alarm(2);
      previousG = G;
      checkError(gainCard(smithy, &G, discard, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(previousG.discardCount[player] + 1 == G.discardCount[player]);
      checkError(fullDeckCount(player,smithy,&G) == 1); //make sure there is a smithy
      checkError((previousG.supplyCount[smithy] - 1) == G.supplyCount[smithy]);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card to deck
      ***************************************************/
      printf("TEST2: Gain a card to deck\n");
      test[player_deck] = 0; //player deck will change
      test[player_deck_count] = 0;  //deck count will change
      test[supply_count] = 0; //supply count will change
      alarm(2);
      previousG = G;
      checkError(gainCard(gold, &G, deck, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError((previousG.deckCount[player] + 1) == G.deckCount[player]);
      checkError(fullDeckCount(player,gold,&G) == 1); //make sure 1 gold now in deck
      checkError((previousG.supplyCount[gold] - 1) == G.supplyCount[gold]);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card to hand
      ***************************************************/
      printf("TEST3: Gain a card to hand\n");
      test[player_hand] = 0;
      test[player_hand_count] = 0;
      test[supply_count] = 0;
      alarm(2);
      previousG = G;
      checkError(gainCard(gold, &G, hand, player) == 0);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(previousG.handCount[player] + 1 == G.handCount[player]);
      checkError(previousG.supplyCount[gold] - 1 == G.supplyCount[gold]);
      //make sure last card gained is a gold
      checkError(handCard(G.handCount[player] - 1,&G) == gold);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card with 0 supply. Nothing changes
      ***************************************************/
      printf("TEST4: Gain a card with 0 supply\n");
      alarm(2);
      G.supplyCount[great_hall] = 0; // set supply count to 0
      previousG = G;
      //we want an error returned
      checkError(gainCard(great_hall, &G, discard, player) == -1);
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

      /***************************************************
            Gain a card that is not in game. Nothing changes.
            Assumes salvager is not in game.
      ***************************************************/
      printf("TEST5: Gain a card that is not in game\n");
      alarm(2);
      previousG = G;
      checkError(gainCard(salvager, &G, discard, player) == -1);
      //we want an error returned
      checkError(checkStates(&previousG,&G,test,0) == 1);
      alarm(0);
      printResults();
      resetError();
      createCompareStateArray(test,1); //reset the excludes

    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing gainCard complete <<<<<<<<<<<\n\n");
  return 0;
}
