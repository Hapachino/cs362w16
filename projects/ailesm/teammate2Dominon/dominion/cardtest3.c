/* cardtest3.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the Cut Purse card in dominion.c
 *           +2 Coins, Each other player discards a Copper card 
 *           (or reveals a hand with no Copper).
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
#define TESTCARD "Cut Purse"

/**********************************************************
 * function: checkCutPurse
  * Description: Unit test for the Cut Purse card in dominion.c
 *           +2 Coins, Each other player discards a Copper card 
 *           (or reveals a hand with no Copper).
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

  int i, j, m;
  int handpos = 0;
  int choice1 = 0;
  int choice2 = 0;
  int choice3 = 0;
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
  
  // ----------- TEST 1: +2 coins --------------
  printf("TEST 1: +2 coins\n");

  // copy the game state to a test case
  memcpy(&testG, &G, sizeof(struct gameState));
  
  choice1 = 2;
  cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

  newCards = 0;
  xtraCoins = 2;
  
  for( i=0; i < MAX_PLAYERS; i++) 
  {
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

    if(testG.coins != G.coins + xtraCoins)
    {
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
  if (result == 1) 
  {
    printf("Test 1 failed.\n");
  } else {
    printf("Test 1 passed.\n");
  }
  // ----------- TEST 2: discard a copper card --------------

  printf("TEST 2: discard a copper card\n");
  
  // reset test flag
  result = 0;
  int numberInHand = 0;
  int coppers[4]= {0,0,0,0};
  int post_coppers[4]= {0,0,0,0};
  int it=0;

  //set cards for the rest of the players
  for(m=1; m< MAX_PLAYERS; m++)
  {
    G.whoseTurn += m;
    for (it = 0; it < 5; it++)
    {
      drawCard(G.whoseTurn, &G);
    }
  }

  // cycle through each players hand to see how many coppers they have
  for (i = 0; i < MAX_PLAYERS; i++) 
  {
    numberInHand = G.handCount[i];
    #if (NOISY_TEST)
      printf("player %d\n", i);
      printf("numberInHand %d\n", numberInHand);
    #endif
    for (j=0; j< numberInHand; j++)
    {
      #if (NOISY_TEST)
        printf("card %d: ", j);
        printf("card value %d\n", G.hand[i][j]);
      #endif
      if(G.hand[i][j] == 4)
      {
        coppers[i]++;
      }
    }
    #if (NOISY_TEST)
      printf("Number of coppers in hand in G: %d\n", coppers[i]);
    #endif
  }
    #if (NOISY_TEST)
      printf("\n");
    #endif
    //reset back to player 0
    G.whoseTurn = 0;
    
    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    //execute the card
    cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);

    #if (NOISY_TEST)
      printf("Post test results\n");
    #endif
 //reset value for loop
  numberInHand = 0;
  for (i = 0; i < MAX_PLAYERS; i++) 
  {
    numberInHand = testG.handCount[i];
    #if (NOISY_TEST)
      printf("test player %d\n", i);
      printf("numberInHand %d\n", numberInHand);
    #endif
    for (j=0; j< numberInHand; j++)
    {
      #if (NOISY_TEST)
        printf("card %d: ", j);
        printf("card value %d\n", testG.hand[i][j]);
      #endif
      if(testG.hand[i][j] == 4)
      {
        post_coppers[i] += 1;
      }
    }
    #if (NOISY_TEST)
      printf("Number of coppers in hand in G: %d\n", post_coppers[i]);
    #endif
  }
    #if (NOISY_TEST)
      printf("\n");
    #endif

    if (coppers[0] != post_coppers[0])
    {
      result = 1;
      #if (NOISY_TEST)
        printf("post coppers should be equal for the first player\n");
      #endif
    }

    for(i=1; i < MAX_PLAYERS; i++)
    {
      if (coppers[i] != (post_coppers[i] +1))
      {
        result = 1;
        #if (NOISY_TEST)
          printf("post coppers should be 2 less than pre\n");
        #endif
      }
    }

  // print out results
  if (result == 1) {
    printf("Test 2 failed.\n");
  } else {
    printf("Test 2 passed.\n");
  }


  printf ("ALL TESTS COMPLETE.\n"); 

  exit(0);
}