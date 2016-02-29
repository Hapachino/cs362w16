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
#include <assert.h>

#define VERBOSE 1

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

  printf("\n-------------------- Random Testing Smithy --------------------\n\n");
  for (iteration = 1; iteration <= 1; iteration++){ 
    resetError();
    alarm(2);
    //initTestGame(2, k, seed, &G);
    assert(initializeGame(2,k,iteration,&G) == 0); 
    
    while (!isGameOver(&G)) {

      player = whoseTurn(&G);
      
      money = 0;
      smithyPos = -1;
      adventurerPos = -1;
      printHand(&G,player);
      for (i = 0; i < numHandCards(&G); i++) {
        //printf("checking %d\n",i);
        if (handCard(i, &G) == smithy){
          smithyPos = i;
        }
        else if (handCard(i, &G) == adventurer) {
          adventurerPos = i;
        }
      }
      
      if (smithyPos != -1) {
        previousG = G;
        if (VERBOSE) {
          printf("%d: smithy played from position %d\n", player,smithyPos);
        }
        //playCard(adventurerPos, -1, -1, -1, &G);
        checkError(testSmithy(&G,player,smithyPos) == 0);
        
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
    
      money += countTreasures(player,&G);
          printf("%d Money: %d\n",player,money);
        
        if (money >= 8) {
          result = buyCard(province, &G);
          if (result != -1)
            money -= 8;
          if (VERBOSE && result != -1){
            
            printf("%d: bought province\n",player);
          }
        }
        
        if (money >= 6 && player == 0) {
          result = buyCard(gold, &G);
          if (result != -1)
            money -= 6;
          if (VERBOSE && result != -1)
            printf("%d: bought gold\n",player);
        }
        if (money >= 6 && player == 1) {
          result = buyCard(adventurer, &G);
          if (result != -1)
            money -= 6;
          if (VERBOSE && result != -1)
            printf("%d: bought adventurer\n",player); 
        }
        if (money >= 4) {
          result = buyCard(smithy, &G);
          if (result != -1)
            money -= 4;
          if (VERBOSE && result != -1)
            printf("%d: bought smithy\n",player);
          numSmithies++;
        }
        if (money >= 3 && player == 0) {
          result = buyCard(silver, &G);
          if (result != -1)
            money -= 3;
          if (VERBOSE && result != -1)
            printf("%d: bought silver\n",player);
          
        }
        if (money >= 3 && player == 1) {
          result = buyCard(village, &G);
          if (result != -1)
            money -= 3;
          if (VERBOSE && result != -1)
            printf("%d: bought village\n",player);
        }
        
        
      //}
      if (VERBOSE)
        printf("%d: end turn\n",player);
      endTurn(&G);
      exit(0);
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
