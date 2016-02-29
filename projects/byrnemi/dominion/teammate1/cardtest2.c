/* cardtest2.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Smithy card in dominion.c
 *  Smithy lets the player draw three cards.
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
#define TESTCARD "Smithy"

/**********************************************************
 * function: checkSmithy
 * description: This function executes the Smithy effect
 * against a copy of the game struct, I compare to make sure
 * the post play has increment the cards by three cards and that
 * the function can be executed.
 * input: the player number (0-3), a prefilled out struct
 * returns: 0 for success
 ***********************************************************/
int main(void)
{
  //define variables  
  int newCards = 0;
  int xtraCoins = 0;
  int bonus = 0;

  //variable for returning pass or fail
  int result = 0;

  int i=0, j=0, m=0;
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

  // ----------- TEST 1: +3 cards --------------
  printf("TEST 1: +3 cards\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 3;
  xtraCoins = 0;
  
  for( i=0; i < MAX_PLAYERS; i++) {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Test hand count = %d, Baseline hand count = %d\n", testG.handCount[i], G.handCount[i]);
      printf("Test deck count = %d, Baseline deck count = %d\n", testG.deckCount[i], G.deckCount[i]);
      printf("Test discard count = %d, Baseline discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
    #endif
    if(i == thisPlayer)
    {
      if(testG.handCount[i] != G.handCount[i] + newCards)
      {
        #if (NOISY_TEST)
          printf("FAIL: Hand counts didn't increment properly\n");
        #endif
        result = 1;
      }
      
      if(testG.deckCount[i] != G.deckCount[i] - newCards)
      {
        #if (NOISY_TEST)
          printf("FAIL: Deck counts didn't decrement properly\n");
        #endif
        result = 1;
      }

      if(testG.discardCount[i] != G.discardCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: discard counts don't match\n");
        #endif
        result = 1;
      }

      #if (DEBUG)    
        assert(testG.handCount[i] == G.handCount[i] + newCards);
        assert(testG.deckCount[i] == G.deckCount[i] - newCards);
        assert(testG.discardCount[i] == G.discardCount[i]);
      #endif

    }else 
    {
      if(testG.handCount[i] != G.handCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: Hand counts don't match\n");
        #endif
        result = 1;
      }
      
      if(testG.deckCount[i] != G.deckCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: Deck counts don't match\n");
        #endif
        result = 1;
      }

      if(testG.discardCount[i] != G.discardCount[i])
      {
        #if (NOISY_TEST)
          printf("FAIL: discard counts don't match\n");
        #endif
        result = 1;
      }

      #if (DEBUG)    
        assert(testG.handCount[i] == G.handCount[i]);
        assert(testG.deckCount[i] == G.deckCount[i]);
        assert(testG.discardCount[i] == G.discardCount[i]);
      #endif      

    }
  }
    // print out results
  if (result == 1) {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

  // ----------- TEST 2: Remove Smithy card --------------
  printf("TEST 2: Remove Smithy card\n");

  //reset error flag
  result = 0;

    // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);


  //Verify Smithy card is not in player's hand
  for(j = 0; j < testG.handCount[thisPlayer]; j++)
  {
    if(testG.hand[thisPlayer][j] == smithy)
    {
      #if (NOISY_TEST)
        printf("FAIL: Smithy still in player's hand.\n");
      #endif
      
      result=1;
    }
  }

  // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }

  // ----------- TEST 3: Verify supply count is unchanged --------------
  printf("TEST 3: Verify supply count is unchanged\n");

  //reset error flag
  result = 0;

    // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

  for(m = 0; m < 25; m++)
  {
    if(testG.supplyCount[m] != G.supplyCount[m])
    {
      #if (NOISY_TEST)
        printf("FAIL: Supply counts changed by Smithy cardEffect.\n");
      #endif
      
      result = 1;
    }
  }
  // print out results
  if (result == 1) {
    printf("Test 3 failed.\n");
  } else {
    printf("Test 3 passed.\n");
  }
  
  printf ("ALL TESTS COMPLETE.\n"); 

  exit(0);
}