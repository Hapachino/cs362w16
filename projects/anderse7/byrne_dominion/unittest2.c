/* unittest2.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Is Game Over function in dominion.c
 *  isGameOver checks if the stack of Province cards is empty, it also
 * checks to see if the supplyCount is 0. In either case the game ends.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1
#define TESTCARD "isGameOver"

/**********************************************************
 * function: fillSupply
  * Description: Puts a card into each player's supply.
 * input: test struct
 * returns: 0 for success
 ***********************************************************/

//Puts a card into each card's supply
int fillSupply(struct gameState *testG)
{
  int i;

  for(i = 0; i < 25; i++)
  {
    testG->supplyCount[i] = 1;
  }

  return 0;
}

/**********************************************************
 * function: main
  * Description: Control test flow
 ***********************************************************/
int main(void)
{
  //define variables 

  //variable for returning pass or fail
  int result = 0;

  int i=0, j=0, m=0;
  int seed = 1000;
  int numPlayers = MAX_PLAYERS;
  
  
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
  
  for( i=0; i < MAX_PLAYERS; i++) 
  {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Verify starting coins: %d\n", G.coins);
      printf("Verify starting deckCount: %d\n", G.deckCount[i]);
      printf("Verify starting handCount: %d\n", G.handCount[i]);
      printf("Verify starting discardCount: %d\n\n", G.discardCount[i]);
    #endif
  }
  
  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
  
  // ----------- TEST 1: Test to see if there are any provice cards still in play ----
  printf("TEST 1: Test to see if there are any provice cards still in play\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  // place a province card in the test deck
  testG.supplyCount[province] = 1;

  //call game over and see what we get
  result = isGameOver(&testG);

  //test result
  #if (DEBUG)
    assert(result == 0);
  #endif
  
  if(result != 0){
    #if (NOISY_TEST)
      printf("FAIL: Game should not be over\n");
    #endif
    result = 1;
  }

  // now try the opposite case

  // place a province card in the test deck
  testG.supplyCount[province] = 0;

  //call game over and see what we get
  result = isGameOver(&testG);

  //test result
  #if (DEBUG)
    assert(result != 0);
  #endif
  
  if(result == 0){
    #if (NOISY_TEST)
      printf("FAIL: Game should be over\n");
    #endif
    result = 1;
  }

  // print out results
  if (result == 1) 
  {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

  // ----------- TEST 2: Test the state of the empty piles ----
  printf("TEST 2: Test the state of the empty piles\n");

  //reset test flag;
  result=0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  //All piles full
  fillSupply(&testG);
  
  //call game over and see what we get
  result = isGameOver(&testG);

  //test result
  #if (DEBUG)
    assert(result == 0);
  #endif
  
  if(result != 0){
    #if (NOISY_TEST)
      printf("FAIL: Game should not be over\n");
    #endif
    result = 1;
  }

  // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }

  // ----------- TEST 3: Test with one empty pile ----
  printf("TEST 3: Test with one empty pile\n");

  //reset test flag;
  result=0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  for(i = 0; i < 25; i++)
  {
    if(i != 3)  //Skip provinces - only looking at non province piles
    {
      fillSupply(&testG);
      testG.supplyCount[i] = 0;
      result = isGameOver(&testG);
      
    }
  }
  //test result
  #if (DEBUG)
    assert(result == 0);
  #endif
  
  if(result != 0){
    #if (NOISY_TEST)
      printf("FAIL: Game should not be over\n");
    #endif
    result = 1;
  }

  // print out results
  if (result == 1) {
    printf("Test 3 failed.\n");
  } else {
    printf("Test 3 passed.\n");
  }

  // ----------- TEST 4: Test with two empty piles ----
  printf("TEST 4: Test with two empty piles\n");

  //reset test flag;
  result=0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  for(i = 0; i < 25; i++)
  {
    if(i != 3 && j != 3 && i != j)
      {
        fillSupply(&testG);
        testG.supplyCount[i] = 0;
        testG.supplyCount[j] = 0;
        result = isGameOver(&testG);
        
      }
  }
  //test result
  #if (DEBUG)
    assert(result == 0);
  #endif
  
  if(result != 0){
    #if (NOISY_TEST)
      printf("FAIL: Game should not be over\n");
    #endif
    result = 1;
  }

  // print out results
  if (result == 1) {
    printf("Test 4 failed.\n");
  } else {
    printf("Test 4 passed.\n");
  }

    // ----------- TEST 5: Three empty piles should end game ----
  printf("TEST 5: Three empty piles should end game\n");

  //reset test flag;
  result=0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));

  for(i = 0; i < 25; i++)
  {
    for(j = 0; j < 25; j++)
    {
      for(m = 0; m < 25; m++)
      {
        if(i != j && i != m && j != m)
        {
          fillSupply(&testG);
          testG.supplyCount[i] = 0;
          testG.supplyCount[j] = 0;
          testG.supplyCount[m] = 0;
          result = isGameOver(&testG);
        }
      }
    }
  }
  //test result
  #if (DEBUG)
    assert(result == 1);
  #endif
  
  if(result != 1){
    #if (NOISY_TEST)
      printf("FAIL: Game should be over\n");
    #endif
    result = 1;
  }

  // print out results
  if (result == 1) {
    printf("Test 5 failed.\n");
  } else {
    printf("Test 5 passed.\n");
  }
  printf ("ALL TESTS COMPLETE.\n"); 

  exit(0);
}