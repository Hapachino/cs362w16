/********************************************************************************************************************************************************
*** Filename: cardtest1.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/28/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for playSmithy()- refactored version from assignment 2 (Includes deliberate bug - Info can be found in refactor.c)
*** Business requirements:
***  1. Adds exactly 3 cards from the current player's own deck or discarded pile to the current player's hand.
***  2. Adds the smithy card that was just played to the player's discard deck. 
***
***  Testing:
***       1. Check that exactly 3 cards were indeed added to current player's hand by comparing handCount value
***       2. Check that the 3 cards added came from the player's own deck
***       3. Check that playedCardCount has increased by 1
***       4. Check that the smithy card was added to the playedCards pile
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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


int findCard(int player, struct gameState *state, int card, int pileFlag); //helper function to search for cards in hand,deck, and played piles

int main()
{
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
     printf("    Beginning testing for playSmithy()\r\n");
     printf("==============================================\r\n");


     int i;
     for (i = 0; i < numTests; i++)
     {

          memset(&prevState, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &prevState); // initialize a new game

          for (player = 0; player < numPlayer; player++)
          {
    
               prevState.handCount[player] = 1;        // set the number of cards on hand
               int smithyHand[1];
               smithyHand[0] = smithy;
               memcpy(prevState.hand[player], smithyHand, sizeof(int));

               prevState.deckCount[player] = 5;        // set the number of cards in deck
               int mixedDeck[5];
               mixedDeck[0] = copper;
               mixedDeck[1] = silver;
               mixedDeck[2] = gold;
               mixedDeck[3] = gardens;
               mixedDeck[4] = tribute;
               memcpy(prevState.deck[player], mixedDeck, sizeof(int) * 5);  

               /*
               ============================================================
               Refactored to work with teammate2's dominion.c code
               ==============================================================
               */

               //set player to gamestate.whoseTurn to match teammate 2's refactored smithy
               prevState.whoseTurn = player;

               memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on
                         
                    
               //playSmithy(player, &postState, 0);

               testResult = playSmithy(&postState, player, 0); //testing teammate 2's version of smithy


               //Check that exactly 3 cards were indeed added to current player's hand by comparing handCount value
#if (NOISY_TEST == 1)
               printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
               printf("Testing that player[%d] handCount has increased by 2...\r\n", player);
#endif

               testResult = postState.handCount[player]; 

               if (testResult == prevState.handCount[player] + 2) //+2 due to smithy needing being discarded
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }
#if (NOISY_TEST == 1)
               printf("handCount = %d, Expected = %d\r\n", testResult, prevState.handCount[player] + 2);
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
               printf("Checking that the smithy card was added to the played cards pile...\r\n");
#endif
               //Check that the smithy card was added to the played cards pile

               testResult = findCard(player, &postState, smithy, 0);

               if (testResult == -1) //failed, if variable is still -1, smithy was not found
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
                    printf("Failed! Smithy card was not found in played cards pile!\r\n");
               }
               else//passed
               {
                    printf("Passed! Smithy card was found in played cards pile at position %d!\r\n", testResult);
               }
               printf("Checking that smithy card is not in player[%d]'s hand...\r\n", player);
#endif
               //Check that smithy card is not in player's hand

               testResult = findCard(player, &postState, smithy, 1);

               if (testResult == -1) //passed, if variable is still -1, smithy was not found
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
                    printf("Passsed! Smithy card was not found in the player's hand!\r\n");
               }
               else//failed
               {
                    printf("Failed! Smithy card was found in player's hand at position %d!\r\n", testResult);
               }
               printf("Checking that the 3 cards added came from the player's own deck...\r\n");
#endif
               //Check that the 3 cards added came from the player's own deck


               //debug
               //int y;
               //for (y = 0; y < postState.handCount[player]; y++)
               //{
                    //printf("%s Card at position %d \r\n", cards[postState.hand[player][y]], y);
              // }

               int card;
               int cardCount = 0;
               int foundCards[MAX_DECK];
               int j;
               for (j = 0; j < 5; j++)
               {

                    if (j == 0) 
                    { 
                         card = copper; 
                    }
                    if (j == 1) 
                    { 
                         card = silver;
                    }
                    if (j == 2)
                    { 
                         card = gold;
                    }
                    if (j == 3)
                    { 
                         card = gardens;
                    }
                    if (j == 4)
                    { 
                         card = tribute;
                    }

                    testResult = findCard(player, &postState,card, 1);

                    if (testResult != -1) //card found
                    {
                         cardCount++;
                         foundCards[cardCount - 1] = card;

#if (NOISY_TEST == 1)
                         printf("Found %s card in player[%d]'s hand at position %d! Number of cards found: %d\r\n", cards[card], player, testResult, cardCount);
#endif
                    }
               }

               if (cardCount == 3) //passed
               {
                    passedTests++;
               }
               else//failed
               {
                   failedTests++;
               }

#if (NOISY_TEST == 1)
               printf("cardCount = %d, Expected = 3\r\n", cardCount);
#endif

               //check that the found cards are not in the deck anymore
               for (j = 0; j < cardCount; j++)
               {
                    testResult = findCard(player, &postState, foundCards[j], 2);

                    if (testResult == -1) //card not found
                    {
                         passedTests++;                         
                    }
                    else
                    {
                         failedTests++;
#if (NOISY_TEST == 1)
                         printf("Found %s card in player[%d]'s deck at position %d\r\n", cards[card], player, testResult);
#endif
                    }
               }
          }
     }
     
     printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
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