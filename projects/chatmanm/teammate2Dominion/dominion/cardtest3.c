/********************************************************************************************************************************************************
*** Filename: cardtest3.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/28/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: playVillage()- refactored version from assignment 2 (Includes deliberate bug - Info can be found in refactor.c)
*** Business requirements:
***  1. Adds exactly 1 cards from the current player's own deck or discarded pile to the current player's hand.
***  2. Increases the player's available number of actions by exactly 2.
***  3. Adds the played village card to the player's discard pile.
***
***  Testing:
***       1. Check that exactly 1 card was added to current player's hand by comparing handCount value
***       2. Check that the 1 card added came from the player's own deck
***       3. Check that playedCardCount has increased by 1
***       4. Check that the village card was added to the playedCards pile
***       5. Check that the added card is not in the player's deck anymore
***       6. Check that number of actions have increased by 2
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* cardtest3: cardtest3.c dominion.o rngs.o
*      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
     printf("    Beginning testing for playVillage()\r\n");
     printf("==============================================\r\n");


     int i;
     for (i = 0; i < numTests; i++)
     {
          memset(&prevState, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &prevState); // initialize a new game

          for (player = 0; player < numPlayer; player++)
          {
               prevState.handCount[player] = 1;        // set the number of cards on hand
               int villageHand[1];
               villageHand[0] = village;
               memcpy(prevState.hand[player], villageHand, sizeof(int));

               prevState.deckCount[player] = 5;        // set the number of cards in deck
               int mixedDeck[5];
               mixedDeck[0] = copper;
               mixedDeck[1] = silver;
               mixedDeck[2] = gold;
               mixedDeck[3] = gardens;
               mixedDeck[4] = tribute;
               memcpy(prevState.deck[player], mixedDeck, sizeof(int) * 5);

               memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on
               playVillage(player, &postState, 0);

               //Check that exactly 1 card was indeed added to current player's hand by comparing handCount value
#if (NOISY_TEST == 1)
               printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
               printf("Testing that player[%d] handCount is still the same...\r\n", player);
#endif

               testResult = postState.handCount[player];

               if (testResult == prevState.handCount[player]) //due to village needing being discarded, handCount should still be the same
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }
#if (NOISY_TEST == 1)
               printf("handCount = %d, Expected = %d\r\n", testResult, prevState.handCount[player]);
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
               printf("Checking that the village card was added to the played cards pile...\r\n");
#endif
               //Check that the village card was added to the played cards pile

               testResult = findCard(player, &postState, village, 0);

               if (testResult == -1) //failed, if variable is still -1, village was not found
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
                    printf("Failed! village card was not found in played cards pile!\r\n");
               }
               else//passed
               {
                    printf("Passed! village card was found in played cards pile at position %d!\r\n", testResult);
               }
               printf("Checking that village card is not in player[%d]'s hand...\r\n", player);
#endif
               //Check that village card is not in player's hand

               testResult = findCard(player, &postState, village, 1);

               if (testResult == -1) //passed, if variable is still -1, village was not found
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
                    printf("Passsed! village card was not found in the player's hand!\r\n");
               }
               else//failed
               {
                    printf("Failed! village card was found in player's hand at position %d!\r\n", testResult);
               }
               printf("Checking that the card added came from the player's own deck...\r\n");
#endif


               //Check that the 1 card added came from the player's own deck


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

                    testResult = findCard(player, &postState, card, 1);

                    if (testResult != -1) //card found
                    {
                         cardCount++;
                         foundCards[cardCount - 1] = card;

#if (NOISY_TEST == 1)
                         printf("Found %s card in player[%d]'s hand at position %d! Number of cards found: %d\r\n", cards[card], player, testResult, cardCount);
#endif
                    }
               }

               if (cardCount == 1) //passed
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }

#if (NOISY_TEST == 1)
               printf("cardCount = %d, Expected = 1\r\n", cardCount);
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
#if (NOISY_TEST == 1)
               printf("Testing that player[%d] deckCount has decreased by 1..\r\n", player);
#endif
               //Check that deckCount decreased by 1

               testResult = postState.deckCount[player];

               if (testResult == prevState.deckCount[player] - 1) //passed
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }
#if (NOISY_TEST == 1)
               printf("deckCount = %d, Expected = %d\r\n", testResult, prevState.deckCount[player] - 1);
               printf("Checking that the the number of actions have increased by 2...\r\n");
#endif


               //Check that number of actions have increased by 2

               testResult = postState.numActions;

               if (testResult == prevState.numActions + 2) //passed
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }
#if (NOISY_TEST == 1)
               printf("numActions = %d, Expected = %d\r\n", testResult, prevState.numActions + 2);
               printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif

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