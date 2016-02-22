/*
                                            unittest1.c
    Patrick Burrell
    CS 362 - Winter 2016
    Assignment 3
    Test for: drawCard()
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
 Items to test:
    Function runs successfully (returns 0)
    Current player's hand count is increased by one
    Current player's deck count is decreased by one
    Current player's discard count is unchanged
    Current player's total card count is unchanged
    Card from "top" of player's deck is added to hand
    Other player's deck, card, and discard counts are unchanged
*/

int testDrawPlayer(int player, struct gameState *pre, struct gameState *post);

int testOtherPlayers(int player, struct gameState *pre, struct gameState *post);

int main() {
    //s1 will hold state after initialization, s2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int seed = 7;
    
    //Run tests for all possible game sizes
    for (numPlayers = 2; numPlayers < 4; numPlayers++)
    {
        printf("Beginning test of drawCard() function with %d players.\n", numPlayers);
        
        //Initialize game and test for success
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialize. No testing completed.\n");
            return -1;
        }
        //Run tests on changes in game state after call to drawCard
        else
        {
            int j;
            int i = 1;
            int deckSize = gs1->deckCount[i];
            
            //Test runs until player has drawn all cards in original deck
            //Also tests what happens after player has drawn last card in original deck
            for (j = 0; j <= deckSize; j++)
            {
                //Save state of game before call to drawCard for comparison
                memcpy(gs2, gs1, sizeof(struct gameState));
                
                printf("Player %d has %d card(s) remaining in deck.\n", i, gs1->deckCount[i]);
                
                //Test for general error in call to function
                if (drawCard(i, gs1) == -1)
                {
                    printf("Error in call to drawCard().\n");
                    //return -1;
                }
                else
                {
                    if (testDrawPlayer(i, gs2, gs1) != -1)
                    {
                        printf("drawCard() PASSED all tests for player %d, who drew card.\n", i);
                    }
                    if (testOtherPlayers(i, gs2, gs1) != -1)
                    {
                        printf("drawCard() PASSED all tests for players who did not draw a card.\n");
                    }
                }
            } //End for loop
        }
    }
    return 0;
}

/************************************************************************************
                                testDrawPlayer()
 This function compares the game state before and after a call to drawCard() to 
 verify that the state for the player who drew has been updated correctly. Tests that:
    Player has one more card in hand
    Player has one less card in deck
    Card that was on "top" of player's deck is now in player's hand
    Player's discard size is unchanged
    Player's total card count is unchanged
 ************************************************************************************/

int testDrawPlayer(int player, struct gameState *pre, struct gameState *post)
{
    int returnValue = 0;
    
    //Test that player's hand size  increased by one
    if (post->handCount[player] != (pre->handCount[player] + 1))
    {
        printf("FAIL. Player's hand count did not increase by 1.\n");
        returnValue = -1;
    }
    
    //Test that player's deck count decreased by one
    if (post->deckCount[player] != (pre->deckCount[player] - 1))
    {
        printf("FAIL. Player's deck count did not decrease by 1.\n");
        returnValue = -1;
    }
    
    //Test that top card from player's deck before draw is now in player's hand
    if (post->hand[player][post->handCount[player] - 1] != pre->deck[player][pre->deckCount[player] - 1])
    {
        printf("FAIL. Player's top deck card was not added to hand.\n");
        returnValue = -1;
    }

    
    //Test that player's discard pile is the same size
    if (post->discardCount[player] != pre->discardCount[player])
    {
        printf("FAIL. Player's discard pile count has changed.\n");
        returnValue = -1;
    }
    
    //Test that player's total card count is unchanged
    if (fullDeckCount(player, 7, post) != fullDeckCount(player, 7, pre))
    {
        printf("FAIL. Player's total deck count has changed.\n");
        returnValue = -1;
    }
    
    return returnValue;
}


/************************************************************************************
                                    testOtherPlayers()
 This function compares the game state before and after a call to drawCard() to
 verify that the state of the players who did not draw a card is unchanged. Tests that:
    Other players' hand count is unchanged
    Other players' deck count is unchanged
    Other players' discard count is unchanged
 ************************************************************************************/
int testOtherPlayers(int player, struct gameState *pre, struct gameState *post)
{
    int returnValue = 0;
    int numPlayers = pre->numPlayers;
    int i;
    
    for (i = 1; i < numPlayers; i++)
    {
        //Run tests for all players other than one who drew card
        if (i != player)
        {
            //Test that deck count did not change
            if (post->deckCount[i] != pre->deckCount[i])
            {
                printf("FAIL. Player %d did not draw but had a change in deck count.\n", i);
                returnValue = -1;
            }
            //Test that hand count did not change
            if (post->handCount[i] != pre->handCount[i])
            {
                printf("FAIL. Player %d did not draw but had a change in hand count.\n", i);
                returnValue = -1;
            }
            //Test that discard count did not change
            if (post->discardCount[i] != pre->discardCount[i])
            {
                printf("FAIL. Player %d did not draw but had a change in discard count.\n", i);
                returnValue = -1;
            }
        }
    }
    
    return returnValue;
}