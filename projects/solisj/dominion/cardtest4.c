/********************************************************************************************************************************************************
*** Filename: cardtest4.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/28/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: playSalvager()
*** Business requirements:
***  1. Increase the game state number of buys by exactly 1.
***  2. Trash a card and gain coins equal to the trashed card cost.
***  3. Discard the played salvager card.
***
***  Testing:
***       1. Check that numBuys is increased by 1.
***       2. Check every card possible to be trashed and correct number of coins is added.
***       3. Check that playedCardsCount increased by 1. 
***       4. Check that the played salvager card is in the playedCards pile
***       5. Check that the played salvager card is not in the player's hand
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* cardtest4: cardtest4.c dominion.o rngs.o
*      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*
********************************************************************************************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int findCard(int player, struct gameState *state, int card, int pileFlag); //helper function to search for cards in hand,deck, and played piles

int main()
{
     int i;
     int j;
     int r;
     int player;
     int numPlayer = 2;

     int seed = 1000;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };

#if (NOISY_TEST == 1)
     const char* cards[] = //All 27 cards in game
     {
          "curse",
          "estate",
          "duchy",
          "province",
          "copper",
          "silver",
          "gold",
          "adventurer",
          "council_room",
          "feast",
          "gardens",
          "mine",
          "remodel",
          "smithy",
          "village",
          "baron",
          "great_hall",
          "minion",
          "steward",
          "tribute",
          "ambassador",
          "cutpurse",
          "embargo",
          "outpost",
          "salvager",
          "sea_hag",
          "treasure_map"
     };
#endif

     struct gameState prevState; //untouched game state to compare with after running tests
     struct gameState postState; //game state that will be used for tests


     int testResult;

     int numTests = 1; //how many test iterations to run.
     int failedTests = 0;
     int passedTests = 0;

     printf("==============================================\r\n");
     printf("    Beginning testing for playSalvager() \r\n");
     printf("==============================================\r\n");

     for (i = 0; i < numTests; i++)
     {      
          for (player = 0; player < numPlayer; player++)
          {
               for (j = 0; j <= 26; j++) //iterate through every possible card in the game
               {
                    int otherPlayer = 0;
                    if (player == 0)
                    {
                         otherPlayer = 1;
                    }
#if (NOISY_TEST == 1)
                    printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
                    printf("Testing player %d with %s card to be trashed...\n", player, cards[j]);

                                      
#endif
                    memset(&prevState, 23, sizeof(struct gameState));   // clear the game state
                    r = initializeGame(numPlayer, k, seed, &prevState); // initialize a new game

                    prevState.handCount[player] = 2;        // set the number of cards on hand
                    int salvagerHand[2];
                    salvagerHand[0] = salvager;
                    salvagerHand[1] = j;

                    memcpy(prevState.hand[player], salvagerHand, sizeof(int) *2 );
                    memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on

                    testResult = playSalvager(player, &postState, 0, 1);
                    //cardEffect(salvager, 1, 0, 0, &postState, 0, 0);

#if (NOISY_TEST == 1)
                    printf("Checking that the the number of buys have increased by 1...\r\n");
#endif

                    //Check that number of buys have increased by 1

                    testResult = postState.numBuys;

                    if (testResult == prevState.numBuys + 1) //passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("numBuys = %d, Expected = %d\r\n", testResult, prevState.numBuys + 1);
                    printf("Checking that the correct amount of coins was added for %s card...\r\n", cards[j]);
#endif
                    //check correct amount of coins was added
                    
                    int expectedAmount;

                    if (j == -1) //no card specifed
                    {
                         expectedAmount = 0;
                    }
                    else
                    {
                         expectedAmount = getCost(j);
                    }

                    testResult = postState.coins;

                    if (testResult == prevState.coins + expectedAmount) //passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("postState.coins = %d, Expected = %d\r\n", testResult, prevState.coins + expectedAmount);
                    printf("Testing that player[%d] playedCardCount has increased by 1..\r\n", player);
#endif

                    //Check that playedCardCount increased by 1

                    testResult = postState.playedCardCount;

                    if (testResult == prevState.playedCardCount + 1) //passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("playedCardCount = %d, Expected = %d\r\n", testResult, prevState.playedCardCount + 1);
                    printf("Checking that the played salvager card was added to the played cards pile...\r\n");
#endif
                    //Check that the salvager card was added to the played cards pile

                    testResult = findCard(player, &postState, salvager, 0);

                    if (testResult == -1) //failed, if variable is still -1, salvager was not found
                    {
                         failedTests++;
                    }
                    else//passed
                    {
                         passedTests++;
                    }

#if (NOISY_TEST == 1)
                    if (testResult == -1) //failed
                    {
                         printf("Failed! salvager card was not found in played cards pile!\r\n");
                    }
                    else//passed
                    {
                         printf("Passed! salvager card was found in played cards pile at position %d!\r\n", testResult);
                    }
                    printf("Checking that salvager card is not in player[%d]'s hand...\r\n", player);
#endif
                    //Check that salvager card is not in player's hand

                    testResult = findCard(player, &postState, salvager, 1);

                    if (testResult == -1) //passed, if variable is still -1, salvager was not found
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    if (testResult == -1) //passed
                    {
                         printf("Passsed! salvager card was not found in the player's hand!\r\n");
                    }
                    else//failed
                    {
                         printf("Failed! salvager card was found in player's hand at position %d!\r\n", testResult);
                    }
                    printf("Checking that the card that was trashed is not in the playedCards pile...\r\n");
#endif

                    //Check that the card that was trashed is not in the playedCards pile

                    if (j == salvager) //skip this test for salvager as it will be in the played pile
                    {
#if (NOISY_TEST == 1)
                         printf("Skipping this test as salvager will be in played pile\r\n");
                         printf("Checking that card is not in player[%d]'s hand...\r\n", player);
#endif
                    }
                    else
                    {
                         testResult = findCard(player, &postState, j, 0);

                         if (testResult == -1) //passed, if variable is still -1, card was not found
                         {
                              passedTests++;
                         }
                         else//failed
                         {
                              failedTests++;
                         }

#if (NOISY_TEST == 1)
                         if (testResult == -1) //passed
                         {
                              printf("Passed! The card was not found in played cards pile!\r\n");
                         }
                         else//failed
                         {
                              printf("Failed! The card was found in played cards pile at position %d!\r\n", testResult);
                         }
                         printf("Checking that card is not in player[%d]'s hand...\r\n", player);
#endif
                    }

                    //Check that the card is not in player's hand

                    testResult = findCard(player, &postState, j, 1);

                    if (testResult == -1) //passed, if variable is still -1, card was not found
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    if (testResult == -1) //passed
                    {
                         printf("Passsed! The card was not found in the player's hand!\r\n");
                    }
                    else//failed
                    {
                         printf("Failed! The card was found in player's hand at position %d!\r\n", testResult);
                    }
#endif
               }
          }
     }

     printf("%d out of %d tests passed!\r\n", passedTests, passedTests + failedTests);
     printf("%d out of %d tests failed!\r\n", failedTests, passedTests + failedTests);

     return 0;
}

int findCard(int player, struct gameState *state, int card, int pileFlag)
{
     int foundCard = -1;

     //pileFlag = 0: Check played pile
     //pileFlag = 1: Check hand
     //pileFlag = 2: Check deck
     int pileCount = 0;

     if (pileFlag == 0) { pileCount = state->playedCardCount; };
     if (pileFlag == 1) { pileCount = state->handCount[player]; };
     if (pileFlag == 2){ pileCount = state->deckCount[player]; };


     int i;
     for (i = 0; i < pileCount; i++)
     {

          if (pileFlag == 0)
          {
               if (state->playedCards[i] == card)
               {
                    foundCard = i;
               }
          }
          else if (pileFlag == 1)
          {
               if (state->hand[player][i] == card)
               {
                    foundCard = i;
               }
          }
          else if (pileFlag == 2)
          {
               if (state->deck[player][i] == card)
               {
                    foundCard = i;
               }
          }
     }

     return foundCard;

}

     