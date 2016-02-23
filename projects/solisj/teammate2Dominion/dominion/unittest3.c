/********************************************************************************************************************************************************
*** Filename: unittest3.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/27/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: isGameOver()
*** Business requirements:
***  1. If stack of Province cards is empty, the game ends (returns 1)
***  2. If three supply pile are at 0, the game ends (returns 1)
***  3. return 0 if none of the above conditions have been met
***  4. Treasuremap and sea hag is not included as a supply pile according to for loop in isGameOver() as it only checks for cards 0-24
***
***  Testing:
***       1. Test with no supply lines empty
***       2. Test province empty only
***       3. Test every card 0-26 empty only (not including province)
***       4. Test two supply pile combinations empty (not including province)
***       5. Test three supply pile combinations empty (not including province)
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* unittest3: unittest3.c dominion.o rngs.o
*      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
#define NOISY_TEST 1

int main()
{
     int r;
     int j;
     int m;
     int l;
     int numPlayer = 2;
     int seed = 1000;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };
     struct gameState Gstate;
     int testResult;

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
     printf("\n   Beginning testing for isGameOver():\r\n");
     printf("==============================================\r\n");



     int i;
     for (i = 0; i < numTests;i++)
     {

          memset(&Gstate, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &Gstate); // initialize a new game

          /*===============================================================
              Testing new untouched game state (No depleted supply piles)
          ===============================================================*/
#if (NOISY_TEST == 1)
          printf("Testing new untouched game state (No depleted supply piles)\r\n");
#endif
          testResult = isGameOver(&Gstate);

          if (testResult == 1)//game is over
          {
               failedTests++;
          }
          else //game is not over
          {
               passedTests++;
          }

#if (NOISY_TEST == 1)
          printf("isGameover = %d, Expected = 0\r\n", testResult);
          printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

          /*===============================================================
                    Testing depleted Province supply only
          ===============================================================*/
#if (NOISY_TEST == 1)
          printf("Testing depleted Province supply only\r\n");
#endif
          Gstate.supplyCount[province] = 0;

          testResult = isGameOver(&Gstate);

          if (testResult == 1)//game is over
          {
               passedTests++;
          }
          else //game is not over
          {
               failedTests++;
          }
#if (NOISY_TEST == 1)
          printf("isGameover = %d, Expected = 1\r\n", testResult);
          printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

          /*===============================================================
                Testing one depleted supply pile (Not counting province)
          ===============================================================*/
          Gstate.supplyCount[province] = 8; //restore province supply

          
          for (j = 0; j < 27; j++) //iterate through every possible card in the game except treasure map and seahag
          {
               if (j != 3) //every card that is not province
               {
#if (NOISY_TEST == 1)
                    printf("Testing one depleted supply pile- Card depleted: %s \r\n", cards[j]);
#endif
                    Gstate.supplyCount[j] = 0;

                    testResult = isGameOver(&Gstate);

                    if (testResult == 1)//game is over
                    {
                         failedTests++;
                    }
                    else //game is not over
                    {
                         passedTests++;
                    }

#if (NOISY_TEST == 1)
                    printf("isGameover = %d, Expected = 0\r\n", testResult);
                    printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

                    Gstate.supplyCount[j] = 8; //restore supply
               }
          }


          /*===============================================================
                Testing two depleted supply piles (Not counting province)
          ===============================================================*/
          for (j = 0; j < 27; j++) //iterate through possible combinations of every possible card in the game except treasuremap
          {
               for (m = 0; m < 27; m++)
               {
                    if (j != 3 && m !=3 && j != m) //every card that is not province and the two supply piles are not the same
                    {
#if (NOISY_TEST == 1)
                         printf("Testing two depleted supply piles- Cards depleted: %s and %s \r\n", cards[j], cards[m]);
#endif
                         Gstate.supplyCount[j] = 0;
                         Gstate.supplyCount[m] = 0;

                         testResult = isGameOver(&Gstate);

                         if (testResult == 1)//game is over
                         {
                              failedTests++;
                         }
                         else //game is not over
                         {
                              passedTests++;
                         }

#if (NOISY_TEST == 1)
                         printf("isGameover = %d, Expected = 0\r\n", testResult);
                         printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

                         Gstate.supplyCount[j] = 8; //restore supply
                         Gstate.supplyCount[m] = 8; //restore supply
                    }
               }
          }

          /*===============================================================
             Testing three depleted supply piles (Not counting province)
          ===============================================================*/
          for (j = 0; j < 27; j++) //iterate through possible combinations of every possible card in the game except treasuremap and sea hag
          {
               for (m = 0; m < 27; m++)
               {
                    for (l = 0; l < 27; l++)
                    {

                         if (j != 3 && m != 3 && l != 3 && j != m && j != l && m != l) //every card that is not province and the three supply piles are not the same
                         {
#if (NOISY_TEST == 1)
                              printf("Testing three depleted supply piles- Cards depleted: %s, %s, and %s \r\n", cards[j], cards[m], cards[l]);
#endif
                              Gstate.supplyCount[j] = 0;
                              Gstate.supplyCount[m] = 0;
                              Gstate.supplyCount[l] = 0;

                              testResult = isGameOver(&Gstate);

                              if (testResult == 1)//game is over
                              {
                                   passedTests++;
                              }
                              else //game is not over
                              {
                                   failedTests++;
                              }

#if (NOISY_TEST == 1)
                              printf("isGameover = %d, Expected = 1\r\n", testResult);
                              printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

                              Gstate.supplyCount[j] = 8; //restore supply
                              Gstate.supplyCount[m] = 8; //restore supply
                              Gstate.supplyCount[l] = 8; //restore supply
                         }
                    }
               }
          }

     }

     printf("%d out of %d tests passed!\r\n", passedTests, passedTests + failedTests);
     printf("%d out of %d tests failed!\r\n", failedTests, passedTests + failedTests);


     return 0;
}