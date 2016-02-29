/* cardtest1.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Steward card in dominion.c
 *  Steward lets the player choose one of: +2 Cards; or +2 Coins;
 *  or trash 2 cards from your hand.
 * Attribution: This is based off the same steward card from class.
 *              I enhanced this with original state testing to make 
 *              sure we started right and with additional tests to make 
 *              sure other players were not effected from this test.
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
#define TESTCARD "Steward"

/**********************************************************
 * function: checkSteward
 * description: This function executes the Steward effect
 * against a copy of the game struct, I compare to make sure
 * the post play has increment the cards by two cards or by 
 * two coins and that the function can be executed.
 * input: the player number (0-3), a prefilled out struct
 * returns: 0 for success
 ***********************************************************/

int main(void)
{
  //define variables  
  int newCards = 0;
  int discarded = 0;
  int xtraCoins = 0;
  int shuffledCards = 0;
  int bonus = 0;

  //variable for returning pass or fail
  int result = 0;

  int i, j, m;
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
  int remove1 = 0;
  int remove2 = 0;
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

  // ----------- TEST 1: choice1: +2 cards --------------
  printf("TEST 1: choice1: +2 cards\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 1;
  cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 2;
  xtraCoins = 0;
  
  for( i=0; i < MAX_PLAYERS; i++) {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Test hand count = %d, Baseline hand count = %d\n", testG.handCount[i], G.handCount[i]);
      printf("Test deck count = %d, Baseline deck count = %d\n", testG.deckCount[i], G.deckCount[i]);
      printf("Test discard count = %d, Baseline discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
      printf("Test coins = %d, Baseline coins = %d\n\n", testG.coins, G.coins);
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
    
    if(testG.coins != G.coins)
    {
      #if (NOISY_TEST)
        printf("FAIL: coins don't match for player %d\n", i);
      #endif
      result = 1;
      #if (DEBUG)    
          assert(testG.coins == G.coins);
      #endif
    }
    #if (NOISY_TEST)
      printf("\n");
    #endif
  }

    // print out results
  if (result == 1) {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }

  // ----------- TEST 2: choice2: +2 coins --------------
  printf("TEST 2: choice2: +2 coins\n");

  // reset test flag
  result = 0;

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 2;
  cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 0;
  xtraCoins = 2;
  
  for( i=0; i < MAX_PLAYERS; i++) {
    #if (NOISY_TEST)
      printf("Player %d\n", i);
      printf("Test hand count = %d, Baseline hand count = %d\n", testG.handCount[i], G.handCount[i]);
      printf("Test deck count = %d, Baseline deck count = %d\n", testG.deckCount[i], G.deckCount[i]);
      printf("Test discard count = %d, Baseline discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
      printf("Test coins = %d, Baseline coins = %d\n\n", testG.coins, G.coins);
    #endif
  
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

    if(testG.coins != G.coins + xtraCoins){
      #if (NOISY_TEST)
        printf("FAIL: coins don't match for player %d\n", i);
      #endif
      result = 1;
      #if (DEBUG)    
        assert(testG.coins == G.coins + xtraCoins);
      #endif
    }
    
    #if (NOISY_TEST)
      printf("\n");
    #endif
  }

  // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }
  // ----------- TEST 3: choice3: trash two cards --------------

  printf("TEST 3: choice3: trash two cards\n");
  
  // reset test flag
  result = 0;
  
  choice1 = 3;

  // cycle through each eligible combination of 2 cards to trash
  for (i=1; i<G.handCount[thisPlayer]; i++) {
    for (j=i+1; j<G.handCount[thisPlayer]; j++) {

      G.hand[thisPlayer][0] = steward;
      G.hand[thisPlayer][1] = copper;
      G.hand[thisPlayer][2] = duchy;
      G.hand[thisPlayer][3] = estate;
      G.hand[thisPlayer][4] = feast;

      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));

      #if (NOISY_TEST)
        printf("starting cards: ");
      #endif
      for (m=0; m<testG.handCount[thisPlayer]; m++) {
        #if (NOISY_TEST)
          printf("(%d)", testG.hand[thisPlayer][m]);
        #endif
      }
      #if (NOISY_TEST)
        printf("; ");
      #endif

      choice2 = j;
      choice3 = i;
      remove1 = testG.hand[thisPlayer][i];
      remove2 = testG.hand[thisPlayer][j];
      
      cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

      #if (NOISY_TEST)
        printf("removed: (%d)(%d); ", remove1, remove2);
        printf("ending cards: ");
      #endif

      // tests that the removed cards are no longer in the player's hand
      for (m=0; m<testG.handCount[thisPlayer]; m++) {
        #if (NOISY_TEST)
          printf("(%d)", testG.hand[thisPlayer][m]);
        #endif
        #if (DEBUG)
          assert(testG.hand[thisPlayer][m] != remove1);
          assert(testG.hand[thisPlayer][m] != remove2);
        #endif
      }
      #if (NOISY_TEST)
        printf(", expected: ");
      #endif
      for (m=1; m<G.handCount[thisPlayer]; m++) {
        if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i] && G.hand[thisPlayer][m] != G.hand[thisPlayer][j]) {
          #if (NOISY_TEST)
            printf("(%d)", G.hand[thisPlayer][m]);
          #endif
        }
      }
      #if (NOISY_TEST)
        printf("\n\n");
      #endif

      if(testG.hand[thisPlayer][m] == remove1) {
        result = 1;
        #if (NOISY_TEST)
          printf("FAIL: remove from hand test for card 1\n");
        #endif
      }
      if(testG.hand[thisPlayer][m] == remove2) {
        result = 1;
        #if (NOISY_TEST)
          printf("FAIL: remove from hand test for card 2\n");
        #endif
      }

      // tests for the appropriate number of remaining cards
      newCards = 0;
      xtraCoins = 0;
      discarded = 3;
      
      if (i==1 && j==2) {
        #if (NOISY_TEST)
          printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
          printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
        #endif
      }
      #if (DEBUG)
        assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
        assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);
      #endif

      if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
        result = 1;
        #if (NOISY_TEST)
          printf("FAIL: Remaining cards in hand test\n");
        #endif
      }
      if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
        result = 1;
        #if (NOISY_TEST)
          printf("FAIL: Remaining cards in deck test\n");
        #endif
      }    
    }

  }

  // Test that the othe remaining players were not effected.
  #if (NOISY_TEST)
    printf("Testing remaining players\n\n");
  #endif
  for( i=1; i < MAX_PLAYERS; i++) {
  #if (NOISY_TEST)
    printf("Player %d\n", i);
    printf("Test hand count = %d, Baseline hand count = %d\n", testG.handCount[i], G.handCount[i]);
    printf("Test deck count = %d, Baseline deck count = %d\n", testG.deckCount[i], G.deckCount[i]);
    printf("Test discard count = %d, Baseline discard count = %d\n", testG.discardCount[i], G.discardCount[i]);
  #endif

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
  
  #if (NOISY_TEST)
    printf("\n");
  #endif
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