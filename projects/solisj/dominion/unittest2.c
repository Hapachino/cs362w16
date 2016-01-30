/********************************************************************************************************************************************************
*** Filename: unittest2.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/26/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: fullDeckCount()
*** Business requirements:
*** Note: I think that the inteded use of this function was to calcaulate the sum total of all cards in a player's deck, hand, and discard pile.
***       As it is now, it calculates the sum total of a specific card in the player's deck, hand, and discard pile.
***
***  1. Count how many cards of a specific card is in the player's hand.
***  2. Count how many cards of a specific card is in the player's discard pile.
***  3. Count how many cards of a specific card is in the player's deck.
***  4. return the sum total of the specific card in player's hand, discard pile, and deck.
***
***  Testing:
***       1. Test for empty deck, empty hand, and empty discard deck
***       2. Test with all possible 27 cards
***
*** References: testUpdateCoins.c and cardTest4.c provided by instructor to use as examples and templates
***
* Include the following lines in your makefile:
*
* unittest2: unittest2.c dominion.o rngs.o
*      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
     int player;
     int numPlayer = 2;
     int seed = 1000;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };

     struct gameState Gstate;

     int totalCount;
     int deckCount;
     int handCount;
     int discardCount;
     int maxCards = 10; //How many cards to test up to for deck, hand, and discard pile.
     int testResult;
   
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

     int numTests = 0; //variable to keep track of how many tests have been run.
     int failedTests = 0;
     int passedTests = 0;

     printf("==============================================\r\n");
     printf("\n   Beginning testing for fullDeckCount():\r\n");
     printf("==============================================\r\n");

     for (player = 0; player < numPlayer; player++)
     {
          int i;
          int j;
          for (i = 0; i <= 26; i++) //iterate through every possible card in the game
          {
               for (discardCount = 0; discardCount <= maxCards; discardCount++)
               {
                    for (handCount = 0; handCount <= maxCards; handCount++)
                    {
                         for (deckCount = 0; deckCount <= maxCards; deckCount++)
                         {
                              totalCount = discardCount + handCount + deckCount;

#if (NOISY_TEST == 1)
                              printf("Testing player %d with %d total card(s): Deck: %d card(s), Hand: %d card(s), Discard pile: %d card(s). Card name: %s \r\n", player, totalCount, deckCount, handCount, discardCount, cards[i]);                            
#endif

                              int testDeck[deckCount];
                              for (j = 0; j < deckCount; j++)
                              {
                                   testDeck[j] = i;
                              }
                              int testHand[handCount];
                              for (j = 0; j < handCount; j++)
                              {
                                   testHand[j] = i;
                              }

                              int testDiscard[discardCount];
                              for (j = 0; j < discardCount; j++)
                              {
                                   testDiscard[j] = i;
                              }

                              memset(&Gstate, 23, sizeof(struct gameState));   // clear the game state
                              r = initializeGame(numPlayer, k, seed, &Gstate); // initialize a new game

                              Gstate.handCount[player] = handCount;        // set the number of cards on hand
                              Gstate.deckCount[player] = deckCount;        // set the number of cards in deck
                              Gstate.discardCount[player] = discardCount;  // set the number of cards in discard pile

                              memcpy(Gstate.hand[player], testHand, sizeof(int) * handCount);
                              memcpy(Gstate.deck[player], testDeck, sizeof(int) * deckCount);
                              memcpy(Gstate.discard[player], testDiscard, sizeof(int) * discardCount);

                              testResult = fullDeckCount(player, i, &Gstate);
                              numTests++;

                              if (totalCount == testResult)
                              {
                                   passedTests++;
                              }
                              else
                              {
                                   failedTests++;

                              }
#if (NOISY_TEST == 1)
                              printf("fullDeckCount = %d, Expected = %d\r\n", testResult, totalCount);
                              printf("---------------------------------------------------------------------------------------------------------------------------\r\n");
#endif
                         }
                    }
               }
          }
     }

     printf("%d out of %d tests passed!\r\n", passedTests, numTests);
     printf("%d out of %d tests failed!\r\n", failedTests, numTests);

     return 0;
}
