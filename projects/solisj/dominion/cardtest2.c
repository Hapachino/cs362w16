/********************************************************************************************************************************************************
*** Filename: cardtest2.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/28/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: playAdventurer()- refactored version from assignment 2 (Includes deliberate bug - Info can be found in refactor.c)
*** Business requirements:
***  1. Draw cards from player's own deck and discard pile until two treasure cards have been added to hand. 
***  2. All cards drawn that were not the two treasure cards, must be added back to the player's discard pile
***
***  Testing:
***       1. Check that exactly two treasure cards are added to the hand only
***       3. Check that the two treasure cards came from the player's own deck/discard pile
***       4. Check that non treasure cards have been added back to the discard pile
***       5. No other game state changes
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
     printf("    Beginning testing for playAdventurer()\r\n");
     printf("==============================================\r\n");


     int i;
     for (i = 0; i < numTests; i++)
     {
          memset(&prevState, 23, sizeof(struct gameState));   // clear the game state
          r = initializeGame(numPlayer, k, seed, &prevState); // initialize a new game

          for (player = 0; player < numPlayer; player++)
          {
               prevState.handCount[player] = 1;        // set the number of cards on hand
               int adventurerHand[1];
               adventurerHand[0] = adventurer;
               memcpy(prevState.hand[player], adventurerHand, sizeof(int));

               prevState.deckCount[player] = 5;        // set the number of cards in deck
               int mixedDeck[5];
               mixedDeck[0] = copper;
               mixedDeck[1] = feast;
               mixedDeck[2] = gardens;
               mixedDeck[3] = gold;
               mixedDeck[4] = tribute;
               memcpy(prevState.deck[player], mixedDeck, sizeof(int) * 5);

               memcpy(&postState, &prevState, sizeof(struct gameState)); //create clone of game state to run tests on
               playAdventurer(player, &postState);

               //Check that exactly 2 cards were indeed added to current player's hand by comparing handCount value 
#if (NOISY_TEST == 1)
               printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
               printf("Testing that player[%d] handCount has increased by 2...\r\n", player);
#endif

               testResult = postState.handCount[player];

               if (testResult == prevState.handCount[player] + 2) 
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }
#if (NOISY_TEST == 1)
               printf("handCount = %d, Expected = %d\r\n", testResult, prevState.handCount[player] + 2);
               printf("Testing that player[%d] hand contains two treasure cards..\r\n", player);
#endif
               //Check that the hand has the two treasure cards of gold and copper

               int treasureCards = 0;
               int j;
               int card;
               for (j = 0; j < 2; j++)
               {

                    if (j == 0) { card = copper; };
                    if (j == 1) { card = gold; };


                    testResult = findCard(player, &postState, card, 1);

                    if (testResult == -1) //failed, if variable is still -1, card was not found
                    {
                         failedTests++;
                    }
                    else//passed
                    {
                         treasureCards++;
                         passedTests++;
                    }
               }

               if (treasureCards == 2)//passed
               {
                    passedTests++;
               }
               else
               {
                    failedTests++;
               }

#if (NOISY_TEST == 1)
               printf("Number of treasure cards = %d, Expected = %d\r\n", treasureCards, 2);
               printf("Testing that player[%d]'s deckCount has decreased..\r\n", player);
#endif
               testResult = postState.deckCount[player];

               if (testResult < prevState.deckCount[player]) //passed
               {
                    passedTests++;
               }
               else//failed
               {
                    failedTests++;
               }

#if (NOISY_TEST == 1)
               printf("Post deckCount = %d, Previous deckCount = %d\r\n", testResult, prevState.deckCount[player]);
               printf("Testing that player[%d]'s deck does not contain the two treasure cards..\r\n", player);
#endif
               //check that player's deck does not contain copper or gold treasure cards anymore

               for (j = 0; j < 2; j++)
               {

                    if (j == 0) { card = copper; };
                    if (j == 1) { card = gold; };


                    testResult = findCard(player, &postState, card, 2);

                    if (testResult == -1) //passed, the card is not in the deck
                    {
                         passedTests++;
#if (NOISY_TEST == 1)
                         printf("Pass: %s Card was not found in player[%d]'s deck!\r\n", cards[card], player);
#endif
                    }
                    else//failed
                    {
                         failedTests++; 
#if (NOISY_TEST == 1)
                         printf("Fail: %s Card was found in player[%d]'s deck!\r\n",cards[card], player);
#endif
                    }
               }


#if (NOISY_TEST == 1)
               printf("Testing that player[%d]'s discarded pile has increased..\r\n", player);
#endif
               //check that the discard pile increased with the cards that were revealed and were not treasure cards 

               //debug
               //printf("Cards in the discard pile: \r\n");
               //int y;
               //for (y = 0; y < postState.discardCount[player]; y++)
               //{
                    //printf("%s Card at position %d \r\n", cards[postState.discard[player][y]], y);
                //}


               //debug
               //printf("Cards in the hand: \r\n");
               //for (y = 0; y < postState.handCount[player]; y++)
               //{
                    //printf("%s Card at position %d \r\n", cards[postState.hand[player][y]], y);
                //}

               testResult = postState.discardCount[player];

               if (testResult > prevState.discardCount[player])//passed
               {
                    passedTests++;
               }
               else //failed
               {
                    failedTests++;
               }

#if (NOISY_TEST == 1)
               printf("Post discardCount = %d, Previous discardCount = %d\r\n", testResult, prevState.discardCount[player]);
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