/*
                                
                                        unittest2.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: buyCard()
 
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
    Current player's total number of cards is increased by 1
    Current player's discardCount is increased by 1
    Current player's total number of the card purchased is increased by 1
    Current player's coin total is decreased by cost of purchased card
    Current player's number of buys is decreased by 1
    No state change if card is unavailable to purchase
    No state change if player doesn't have enough coins to purchase
    No state change if player doesn't have any buys available
    Supply of purchased card is decreased by 1
    State of other players is unchanged
 */

int testBuyPlayer(int player, struct gameState *pre, struct gameState *post, int card);
int testNonBuyPlayers(int player, struct gameState *pre, struct gameState *post);
int compareStates(struct gameState *a, struct gameState *b);

int main() {
    //gs1 will hold state after initialization, gs2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int numCards = 10;
    int seed = 7;
    int c;          //Index variable
    
    //Initialize a game
    if (initializeGame(2, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
    int currPlayer = whoseTurn(gs1);
    
    //Copy game state for comparison after failed call to buyCard()
    memcpy(gs2, gs1, sizeof(struct gameState));
    
    //Test conditions where player cannot buy card. Game state should be unchanged
    printf("Starting test for player attempting to buy cards without any buys available.\n");
    //Condition where player has no buys
    //Test for each card in deck
    for (c = 0; c < numCards - 1; c++)
    {
        gs1->numBuys = 0;
        //buyCard() should fail
        if (buyCard(gameCards[c], gs1) != -1)
        {
            printf("FAIL. buyCard() did not fail when buys = 0.\n");
        }
        //Reset number of buys to restore gs1 to previous state
        gs1->numBuys = gs2->numBuys;
        
        //Test that game states are identical
        if (compareStates(gs1, gs2) == -1)
        {
            printf("FAIL. Invalid change in game state when no buys were available./n");
        }
        else
        {
            printf("PASS for all tests where player has no buys.\n");
        }
    }
    
    printf("Starting test for player attempting to buy cards without any coins available.\n");
    //Condition where player doesn't have enough money
    //Test for each card in deck
    for (c = 0; c < numCards - 1; c++)
    {
        gs1->coins = 0;
        //buyCard() should fail
        if (buyCard(gameCards[c], gs1) != -1)
        {
            printf("FAIL. buyCard() did not fail when coins = 0.\n");
        }
        //Reset coins to restore gs1 to previous state
        gs1->coins = gs2->coins;
        //Test that game states are identical
        if (compareStates(gs1, gs2) == -1)
        {
            printf("FAIL. Invalid change in game state when no coins were available.\n");
        }
        else
        {
            printf("PASS for all tests where player has no coins.\n");
        }
    }
    printf("Starting test for player attempting to buy cards that are not available.\n");
    //Condition where card is unavailable for purchase (none are left)
    //Test for each card in deck
    for (c = 0; c < numCards - 1; c++)
    {
        gs1->supplyCount[gameCards[c]] = 0;
        //buyCard() should fail
        if (buyCard(gameCards[c], gs1) != -1)
        {
            printf("FAIL. buyCard() did not fail when supplyCount for card %d was 0.\n", gameCards[c]);
        }
        else
        {
            printf("PASS. buyCard() failed when supplyCount for card %d was 0.\n", gameCards[c]);
        }
        //reset supply count to restore gs1 to previous state
        gs1->supplyCount[gameCards[c]] = gs2->supplyCount[gameCards[c]];
        if (compareStates(gs1, gs2) == -1)
        {
            printf("FAIL. Invalid change in game state when card wasn't available to buy.\n");
        }
        else
        {
            printf("PASS for all tests where card %d is not available.\n", gameCards[c]);
        }
    }
    
    //Test for all game sizes
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        printf("Running test for game with %d players.\n", numPlayers);
        
        //Initialize game and test for success
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialize. No testing completed.\n");
            return -1;
        }
        //Run tests on changes in game state after call to buyCard()
        else
        {
            printf("Running tests for instance where player does buy card.\n");
            
            //Run tests for each player in game
            int p;
            for (p = 1; p <= numPlayers; p++)
            {
                //Run tests for each card in the game
                int i;
                for (i = 0; i < numCards - 1; i++)
                {
                    //Ensure that player can buy card
                    gs1->coins = 10;
                    gs1->supplyCount[gameCards[i]] = 5;
                    gs1->numBuys = 1;
                    
                    //Save state of game before call to drawCard for comparison
                    memcpy(gs2, gs1, sizeof(struct gameState));
                    
                    //Test for general error in call to function
                    if (buyCard(gameCards[i], gs1) == -1)
                    {
                        printf("Error in call to buyCard().\n");
                        return -1;
                    }
                    else
                    {
                        int player = gs1->whoseTurn;
                        
                        if (testBuyPlayer(player, gs2, gs1, gameCards[i]) != -1)
                        {
                            printf("buyCard() PASSED all tests for player %d, who bought card %d.\n", p, gameCards[i]);
                        }
                        if (testNonBuyPlayers(player, gs2, gs1) != -1)
                        {
                            printf("buyCard() PASSED all tests for players who did not buy a card.\n");
                        }
                    }
                } //End card for loop
            } //End player for loop
        }
    }
    
    return 0;
}

/************************************************************************************
                            compareStates()
 This function compares two game states and tests whether or not they are identical. 
 It tests for equality in all attributes with the exception of whoseTurn. Returns -1
 if the two states differ in any way, 0 if they are identical.
 ************************************************************************************/
int compareStates(struct gameState *a, struct gameState *b)
{
    int returnValue = 0;
    int i, j;
    
    //Testing numPlayers
    if (a->numPlayers != b->numPlayers)
    {
        returnValue = -1;
        printf("FAIL. Number of players changed in game state.\n");
    }
    //Testing supply count of each card
    for (i = 0; i < treasure_map; i++)
    {
        if (a->supplyCount[i] != b->supplyCount[i])
        {
            returnValue = -1;
            printf("FAIL. Supply count changed in game state for card %d.\n", i);
        }
    }
    //Testing number of embargo tokens for each card
    for (i = 0; i < treasure_map; i++)
    {
        if (a->embargoTokens[i] != b->embargoTokens[i])
        {
            returnValue = -1;
            printf("FAIL. Number of embargo tokens changed in game state for card %d.\n", i);
        }
    }
    //Testing outpostPlayed
    if (a->outpostPlayed != b->outpostPlayed)
    {
        returnValue = -1;
        printf("FAIL. Number for outpostPlayed changed in game state.\n");
    }
    //Testing outpostTurn
    if (a->outpostTurn != b->outpostTurn)
    {
        returnValue = -1;
        printf("FAIL. Number for outpostTurn changed in game state.\n");
    }
    //Testing phase
    if (a->phase != b->phase)
    {
        returnValue = -1;
        printf("FAIL. Phase changed in game state.\n");
    }
    //Testing numActions
    if (a->numActions != b->numActions)
    {
        returnValue = -1;
        printf("FAIL. Number of actions changed in game state.\n");
    }
    //Testing coins
    if (a->numPlayers != b->numPlayers)
    {
        returnValue = -1;
        printf("FAIL. Number of players changed in game state.\n");
    }
    //Testing numBuys
    if (a->coins != b->coins)
    {
        returnValue = -1;
        printf("FAIL. Number of coins changed in game state.\n");
    }
    //Testing hand[MAX_PLAYERS][MAX_HAND]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_HAND; j++)
        {
            if (a->hand[i][j] != b->hand[i][j])
            {
                returnValue = -1;
                printf("FAIL. Card in hand for player %d changed in game state.\n", i + 1);
            }
        }
    }
    //Testing handCount[MAX_PLAYERS]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (a->handCount[i] != b->handCount[i])
        {
            returnValue = -1;
            printf("FAIL. Hand count for player %d changed in game state.\n", i + 1);
        }
    }
    //Testing deck[MAX_PLAYERS][MAX_DECK]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_DECK; j++)
        {
            if (a->deck[i][j] != b->deck[i][j])
            {
                returnValue = -1;
                printf("FAIL. Card in deck for player %d changed in game state.\n", i + 1);
            }
        }
    }
    //Testing deckCount[MAX_PLAYERS]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (a->deckCount[i] != b->deckCount[i])
        {
            returnValue = -1;
            printf("FAIL. Deck count for player %d changed in game state.\n", i + 1);
        }
    }
    //Testing discard[MAX_PLAYERS][MAX_DECK]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        for (j = 0; j < MAX_DECK; j++)
        {
            if (a->discard[i][j] != b->discard[i][j])
            {
                returnValue = -1;
                printf("FAIL. Card in discard for player %d changed in game state.\n", i + 1);
            }
        }
    }
    //Testing discardCount[MAX_PLAYERS]
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        if (a->discardCount[i] != b->discardCount[i])
        {
            returnValue = -1;
            printf("FAIL. Discard count for player %d changed in game state.\n", i + 1);
        }
    }
    //Testing playedCards[MAX_DECK]
    for (i = 0; i < MAX_DECK; i++)
    {
        if (a->playedCards[i] != b->playedCards[i])
        {
            returnValue = -1;
            printf("FAIL. Played cards changed in game state.\n");
        }
    }
    //Testing playedCardCount
    if (a->playedCardCount != b->playedCardCount)
    {
        returnValue = -1;
        printf("FAIL. Played Card Count changed in game state.\n");
    }
   
    return returnValue;
}


/************************************************************************************
                                testBuyPlayer()
 This function compares the game state before and after a call to buyCard() under the
 scenario in which the player should be able to buy a card to verify that the state 
 for the player who bought a card has been updated correctly. Tests that:
    Player has one more card in discard pile
    Player's deck count is unchanged
    Player's hand count is unchanged
    Player's coin total has decreased by cost of purchased card
    Player's number of buys has decreased by one
    Player's number of actions is unchanged
    Supply count of purchased card has decreased by one
 
 ************************************************************************************/

int testBuyPlayer(int player, struct gameState *pre, struct gameState *post, int card)
{
    int returnValue = 0;
    
    //Test that player's discard size increased by one
    if (post->discardCount[player] != (pre->discardCount[player] + 1))
    {
        printf("FAIL. Player's discard pile count did not increase by 1.\n");
        returnValue = -1;
    }
    
    //Test that player's deck count did not change
    if (post->deckCount[player] != pre->deckCount[player])
    {
        printf("FAIL. Player's deck count changed.\n");
        returnValue = -1;
    }
    
    //Test that player's hand count did not change
    if (post->handCount[player] != pre->handCount[player])
    {
        printf("FAIL. Player's hand count changed.\n");
        returnValue = -1;
    }
    
    //Test that player's number of buys has decreased by 1
    if (post->numBuys != (pre->numBuys - 1))
    {
        printf("FAIL. Player's number of buys did not decrease by 1.\n");
        returnValue = -1;
    }
    
    //Test that player's coin total has decreased by cost of purchased card
    if (post->coins != (pre->coins - getCost(card)))
    {
        printf("FAIL. Player's coin total did not decrease by proper amount for card %d.\n", card);
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
                            testNonBuyPlayers()
 This function compares the game state before and after a call to drawCard() to
 verify that the state of the players who did not draw a card is unchanged. Tests that:
     Other players' hand count is unchanged
     Other players' deck count is unchanged
     Other players' discard count is unchanged
 ************************************************************************************/
int testNonBuyPlayers(int player, struct gameState *pre, struct gameState *post)
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