/* cardtest4.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Adventurer card in dominion.c
 * Action Sequence: Reveal cards until two treasure cards are revealed.
 * Add them to your hand, then discard the other revealed cards.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1
#define TESTCARD "Adventurer"

/**********************************************************
 * function: checkplayAdventurer
 * description: This function executes the adventurer effect
 * against a copy or the game struct, I compare to make sure
 * the post play has increment the cards by two treasure cards
 * and that the function can be executed.
 * input: the player number (0-3), a prefilled out struct
 * returns: 0 for success
 ***********************************************************/

int main(void)
{
  
   //define variables  
  int bonus = 0;
  int result = 0; //variable for returning pass or fail
  int i;
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int seed = 1000;
  int numPlayers = MAX_PLAYERS;
  int thisPlayer = 0;
  
  // game state struct
  struct gameState G;

  // struct to compare to normal game state
  struct gameState testG;

  //define a array of cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};
  
  /************************************************************************* 
   * Initialize the game normally.  Each player starts
   * Each player starts with a deck of 
   *   7 Coppers
   *   3 Estates.
   * 
   * Victory cards: 
   *   12 Estates
   *   12 Duchies
   *   12 Provinces.

   * Treasures: 
   *   60 Coppers (minus the cards players start with), 
   *   40 Silvers, 
   *   30 Golds.
   *
   * Curses:
   *   30 Curses for four players.
   *
   ****************************************************************************/
  
  // initialize a baseline game state
  initializeGame(numPlayers, k, seed, &G);
  
  // Verify that the default structure in as expected for a game
  #if (NOISY_TEST)
    printf("Testing Baseline state of game\n");
    printf("Verify 12 Estate cards: %d\n", G.supplyCount[1]);
    printf("Verify 12 Duchies cards: %d\n", G.supplyCount[2]);
    printf("Verify 12 Province cards: %d\n\n", G.supplyCount[3]);
  #endif
  
  for( i=0; i < MAX_PLAYERS; i++) {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Verify starting coins: %d\n", G.coins);
      printf("Verify starting deckCount: %d\n", G.deckCount[i]);
      printf("Verify starting handCount: %d\n", G.handCount[i]);
      printf("Verify starting discardCount: %d\n\n", G.discardCount[i]);
    #endif
  }
  
 printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  // ----------- TEST 1: Hand count is incremented by one --------------
  printf("TEST 1: Hand count is incremented by one\n");

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Test that handCount is incremented by one
  #if (DEBUG)
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1);
  #endif
  if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 1)
  {
    #if (NOISY_TEST)
      printf("FAIL: Expected Value: %d  Actual Value: %d\n", G.handCount[thisPlayer] + 1, testG.handCount[thisPlayer]);
    #endif
    result=1;
  }

    // print out results
  if (result == 1) {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

 // ----------- TEST 2: deck count is decremented by at least two --------------
  printf("TEST 2: deck count is decremented by at least two\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Test that deck count is decremented by at least two
  #if (DEBUG)
    assert(testG.deckCount[thisPlayer] <= G.deckCount[thisPlayer] - 2);
  #endif
  if(testG.deckCount[thisPlayer] > G.deckCount[thisPlayer] - 2)
  {
    #if (NOISY_TEST)
      printf("FAIL: Expected Value: <= %d  Actual Value: %d\n", G.deckCount[thisPlayer] - 2, testG.deckCount[thisPlayer]);
    #endif
    
    result=1;
  }

      // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }
  
 // ----------- TEST 3: two treasure cards (coins) are added to the hand --------------
  printf("TEST 3: two treasure cards (coins) are added to the hand\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  // see if the two cards are treasure cards
  if((testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold) &&
    (testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver || 
    testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold))
  {
    #if (NOISY_TEST)
      printf("We got 2 treasure cards: %d, %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], 
        testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]);
    #endif
  }
  else
  {
    result=1;
  }

  // print out results
  if (result == 1) {
    printf("Test 3 failed.\n");
  } else {
    printf("Test 3 passed.\n");
  }

 // ----------- TEST 4: Test discard of other revealed cards --------------
  printf("TEST 4: Test discard of other revealed cards\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //test discard
  #if (DEBUG)
    assert((testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) == (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 2));
  #endif
  if((testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) != (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 2))
  {
    #if (NOISY_TEST)
      printf("FAIL: Expected Value: %d  Actual Value: %d\n", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], 
        G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - 2);
    #endif
      result=1;
  }

  // print out results
  if (result == 1) {
    printf("Test 4 failed.\n");
  } else {
    printf("Test 4 passed.\n");
  }

  // ----------- TEST 5: Make sure no other players are effected --------------
  printf("TEST 5: Make sure no other players are effected\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Testing Other Players hand and deck counts
  for(i = 1; i < MAX_PLAYERS; i++)
  {
    #if (DEBUG)
      assert(testG.handCount[i] == G.handCount[i]);
      assert(testG.deckCount[i] == G.deckCount[i]);
    #endif
    
    if(testG.handCount[i] != G.handCount[i])
    {
      #if (NOISY_TEST)
        printf("Expected handcount was: %d Actual value: %d\n", testG.handCount[i], G.handCount[i]);
      #endif
      result=1;
    }

    if(testG.deckCount[i] != G.deckCount[i])
    {
      #if (NOISY_TEST)
        printf("Expected deckCount was: %d Actual value: %d\n", testG.deckCount[i], G.deckCount[i]);
      #endif
      result=1;
    }
  }
  
  // print out results
  if (result == 1) {
    printf("Test 5 failed.\n");
  } else {
    printf("Test 5 passed.\n");
  }

  // ----------- TEST 5: Make sure no other players are effected --------------
  printf("TEST 5: Make sure no other players are effected\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  //Testing Other Players hand and deck counts
  for(i = 1; i < MAX_PLAYERS; i++)
  {
    #if (DEBUG)
      assert(testG.handCount[i] == G.handCount[i]);
      assert(testG.deckCount[i] == G.deckCount[i]);
    #endif
    
    if(testG.handCount[i] != G.handCount[i])
    {
      #if (NOISY_TEST)
        printf("Expected handcount was: %d Actual value: %d\n", testG.handCount[i], G.handCount[i]);
      #endif
      result=1;
    }

    if(testG.deckCount[i] != G.deckCount[i])
    {
      #if (NOISY_TEST)
        printf("Expected deckCount was: %d Actual value: %d\n", testG.deckCount[i], G.deckCount[i]);
      #endif
      result=1;
    }
  }
  
  // print out results
  if (result == 1) {
    printf("Test 6 failed.\n");
  } else {
    printf("Test 6 passed.\n");
  }

  // ----------- TEST 7: Test that the supply is unchanged --------------
  printf("TEST 7: Test that the supply is unchanged\n");

  result=0; //reset result flag

  //Set control state for comparison, call cardEffect
  memcpy(&testG, &G, sizeof(struct gameState));
  
  cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

  for(i = 0; i < 25; i++)
  {
    #if (DEBUG)
      assert(testG.supplyCount[i] == G.supplyCount[i]);
    #endif
    
    if (testG.supplyCount[i] != G.supplyCount[i])
    {
      #if (NOISY_TEST)
        printf("Expected supplyCount was: %d Actual value: %d\n", testG.supplyCount[i], G.supplyCount[i]);
      #endif
      result=1;
    }
  }
  
  // print out results
  if (result == 1) {
    printf("Test 6 failed.\n");
  } else {
    printf("Test 6 passed.\n");
  }

  printf ("ALL TESTS COMPLETE.\n");

  return 0;
}