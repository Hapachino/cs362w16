#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>


int main (int argc, char** argv) {
  struct gameState G;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};


  

  int money = 0;
  int smithyPos = -1;
  int adventurerPos = -1;
  int i=0;
  int player;
  int numSmithies = 0;
  int numAdventurers = 0;
  int iteration;
  int errors = 0;
  printf("\n-------------------- Random Testing Smithy --------------------\n\n");
  for (iteration = 1; iteration <= 1000; iteration++){
    resetError();
    assert(initializeGame(2, k, iteration, &G) == 0);
    numSmithies = 0;
    while (!isGameOver(&G)) {
      player = whoseTurn(&G);
      money = 0;
      smithyPos = -1;
      adventurerPos = -1;
      for (i = 0; i < numHandCards(&G); i++) {
        if (handCard(i, &G) == copper)
      money++;
        else if (handCard(i, &G) == silver)
      money += 2;
        else if (handCard(i, &G) == gold)
      money += 3;
        else if (handCard(i, &G) == smithy)
      smithyPos = i;
        else if (handCard(i, &G) == adventurer)
      adventurerPos = i;
      }

      if (whoseTurn(&G) == 0) {
        if (smithyPos != -1) {
          checkError(testSmithy(&G,player,smithyPos) == 0);
          if (ERROR){
            errors++;
            break;
          }
        }
      money = 0;
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
        if (money >= 8) {
          buyCard(province, &G);
        }
        else if (money >= 6) {
          buyCard(gold, &G);
        }
        else if ((money >= 4) && (numSmithies < 4)) {
          buyCard(smithy, &G);
          numSmithies++;
        }
        else if (money >= 3) {
          buyCard(silver, &G);
        }

        endTurn(&G);
      }
      else {
        if (adventurerPos != -1) {
          playCard(adventurerPos, -1, -1, -1, &G);
          money = 0;
          i=0;
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
        }

        if (money >= 8) {
          buyCard(province, &G);
        }
        else if ((money >= 6) && (numAdventurers < 2)) {
          buyCard(adventurer, &G);
          numAdventurers++;
        }else if (money >= 6){
  	    buyCard(gold, &G);
          }
        else if (money >= 3){
  	    buyCard(silver, &G);
        }

        endTurn(&G);
      }
    } // end of While
    if (ERROR){
      printRandomTestResults(iteration,"CARD EFFECT");
    }
    else {
      printRandomTestResults(iteration,"");
    }
  }
  printf("\tTotal Errors Found: %d\n",errors);
  printf(">>>>>>>>>>> Random Testing Adventure Complete <<<<<<<<<<<\n\n");

  return 0;
}
