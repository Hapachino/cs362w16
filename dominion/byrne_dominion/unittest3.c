/* unittest3.c
 * Author: Eric Anderson
 * Class: CS362w16
 * Description: Unit test for the playCard function in dominion.c
 *  Play Card gets the card played and checks it to see if the 
 *  selected card is an action, it then "palys" the card through 
 *  cardEffect. Then it reduces number of actions and ends by 
 *  updating coins (Treasure cards may be added with card draws).
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 0

/**********************************************************
 * function: checkPlayCard
 * description: This function executes the checkPlayCard function
 * against several conditions conditions;
 *    checks if the state->phase != 0
 *    checks if the state->numActions < 1
 *    check if selected card is an adventurer or treasure_map
 *    checks if playing the card failed
 * in any of these cases the function will return a -1.  This tests for both cases.
 * input: the player number (0-3), a prefilled out struct and a card number
 * returns: result, 0 for success, 1 for failure
 ***********************************************************/
int checkPlayCard(int handPos, int c1, int c2, int c3, struct gameState *post)
{
  //define variables
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int card = handCard(handPos, post);
  int coin_bonus = 0;
  int r = 0;
  int result = 0;

  // execute the playCard action against the "pre" version of the struct
  // this is the same content as in the playCard code in dominion.c
  r = playCard(handPos, c1, c2, c3, post);
  
  // test 1: Check for the four conditions and make sure we got a -1
  if (pre.phase != 0 || pre.numActions < 1 || card < adventurer || card > treasure_map ||
      cardEffect(card, c1, c2, c3, &pre, handPos, &coin_bonus) < 0) 
  {
#if (DEBUG)
    assert (r == -1);
#endif

#if (NOISY_TEST) 
    printf("The assert r==1 passed");
#endif

  }
  else
  {
    // test 2: Everything worked and so we should get a 0
    pre.numActions--;
    updateCoins(pre.whoseTurn, &pre, coin_bonus);
#if (DEBUG)
    assert (r == 0);
#endif

#if (NOISY_TEST) 
    printf("The assert r == 0 passed");
#endif
  }
  

#if (DEBUG)
  //test3: pre and post should look the same if the function works all the time
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
#endif

  if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
#if (NOISY_TEST) 
    printf("pre and post don't match");
#endif
    result = 1;
  }

  return result;
}

int main()
{
  //define variables
  int i, n,p, handPos, c1, c2, c3;
  int result = 0;
  
  //define a gamestate
  struct gameState G;
  printf ("Testing playCard with Random Tests\n");
  SelectStream(2);
  PutSeed(3);

  //Loop through players, decks and hands to fill the struct
  // and initiate game play.  
  for (n = 0; n < 2000; n++)
  {
    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    handPos = floor(Random() * 15);//number of cards in hand
    c1 = floor(Random() * 10);//kingdom card index
    c2 = floor(Random() * 10);
    c3 = floor(Random() * 10);
    p = floor(Random() * 2);
    
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    G.phase = floor(Random() * 3);
    G.numActions = floor(Random() * 16);
    G.whoseTurn = floor(Random() * 2);
    //run unit test.
    result = checkPlayCard(handPos, c1, c2, c3, &G);
  }

  // print out results
  if (result == 1) {
    printf("playCard tests failed.\n");
  } else {
    printf("playCard tests passed.\n");
  }
  
  printf ("RANDOM TESTS COMPLETE.\n");

  exit(0);
}