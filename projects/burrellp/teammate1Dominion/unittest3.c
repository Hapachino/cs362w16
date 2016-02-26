/*
 
                                                unittest3.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: discardCard()
 
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
    Current player's total number of cards is unchanged
    Current player's handCount is decreased by 1
    Current player's deckCount is unchanged
    Current player's discardCount is increased by 1
    Current player's coin total is unchanged
    Current player's numBuys is unchanged
    Current player's numActions is unchanged
    State of other players is unchanged
 */

int testDiscardPlayer(int player, struct gameState *pre, struct gameState *post);
int testNonDiscardPlayers(int player, struct gameState *pre, struct gameState *post);

int main()
{
    //gs1 will hold state after initialization, gs2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int numCards = 10;
    int seed = 100;
    int i, j;           //Index variables
    int activePlayerPass = 1;
    int nonActivePlayerPass = 1;
    
    //Test discardCard() for all players in all game sizes
    printf("Beginning tests for discardCard().\n");
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        //Initialize a game
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialize. No testing completed.\n");
            return -1;
        }
        
        //Test for each player in game
        for (i = 0; i < numPlayers; i++ )
        {
            //Test for each card in hand
            for (j = 0; j < gs1->handCount[i]; j++)
            {
                //Make copy of current game state to use in comparison testing
                memcpy(gs2, gs1, sizeof(struct gameState));
                
                //Card to discard will be randomly chosen
                int handPos = rand() % 3;
                int player = gs1->whoseTurn;
                
                if (discardCard(handPos, player, gs1, 0) == -1)
                {
                    printf("Error in call to drawCard() for player %d on card % in hand.\n", i, j);
                }
                else
                {
                    if (testDiscardPlayer(player, gs2, gs1) == -1)
                    {
                        activePlayerPass = -1;
                    }
                    if (testNonDiscardPlayers(player, gs2, gs1) == -1)
                    {
                        nonActivePlayerPass = 1;
                    }
                }
                
                //Return game state to condition before call to function for next test
                memcpy(gs1, gs2, sizeof(struct gameState));
            }
            if (activePlayerPass != -1)
                printf ("PASS all tests for player %d in %d player game.\n", i + 1, numPlayers);
        }
        if (nonActivePlayerPass != -1)
            printf ("PASS all tests for non-discarding players in %d player game.\n", numPlayers);
    }
    
    //Test special cases of drawCard()
    //Trash flag is set to 1
    printf("Beginning test for special case where trash flag is set to 1.\n");
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialized. Testing with trashFlag = 1 aborted.\n");
            return -1;
        }
        memcpy(gs2, gs1, sizeof(struct gameState));
               
        //Card to discard will be randomly chosen
        int handPos = rand() % 3;
        int player = gs1->whoseTurn;
       
        if (discardCard(handPos, player, gs1, 1) == -1)
        {
            printf("Error in call to drawCard() for player %d on card % in hand.\n", i, j);
        }
        else
        {
            //Increment playedCardCount for test purposes. Any error will still be caught
            gs1->playedCardCount++;
            
            if (testDiscardPlayer(player, gs2, gs1) == -1)
                activePlayerPass = -1;
            if (testNonDiscardPlayers(player, gs2, gs1) == -1)
                nonActivePlayerPass = 1;
        }
        
        if (activePlayerPass != -1)
               printf("PASS all tests for discarding player in %d person game.\n", numPlayers);
        if (nonActivePlayerPass != -1)
               printf("PASS all tests for non-discarding players in %d person game.\n", numPlayers);
               
       
       //Return game state to condition before call to function for next test
       memcpy(gs1, gs2, sizeof(struct gameState));
    }
    
    //Player only has one card in hand
    printf("Beginning test for special case where player has only one card in hand.\n");
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialized. Testing with trashFlag = 1 aborted.\n");
            return -1;
        }
        
        //Card to discard will be randomly chosen
        int handPos = rand() % 3;
        int player = gs1->whoseTurn;
        //Player only has one card
        gs1->handCount[player] = 1;
        
        memcpy(gs2, gs1, sizeof(struct gameState));
               
        if (discardCard(handPos, player, gs1, 0) == -1)
        {
            printf("Error in call to drawCard() for player %d on card % in hand.\n", i, j);
        }
        else
        {
            if (testDiscardPlayer(player, gs2, gs1) == -1)
            {
                activePlayerPass = -1;
            }
            if (testNonDiscardPlayers(player, gs2, gs1) == -1)
            {
                nonActivePlayerPass = 1;
            }
        }
                          
        if (activePlayerPass != -1)
        {
            printf("PASS all tests for discarding player in %d person game.\n", numPlayers);
        }
        if (nonActivePlayerPass != -1)
        {
            printf("PASS all tests for non-discarding players in %d person game.\n", numPlayers);
        }
               
        //Return game state to condition before call to function for next test
        memcpy(gs1, gs2, sizeof(struct gameState));
    }
    
    return 0;
}

/************************************************************************************
                                testDiscardPlayer()
 This function compares the game state before and after a call to buyCard() under the
 scenario in which the player should be able to buy a card to verify that the state
 for the player who bought a card has been updated correctly. Tests that:
    Player has one more card played card pile (played card implemented incorrectly?)
    Player has one less card in hand
    Player's deck count is unchanged
    Player's coin total is unchanged
    Player's number of buys is unchanged
    Player's number of actions is unchanged
 ************************************************************************************/
int testDiscardPlayer(int player, struct gameState *pre, struct gameState *post)
{
    int returnValue = 0;
    
    //Test that playedCard count has increased by 1
    if (post->playedCardCount != (pre->playedCardCount + 1))
    {
        printf("FAIL. PlayedCardCount did not increase by 1.\n");
        returnValue = -1;
    }
    
    //Test that player's deck count is unchanged
    if (post->deckCount[player] != pre->deckCount[player])
    {
        printf("FAIL. Player's deck count changed.\n");
        returnValue = -1;
    }
    
    //Test that player's hand count decreased by 1
    if (post->handCount[player] != (pre->handCount[player] - 1))
    {
        printf("FAIL. Player's hand count did not decrease by 1.\n");
        returnValue = -1;
    }
    
    //Test that player's number is unchanged
    if (post->numBuys != pre->numBuys)
    {
        printf("FAIL. Player's number of buys changed.\n");
        returnValue = -1;
    }
    
    //Test that player's coin total has decreased by cost of purchased card
    if (post->coins != pre->coins)
    {
        printf("FAIL. Player's coin total changed.\n");
        returnValue = -1;
    }
    
    //Test that player's number of actions is unchanged
    if (post->numActions != pre->numActions)
    {
        printf("FAIL. Player's number of actions changed.\n");
        returnValue = -1;
    }
    
    return returnValue;
}


/************************************************************************************
                                testNonDiscardPlayers()
 This function compares the game state before and after a call to drawCard() to
 verify that the state of the players who did not draw a card is unchanged. Tests that:
    Other players' hand count is unchanged
    Other players' deck count is unchanged
    Other players' discard count is unchanged
 ************************************************************************************/
int testNonDiscardPlayers(int player, struct gameState *pre, struct gameState *post)
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


