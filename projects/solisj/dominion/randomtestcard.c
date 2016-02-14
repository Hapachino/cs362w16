/********************************************************************************************************************************************************
*** Filename: randomtestcard.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 2/14/2015
*** Assignment 4
*** Description: Unit test for:  case great_hall in cardEffect()
*** Business requirements:
***  1. Adds exactly 1 card to the player's hand
***  2. Adds exactly 1 action to the game state 
***  3. The played great_hall is discarded from the player's hand
***
***  Testing:
***       1. Test that player's handcount is the same(1 card added, but great_hall is discarded)
***       2. Test that playedCardsCount has increased by 1
***       3. Test that number of actions has increased by 1
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* randomtestcard: randomtestcard.c dominion.o rngs.o
*      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*
********************************************************************************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main()
{
     int i, j, l;
     int r;
     int player;
     int numPlayer;
     int handPos;
     int card;
     int seed;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };


     struct gameState prevState; //untouched game state to compare with after running tests
     struct gameState postState; //game state that will be used for tests

     srand(time(NULL)); //seed random number generator

     //testing variables
     int numTests = 2000; //how many test iterations to run.
     int testResult;
     int testCase1Passed = 0;
     int testCase1Failed = 0;
     int testCase2Passed = 0;
     int testCase2Failed = 0;
     int testCase3Passed = 0;
     int testCase3Failed = 0;


     printf("======================================================\r\n");
     printf(" Beginning random testing for great_hall cardEffect()\r\n");
     printf("=======================================================\r\n");


     for (i = 0; i < numTests; i++)
     {
          //randomize intializeGame options
          seed = rand(); //random seed
          numPlayer = (rand() % (3)) + 2; //random amount of players 2-4

          //intialize the game
          memset(&prevState, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &prevState); // initialize a new game

          //randomize player's deck, discard, and hand. 
          for (player = 0; player < numPlayer; player++)
          {
               //Credit: betterTestDrawCard.c
               prevState.deckCount[player] = floor(Random() * MAX_DECK);
               prevState.discardCount[player] = floor(Random() * MAX_DECK);
               prevState.handCount[player] = floor(Random() * MAX_HAND);
               
               //fill in player's deck, discard, and hand with random cards
               for (j = 0; j < prevState.deckCount[player]; j++)
               {
                    prevState.deck[player][j] = floor(Random() *treasure_map);
               }

               for (j = 0; j < prevState.discardCount[player]; j++)
               {
                    prevState.discard[player][j] = floor(Random() *treasure_map);
               }

               for (j = 0; j < prevState.handCount[player]; j++)
               {
                    prevState.hand[player][j] = floor(Random() *treasure_map);
               }

               //check to see if great_hall is on the player's hand
               handPos = -1;
               for (j = 0; j < prevState.handCount[player]; j++)
               {
                    card = prevState.hand[player][j];
                    if (card == great_hall)
                    {
                         handPos = j;
                         break;
                    }
               }

               if (handPos == -1)//great_hall is not in hand
               {
                    //insertgreat_hall into random hand pos
                    handPos = floor(Random() *prevState.handCount[player]);
                    prevState.hand[player][handPos] = great_hall;
               }

          }

          player = rand() % numPlayer; //choose a random player
          prevState.whoseTurn = player;
          memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on
          l = cardEffect(great_hall, 0, 0, 0, &postState, handPos, 0);

          //Test Case 1: Test that player's handcount is the same(1 card added, but great_hall is discarded)
          testResult = postState.handCount[player];

          if (testResult == prevState.handCount[player])
          {
               testCase1Passed++;
          }
          else//failed
          {
               testCase1Failed++;
#if (NOISY_TEST == 1)
               printf("Iteration #%d: Testing that player[%d] handCount has remained the same has failed.\r\n", i, player);
               printf("Previous handCount = %d, Previous deckCount = %d, Previous discardCount = %d, \r\n", prevState.handCount[player], prevState.deckCount[player], prevState.discardCount[player]);
               printf("Post handCount = %d, Post deckCount = %d, Post discardCount = %d, \r\n", postState.handCount[player], postState.deckCount[player], postState.discardCount[player]);
#endif
          }


          //Test Case 2: that playedcardsCount has increased by 1
          testResult = postState.playedCardCount;

          if (testResult == prevState.playedCardCount + 1) //passed
          {
               testCase2Passed++;
          }
          else//failed
          {
               testCase2Failed++;

#if (NOISY_TEST == 1)
               printf("Iteration #%d: Testing that playedcardsCount has increased by 1 has failed.\r\n", i);
               printf("prevState.playedCardCount = %d, postState.playedCardCount = %d, expected = %d, \r\n", prevState.playedCardCount, postState.playedCardCount, prevState.playedCardCount + 1);
#endif
          }


          //Test case 3: Test that number of actions has increased by 1
          testResult = postState.numActions;

          if (testResult == prevState.numActions + 1) //passed
          {
               testCase3Passed++;
          }
          else//failed
          {
               testCase3Failed++;
#if (NOISY_TEST == 1)
               printf("Iteration #%d: Testing that number of actions has increased by 1 has failed.\r\n", i);
               printf("prevState.numActions = %d, postState.numActions = %d, expected = %d, \r\n", prevState.numActions, postState.numActions, prevState.numActions + 1);
#endif
          }

     }//end numTests loop

     printf("Random testing for great_hall cardEffect() completed.\r\n");
     printf("=================================================\r\n");
     printf("Tests that player's handcount is the same: \r\n");
     printf("%d out of %d tests passed!\r\n", testCase1Passed, testCase1Passed + testCase1Failed);
     printf("%d out of %d tests failed!\r\n", testCase1Failed, testCase1Passed + testCase1Failed);

     printf("Tests that that playedcardsCount has increased by 1: \r\n");
     printf("%d out of %d tests passed!\r\n", testCase2Passed, testCase2Passed + testCase2Failed);
     printf("%d out of %d tests failed!\r\n", testCase2Failed, testCase2Passed + testCase2Failed);

     printf("Tests that number of actions has increased by 1: \r\n");
     printf("%d out of %d tests passed!\r\n", testCase3Passed, testCase3Passed + testCase3Failed);
     printf("%d out of %d tests failed!\r\n", testCase3Failed, testCase3Passed + testCase3Failed);


     return 0;
}