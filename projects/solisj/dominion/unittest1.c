/********************************************************************************************************************************************************
*** Filename: unittest1.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Date: 1/25/2015
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Unit test for: updateCoins()
*** Business requirements:
***  1. Reset game state coin count.
***  2. Iterate through the player's hand and add coins depending on the type of treasure card (copper = 1, silver = 2, and gold = 3). 
***  3. Add a bonus if specified in passed parameter
***
***
***  Testing:
***       1. Check that the gamestate.coins is indeed changed after calls to updateCoins()
***       2. Check result for no cards in hand + bonuses.
***       3. Check that multiple combinations of the three treasure cards + bonus return the expected amount. 
***
***
*** References: testUpdateCoins.c provided by instructor to use as example and template
***
* Include the following lines in your makefile:
*
* unittest1: unittest1.c dominion.o rngs.o
*      gcc -o testUpdateCoins -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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

int main(){
     int r;
     int player;
     int numPlayer = 2;
     int handCount;
     int maxHandCount = 5;
     int bonus;
     int maxBonus = 10;
     //int previousGameStateCoins; //variable to check for correct change in gamestate. Should always be 0 in this unit test due to clearing the gamestate
     int numTests = 0; //variable to keep track of how many tests have been run.
     int seed = 1000; 
     struct gameState Gstate;
     int k[10] = { adventurer, council_room, feast, gardens, mine
          , remodel, smithy, village, baron, great_hall };
     // arrays of all coppers, silvers, and golds
     int coppers[MAX_HAND];
     int silvers[MAX_HAND];
     int golds[MAX_HAND];
     int i;
     for (i = 0; i < MAX_HAND; i++)
     {
          coppers[i] = copper;
          silvers[i] = silver;
          golds[i] = gold;
     }

     printf("==============================================\n");
     printf("\n   Beginning testing for updateCoins():\n");
     printf("==============================================\n");

     for (player = 0; player < numPlayer; player++)
     {
          for (handCount = 0; handCount <= maxHandCount; handCount++) //start with checking empty hands 
          {
               for (bonus = 0; bonus <= maxBonus; bonus++)
               {

                    memset(&Gstate, 23, sizeof(struct gameState));   // clear the game state
                    r = initializeGame(numPlayer, k, seed, &Gstate); // initialize a new game
                    Gstate.handCount[player] = handCount;        // set the number of cards on hand

                    /*======================================================
                                Testing copper treasure cards
                    ======================================================*/
#if (NOISY_TEST == 1)
                    printf("Testing player %d with %d copper card(s) and %d bonus.\n", player, handCount, bonus);
#endif

                    memcpy(Gstate.hand[player], coppers, sizeof(int) * handCount); // set all the cards to copper
                    updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                    printf("GameState.coins = %d, expected = %d\n", Gstate.coins, handCount * 1 + bonus);
#endif
                    assert(Gstate.coins == handCount * 1 + bonus); // check if the number of coins is correct
                    numTests++;

                    /*==================================================
                                Testing silver treasure cards
                    ===================================================*/
#if (NOISY_TEST == 1)
                    printf("Testing player %d with %d silver card(s) and %d bonus.\n", player, handCount, bonus);
#endif
                    memcpy(Gstate.hand[player], silvers, sizeof(int) * handCount); // set all the cards to silver
                    updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                    printf("GameState.coins = %d, expected = %d\n", Gstate.coins, handCount * 2 + bonus);
#endif
                    assert(Gstate.coins == handCount * 2 + bonus); // check if the number of coins is correct
                    numTests++;

                    /*===================================================
                                   Testing gold treasure cards
                    ===================================================*/
#if (NOISY_TEST == 1)
                    printf("Testing player %d with %d gold card(s) and %d bonus.\n", player, handCount, bonus);
#endif
                    memcpy(Gstate.hand[player], golds, sizeof(int) * handCount); // set all the cards to gold
                    updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                    printf("GameState.coins = %d, expected = %d\n", Gstate.coins, handCount * 3 + bonus);
#endif
                    assert(Gstate.coins == handCount * 3 + bonus); // check if the number of coins is correct
                    numTests++;

                    /*=============================================
                            Testing mixed treasure cards
                    ================================================*/

                    if (handCount == 2)
                    {
                         int mixedHand1[2];


                         //Copper + Silver
#if (NOISY_TEST == 1)
                         printf("Testing player %d with 1 copper and 1 silver card(s) and %d bonus.\n", player, bonus);
#endif
                        
                         mixedHand1[0] = copper;
                         mixedHand1[1] = silver;

                         memcpy(Gstate.hand[player], mixedHand1, sizeof(int) * handCount); // set cards to 1 copper and 1 silver
                         updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                         printf("GameState.coins = %d, expected = %d\n", Gstate.coins, 3 + bonus);
#endif
                         assert(Gstate.coins == 3 + bonus); // check if the number of coins is correct
                         numTests++;

                         //Copper + Gold
#if (NOISY_TEST == 1)
                         printf("Testing player %d with 1 copper and 1 gold card(s) and %d bonus.\n", player, bonus);
#endif
                         mixedHand1[0] = copper;
                         mixedHand1[1] = gold;

                         memcpy(Gstate.hand[player], mixedHand1, sizeof(int) * handCount); // set cards to 1 copper and 1 gold
                         updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                         printf("GameState.coins = %d, expected = %d\n", Gstate.coins, 4 + bonus);
#endif
                         assert(Gstate.coins == 4 + bonus); // check if the number of coins is correct
                         numTests++;

                         //Silver + gold
#if (NOISY_TEST == 1)
                         printf("Testing player %d with 1 silver and 1 gold card(s) and %d bonus.\n", player, bonus);
#endif
                         mixedHand1[0] = silver;
                         mixedHand1[1] = gold;

                         memcpy(Gstate.hand[player], mixedHand1, sizeof(int) * handCount); // set cards to 1 silver and 1 gold
                         updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                         printf("GameState.coins = %d, expected = %d\n", Gstate.coins, 5 + bonus);
#endif
                         assert(Gstate.coins == 5 + bonus); // check if the number of coins is correct
                         numTests++;
                    }

                    if (handCount == 3)
                    {
                         int mixedHand2[3];

                         //copper + silver + gold
#if (NOISY_TEST == 1)
                         printf("Testing player %d with 1 copper, 1 silver, and 1 gold card(s) and %d bonus.\n", player, bonus);
#endif
                         mixedHand2[0] = copper;
                         mixedHand2[1] = silver;
                         mixedHand2[2] = gold;

                         memcpy(Gstate.hand[player], mixedHand2, sizeof(int) * handCount); // set cards to 1 copper, 1 silver and 1 gold
                         updateCoins(player, &Gstate, bonus);
#if (NOISY_TEST == 1)
                         printf("GameState.coins = %d, expected = %d\n", Gstate.coins, 6 + bonus);
#endif
                         assert(Gstate.coins == 6 + bonus); // check if the number of coins is correct
                         numTests++;
                    }
               }
          }
     }

     printf("All %d tests passed!\n", numTests);

     return 0;
}

