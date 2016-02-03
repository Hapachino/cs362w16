/*
Testing Function: drawCard

Steps:
1. Check if deck is empty
	1.1 If deck is empty, shuffle discard pile to deck
		1.1.1 Check that deck count is greater than 0
	1.2 Set the discard pile count to 0
2. Add card to hand
3. Increment hand count
4. Decrement deck count

Things to check to ensure pass:
- Hand count + 1
- Deck count - 1
- Draw a card with empty draw deck
- Draw a card with all cards in hand
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
  //draw card should only affect player hand, player hand count, and player deck count
  test[player_hand] = 0;
  test[player_hand_count] = 0;
  test[player_deck_count] = 0;

  int i=0;
  int j = 0;
  int limit = 0;
  int total_deck_count = 0;
  int money = 0;
  int hand_count = 0;
  int offset = 0;


  signal(SIGALRM,timeout);
  signal(SIGSEGV,handle_segfault);

  printf("\n-------------------- Testing drawCard --------------------\n\n");
  for (i = 1; i <= 1; i++){ //for some fuzzing, set seed to i
    resetError();
    initTestGame(2, k, seed, &G);
    limit = 0;
    total_deck_count = 0;
    money = 0;
    hand_count = 0;

    if (whoseTurn(&G) == 0) {

      total_deck_count = totalDeckCount(0,&G);
      /***************************************************
                draw card with empty hand
      ***************************************************/
      printf("TEST1: Draw card with empty hand\n");
      alarm(2);
      previousG = G;
      checkError(drawCard(0,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1); //check nothing else got affected
      offset = 1; //should be 1 card more
      checkError(checkDeck(0,&previousG,&G) == 0);
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();


      /***************************************************
            tests drawing all the rest of cards in deck
      ***************************************************/
      printf("TEST2: Draw all cards in deck\n");
      alarm(2);
      //set limit for drawing all card in deck to hand
      if (MAX_HAND > total_deck_count){
        limit = total_deck_count - numHandCards(&G);
      }
      else {
        limit = MAX_HAND - numHandCards(&G);
      }

      hand_count = numHandCards(&G);
      for (j = 0; j < limit; j++) { //draw all rest of cards in deck
        previousG = G;
        checkError(drawCard(0,&G) == 0); 
        checkError(checkStates(&previousG,&G,test,0) == 1); 
      }
      checkError(checkHand(hand_count,limit, 0, &G) == 0); //should be offset by limit
      alarm(0);
      printResults();
      resetError();

      /***************************************************
      check that another card is not drawn when deck and 
      discard are empty
      ***************************************************/
      printf("TEST3: Draw card with all cards in hand\n");
      alarm(2);
      hand_count = numHandCards(&G);
      previousG = G;
      checkError(drawCard(0,&G)); //we want the -1 return value here
      checkError(checkStates(&previousG,&G,test,0) == 1);
      offset = 0; //hand count should not change, so no offset
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();

      /***************************************************
        check when all cards are in discard pile
      ***************************************************/
      printf("TEST4: Draw card when all cards in discard pile\n");
      alarm(2);
      test[player_deck] = 0; //deck should change due to reshuffle
      test[player_discard] = 0; //discard should change due to reshuffle
      test[player_discard_count] = 0; //discare count should change due to reshuffle
      discardAll(0,&G);
      offset = 1;
      hand_count = numHandCards(&G);
      previousG = G;
      checkError(drawCard(0,&G) == 0); 
      checkError(checkStates(&previousG,&G,test,0) == 1);
      checkError(checkDeck(0,&previousG,&G) == 0);
      checkError(checkHand(hand_count,offset,0,&G) == 0);
      alarm(0);
      printResults();
      resetError();
      
    }
    
  } // end of main for
  printf(">>>>>>>>>>> SUCCESS: Testing drawCard complete <<<<<<<<<<<\n\n");
  return 0;
}
