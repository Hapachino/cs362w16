/********************************************************************************************************************************************************
*** Filename: unittest4.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/27/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: gainCard()
*** Business requirements:
***  1. Check if supply pile is empty (0) or card is not used in game (return -1)
***  2. If not empty, add the card to either the player's hand, deck, or discard pile as specified in the toFlag parameter
***  3. Decrease the supplycount for the specifed card
***  4. Return 0 if successful
***
***  Testing:
***       1. Test empty supply piles
***       3. Test cards that are set to -1 (Cards that are not used in current game)
***       4. Test adding card to each of the differenct locations of player's hand, deck, or discard pile
***       5. Test that supplycount is decreased correctly
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* unittest4: unittest4.c dominion.o rngs.o
*      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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


int main()
{
     int r;
     int player;
     int numPlayer = 2;

     int seed = 1000;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };
     struct gameState Gstate;
     int testResult;
     int prevCardCount;

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

     

     int numTests = 1; //how many test iterations to run.
     int failedTests = 0;
     int passedTests = 0;

     printf("==============================================\r\n");
     printf("\n   Beginning testing for gainCard()\r\n");
     printf("==============================================\r\n");


     int i;
     for (i = 0; i < numTests; i++)
     {
          for (player = 0; player < numPlayer; player++)
          {
               int j;
               for (j = 0; j <= 26; j++) //iterate through every possible card in the game
               {
                    memset(&Gstate, 23, sizeof(struct gameState));   // clear the game state
                    r = initializeGame(numPlayer, k, seed, &Gstate); // initialize a new game

                    /*===============================================================
                             Testing empty supply pile for spcecified card
                    ===============================================================*/
#if (NOISY_TEST == 1)
                    printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
                    printf("Testing empty supply pile for spcecified card: %s \r\n", cards[j]);
#endif

                    Gstate.supplyCount[j] = 0;

                    testResult = gainCard(j,&Gstate, 0, player);

                    if (testResult == -1)//supply pile is empty (0) or card is not used in game
                    {
                         passedTests++;
                    }
                    else 
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("gainCard() = %d, Expected = -1\r\n", testResult);
#endif

                    /*===============================================================
                                 Testing cards set to -1 (Not used in game)
                    ===============================================================*/
#if (NOISY_TEST == 1)
                    printf("Testing card set to -1 (Not used in game) for spcecified card: %s \r\n", cards[j]);
#endif

                    Gstate.supplyCount[j] = -1;

                    testResult = gainCard(j, &Gstate, 0, player);

                    if (testResult == -1)//supply pile is empty (0) or card is not used in game
                    {
                         passedTests++;
                    }
                    else
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("gainCard() = %d, Expected = -1\r\n", testResult);
#endif

                    /*==========================================================================
                    Testing toFlag to deck, discard, and hand and that spupply is decreased
                    ===========================================================================*/
                    //added card for [whoseTurn] current player:
                    // toFlag = 0 : add to discard
                    // toFlag = 1 : add to deck
                    // toFlag = 2 : add to hand


                     //discard pile
                    //======================================================
#if (NOISY_TEST == 1)
                    printf("Testing toFlag set for discard pile for spcecified card: %s \r\n", cards[j]);
#endif

                    Gstate.supplyCount[j] = 5;

                    prevCardCount = Gstate.discardCount[player]; //Save current discardCount to be compared later

                    testResult = gainCard(j, &Gstate, 0, player);

                    if (testResult == 0)//supply pile is not empty (0) or card is used in game
                    {
                         passedTests++;
                    }
                    else
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("gainCard() = %d, Expected = 0\r\n", testResult);
                    printf("Testing if supply count was decreased for spcecified card: %s \r\n", cards[j]);
#endif

                    testResult = Gstate.supplyCount[j];

                    if (testResult == 4)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("Gstate.supplyCount[%s] = %d, Expected = 4\r\n", cards[j], testResult);
                    printf("Checking if discardCount was increased for player %d\r\n", player);
#endif

                    testResult = Gstate.discardCount[player];

                    if (testResult == prevCardCount + 1)//passed
                    {
                       passedTests++;  
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.discardCount[%d] = %d, Expected = %d\r\n", player, testResult, prevCardCount + 1);
                    printf("Checking if card was added to player %d's discard pile for spcecified card: %s \r\n", player, cards[j]);
#endif

                    testResult = Gstate.discard[player][Gstate.discardCount[player]-1];

                    if (testResult == j)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.discard[%d][%d] = %d, Expected = %d\r\n", player, prevCardCount, testResult, j);
                    printf("Testing toFlag set for deck for spcecified card: %s \r\n", cards[j]);
#endif
                    //deck
                    //===============================================

                    prevCardCount = Gstate.deckCount[player]; //Save current deckCount to be compared later

                    testResult = gainCard(j, &Gstate, 1, player);

                    if (testResult == 0)//supply pile is not empty (0) or card is used in game
                    {
                         passedTests++;
                    }
                    else
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("gainCard() = %d, Expected = 0\r\n", testResult);
                    printf("Testing if supply count was decreased for spcecified card: %s \r\n", cards[j]);
#endif

                    testResult = Gstate.supplyCount[j];

                    if (testResult == 3)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("Gstate.supplyCount[%s] = %d, Expected = 3\r\n", cards[j], testResult);
                    printf("Checking if deckCount was increased for player %d\r\n", player);
#endif

                    testResult = Gstate.deckCount[player];

                    if (testResult == prevCardCount + 1)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.deckCount[%d] = %d, Expected = %d\r\n", player, testResult, prevCardCount + 1);
                    printf("Checking if card was added to player %d's deck for spcecified card: %s \r\n", player, cards[j]);
#endif

                    testResult = Gstate.deck[player][Gstate.deckCount[player]-1];

                    if (testResult == j)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.deck[%d][%d] = %d, Expected = %d\r\n", player, prevCardCount, testResult, j);
                    printf("Testing toFlag set for hand for spcecified card: %s \r\n", cards[j]);
#endif
                    //hand
                    //===========================================

                    prevCardCount = Gstate.handCount[player]; //Save current handCount to be compared later

                         testResult = gainCard(j, &Gstate, 2, player);

                    if (testResult == 0)//supply pile is not empty (0) or card is used in game
                    {
                         passedTests++;
                    }
                    else
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("gainCard() = %d, Expected = 0\r\n", testResult);
                    printf("Testing if supply count was decreased for spcecified card: %s \r\n", cards[j]);
#endif

                    testResult = Gstate.supplyCount[j];

                    if (testResult == 2)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }
#if (NOISY_TEST == 1)
                    printf("Gstate.supplyCount[%s] = %d, Expected = 2\r\n", cards[j], testResult);
                    printf("Checking if handCount was increased for player %d\r\n", player);
#endif

                    testResult = Gstate.handCount[player];

                    if (testResult == prevCardCount + 1)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.handCount[%d] = %d, Expected = %d\r\n", player, testResult, prevCardCount + 1);
                    printf("Checking if card was added to player %d's hand for spcecified card: %s \r\n", player, cards[j]);
#endif

                    testResult = Gstate.hand[player][Gstate.handCount[player]-1];

                    if (testResult == j)//passed
                    {
                         passedTests++;
                    }
                    else//failed
                    {
                         failedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("Gstate.hand[%d][%d] = %d, Expected = %d\r\n", player, prevCardCount, testResult, j);
                    printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif
               }
          }
     }

     printf("%d out of %d tests passed!\r\n", passedTests, passedTests + failedTests);
     printf("%d out of %d tests failed!\r\n", failedTests, passedTests + failedTests);

     return 0;
}


