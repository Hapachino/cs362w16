/*
Testing Function: FUNCTION_NAME

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

#define VERBOSE 0

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState previousG;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  int* test = malloc(last_tester * sizeof(int));
  createCompareStateArray(test,1);
  test[player_hand] = 0;
  test[player_hand_count] = 0;
  test[player_deck] = 0; //will only be affected upon reshuffle
  test[player_deck_count] = 0;
  test[player_discard] = 0;
  test[player_discard_count] = 0;
  test[played_cards] = 0;
  test[played_card_count] = 0;

  int money = 0;
  int smithyPos = -1;
  int adventurerPos = -1;
  int i=0;
  int j;
  int num;
  int result;
  int card;
  int errors = 0;

  int numSmithies = 0;
  int numAdventurers = 0;

  int iteration=0;
  int player = 0;
  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Random Testing Adventurer --------------------\n\n");
  for (iteration = 1; iteration <= 1000; iteration++){ 
    resetError();
    alarm(2);
    //initTestGame(2, k, seed, &G);
    initializeGame(2,k,iteration,&G);
    numAdventurers = 0;
    while (!isGameOver(&G)) {
      player = whoseTurn(&G);
      money = 0;
      smithyPos = -1;
      adventurerPos = -1;
      for (i = 0; i < numHandCards(&G); i++) {
        if (handCard(i, &G) == smithy)
          smithyPos = i;
        else if (handCard(i, &G) == adventurer)
          adventurerPos = i;
      }
      
      if (adventurerPos != -1) {
        previousG = G;
        
        if (VERBOSE)
          printf("%d: adventurer played from position %d\n", player,adventurerPos);
        
        //playCard(adventurerPos, -1, -1, -1, &G);
        checkError(testAdventurer(&G,player,adventurerPos) == 0);
        
        if (ERROR) {
          errors++;
          break;
        }
        

        
      }
      //play another card, first one in hand that is not a coin
      for (j = 0; j < numHandCards(&G); j++){
        if (G.numActions <= 0){
          break;
        }
        card = handCard(j,&G);
        //if (VERBOSE)
        //  printf("%d: Trying to play card %d\n",player,card);
        result = playCard(j,-1,-1,-1,&G);
        if (result != -1){
          if (VERBOSE)
            printf("%d: Played card %d\n",player,card);
        }
      }
      i = 0;
      while(i<numHandCards(&G)){
          if (handCard(i, &G) == copper){
            playCard(i, -1, -1, -1, &G);
            money++;
          }
          else if (handCard(i, &G) == silver){
            playCard(i, -1, -1, -1, &G);
            money += 2;
          }
          else if (handCard(i, &G) == gold){
            playCard(i, -1, -1, -1, &G);
            money += 3;
          }
          i++;
        }
      //while (G.numBuys > 0 && money > 2){ //trying to use all buys, gets stuck when there are no more coins left to buy
        //if (VERBOSE)
          //printf("%d Money: %d\n",player,money);
        if (money >= 8) {
          buyCard(province, &G);
        }
        else if ((money >= 6) && (numAdventurers < 4)) {
          buyCard(adventurer, &G);
          numAdventurers++;
        }else if (money >= 6){
        buyCard(gold, &G);
          }
        else if (money >= 3){
        buyCard(silver, &G);
        }
      //}

      if (VERBOSE)
        printf("%d: end turn\n",player);
      endTurn(&G);

      alarm(0);
    }
    if (ERROR){
      printRandomTestResults(iteration,"CARD EFFECT");
    }
    else {
      printRandomTestResults(iteration,"");
    }

      
    resetError();
    if (VERBOSE)
      printf ("Player 0: %d\nPlayer 1: %d\n\n", scoreFor(0, &G), scoreFor(1, &G));
  } // end of main for
  printf("\tTotal Errors Found: %d\n",errors);
  printf(">>>>>>>>>>> Random Testing Adventure Complete <<<<<<<<<<<\n\n");
  return 0;
}
