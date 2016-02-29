/**
 ** Author: Tim Robinson
 ** Tested Function: discardCard
 ** Description: The main function in this file tests if the discardCard
 ** function behaves as expected and changes a gameState object as expected.
 ** 
 ** Once passed, unit test 1 calls all of the other test functions:
 **   test2, test3, test4 <-- Unit tests
 **   cardtest1, cardtest2, cardtest3, cardtest4 <-- Card tests
 **
 ** Add the following to your makefile:
  
  cardtests: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
    gcc -c -g cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o $(CFLAGS)
  
  unittests: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
    gcc -c -g unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o $(CFLAGS)
  
  alltests: unittests cardtests
    gcc -o alltests -g unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o $(CFLAGS)
 
  unittestresults.out: alltests
    ./alltests > unittestresults.out 2>&1
    gcov dominion.c -b >> unittestresults.out
    gcov dominion.c -f >> unittestresults.out
**
** In order to compile and run the test suite simply type:
**
**    make unittestresults.out
**
** The results of the test suite including test coverage information can then 
** be found in unittestresults.out.
**
** The user can compile and run either the card tests or the unit tests by 
** themselves. The user can also compile and run all of the tests together.
**
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

#define MAX_HAND_TEST 5
#define TEST_FUNC "discardCard"

int main() {

	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
	int max_hand = 5;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};
  int pre_hand[MAX_HAND_TEST];

  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));
  
  printf("---------------- Testing %s Function ----------------\n", TEST_FUNC);

  // For each trash flag
  int trash;
  for (trash = 0; trash <= 1; trash++)
  {
    if (trash)
    {
      printf("Discard to trash, ");
    } else
    {
      printf("Discard to discard pile, ");
    }
  	// For each player
    int player;
  	for (player = 0; player <=1; player++)
  	{
      printf("for player %d, ", player);
  		// For each possible hand size
      int hand_size;
  		for (hand_size = 1; hand_size <= MAX_HAND_TEST; hand_size++)
  		{
        printf("for hand size %d, ", hand_size);
  			state.handCount[player] = hand_size;
        pre.handCount[player] = hand_size;
  			// For each possible hand position
        int hand_pos;
        for (hand_pos = 0; hand_pos < hand_size; hand_pos++)
  			{
          printf("from hand position %d\n", hand_pos);
          discardCard(hand_pos, player, &state, trash);

          if (trash == 0)
          {
            // Check the playedCardCount
            assert(state.playedCardCount == pre.playedCardCount + 1);
          } else
          {
            // Check the playedCardCount
            assert(state.playedCardCount == pre.playedCardCount);
          }

				  // If it is the last hand position
          if (hand_pos == hand_size - 1) 
          {
  				  printf("Discarding card from last hand position\n");
            
            // Did the order of the cards not change?
  			    assert(strncmp(state.hand[player], pre.hand[player], hand_size - 1) == 0);
          
          // Else if it is the last card
          } else if (hand_size == 1)
          {
            printf("Discarding final card in hand\n");
  				 
            // Is there no hand?
            assert(state.handCount[player] == 0);

          } else 
          {
            printf("Filling discarded card's hole in hand\n");

  			    // Else did we correctly replace the discarded card?
            assert(state.hand[player][hand_pos] == pre.hand[player][hand_size - 1]);
          }
  			  
          // Did handCount decrease by 1 relative to hand size?
          assert(state.handCount[player] == pre.handCount[player] - 1);

          // Copy our current gamestate to negate discard
          memcpy(&state, &pre, sizeof(struct gameState));
          printf("Passed\n");
  			}
  		}	
  	}
  }

  printf("\nUNIT TEST 1 PASSED.\n\n");

  int res2 = test2();
  int res3 = test3();
  int res4 = test4();

  int cres1 = cardtest1();
  int cres2 = cardtest2();
  int cres3 = cardtest3();
//  int cres4 = cardtest4();


	return 0;
}
