/********************************************************************************************************************************************************
*** Filename: randomtestadventurer.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 2/14/2015
*** Assignment 4
*** Description: random tester for: playAdventurer()- refactored version from assignment 2 (Includes deliberate bug - Info can be found in refactor.c)
*** Business requirements:
***  1. Draw cards from player's own deck and discard pile until two treasure cards have been added to hand.
***  2. All cards drawn that were not the two treasure cards, must be added back to the player's discard pile
***
***  Testing:
***       1. Check that player's handcount increased by 2
***       2. Check that the two treasure cards were added to player's hand
***       3. No other game state changes
***
*** References: testUpdateCoins.c, cardTest4.c, and bettertestdrawcard.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
*      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
#define NOISY_TEST 0

int main()
{
     int i, j;
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


     printf("==============================================\r\n");
     printf(" Beginning random testing for playAdventurer()\r\n");
     printf("==============================================\r\n");


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

               //check to see if adventurer is on the player's hand
               int foundAdventurer = -1;
               for (j = 0; j < prevState.handCount[player]; j++)
               {
                    card = prevState.hand[player][j];
                    if (card == adventurer)
                    {
                         foundAdventurer = j;
                         break;
                    }
               }

               if (foundAdventurer == -1)//adventurer is not in hand
               {
                    //insert adventurer into random hand pos
                    handPos = floor(Random() *prevState.handCount[player]);
                    prevState.hand[player][handPos] = adventurer;
               }

               /*
               //insert two treasure cards randomly to assure at least two treasure cards in deck
               //make sure second handPos1 != handPos2
               int handPos1 = floor(Random() *prevState.deckCount[player]);
               int handPos2 = floor(Random() *prevState.deckCount[player]);

               while (handPos1 == handPos2)
               {
                    handPos2 = (floor(Random() *prevState.deckCount[player])) + 1;
               }

               //randompick which treasure card to insert
               prevState.deck[player][handPos1] = (rand() % 3) + 4; //random number between 4 and 6. (4 = copper, 5 = silver, 6 = gold)
               prevState.deck[player][handPos2] = (rand() % 3) + 4; //random number between 4 and 6. (4 = copper, 5 = silver, 6 = gold)

               //*/

          }


          player = rand() % numPlayer; //choose a random player
          memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on
          playAdventurer(player, &postState);


          //Check that exactly 2 cards were indeed added to current player's hand by comparing handCount value 
          //=====================================================================================================
          testResult = postState.handCount[player];

          if (testResult == prevState.handCount[player] + 2)
          {
               testCase1Passed++;
          }
          else//failed
          {
               testCase1Failed++;
#if (NOISY_TEST == 1)
               printf("Iteration #%d: Testing that player[%d] handCount has increased by 2 has failed.\r\n", i, player);
               printf("Previous handCount = %d, Previous deckCount = %d, Previous discardCount = %d, \r\n", prevState.handCount[player], prevState.deckCount[player], prevState.discardCount[player]);
#endif
          }


          //Check that the hand has had two treasure cards added
          //=======================================================
          int prevTreasureCardCount = 0;
          int postTreasureCardCount = 0;
                 
          //check previous state treasureCardCount
          for (j = 0; j < prevState.handCount[player]; j++)
          {
               card = prevState.hand[player][j];
               if (card == copper || card == silver || card == gold)
               {
                    prevTreasureCardCount++;
               }
          }

          //check post state treasureCardCount
          for (j = 0; j < postState.handCount[player]; j++)
          {
               card = postState.hand[player][j];
               if (card == copper || card == silver || card == gold)
               {
                    postTreasureCardCount++;
               }
          }
          
          if (postTreasureCardCount == prevTreasureCardCount + 2)//passed
          {
               testCase2Passed++;
          }
          else//failed
          {
               testCase2Failed++;
#if (NOISY_TEST == 1)
               printf("Iteration #%d: Testing that player[%d] hand has had two treasure cards added has failed.\r\n", i, player);
               printf("Previous handCount = %d, Previous deckCount = %d, Previous discardCount = %d, \r\n", prevState.handCount[player], prevState.deckCount[player], prevState.discardCount[player]);
               
               int prevTreasureCardDeckCount;
               //check previous state treasureCardCount for the deck
               for (j = 0; j < prevState.deckCount[player]; j++)
               {
                    card = prevState.deck[player][j];
                    if (card == copper || card == silver || card == gold)
                    {
                         prevTreasureCardDeckCount++;
                    }
               }

               int prevTreasureCardDiscardCount;
               //check previous state treasureCardCount for the deck
               for (j = 0; j < prevState.discardCount[player]; j++)
               {
                    card = prevState.discard[player][j];
                    if (card == copper || card == silver || card == gold)
                    {
                         prevTreasureCardDiscardCount++;
                    }
               }
                              
               printf("prevTreasureCardCount in deck was %d\r\n", prevTreasureCardDeckCount);
               printf("prevTreasureCardCount in hand was %d\r\n", prevTreasureCardCount);
               printf("prevTreasureCardCount in discard was %d\r\n", prevTreasureCardDiscardCount);
#endif
          }

     }//end numTests loop

     printf("Random testing for playAdventurer() completed.\r\n");
     printf("=================================================\r\n");
     printf("Tests that exactly 2 cards were indeed added to current player's hand by comparing handCount value: \r\n");
     printf("%d out of %d tests passed!\r\n", testCase1Passed, testCase1Passed + testCase1Failed);
     printf("%d out of %d tests failed!\r\n", testCase1Failed, testCase1Passed + testCase1Failed);

     printf("Tests that the player's hand has had two treasure cards added: \r\n");
     printf("%d out of %d tests passed!\r\n", testCase2Passed, testCase2Passed + testCase2Failed);
     printf("%d out of %d tests failed!\r\n", testCase2Failed, testCase2Passed + testCase2Failed);

     return 0;
}

