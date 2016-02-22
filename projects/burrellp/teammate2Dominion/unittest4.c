/*
 
                                            unittest4.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: updateCoins()
 
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
    State before and after function is identical with the exception of coins
    Value of coins increases by proper amount
 Conditions to test:
    Gold coins in hand increase value of coins by 3
    Silver coins in hand increase value of coins by 2
    Copper coins in hand increase value of coins by 1
    Bonus value increases value of coins by correct amount
 */

int compareStates(struct gameState *a, struct gameState *b, int coinChange);
int hardCodedCompare(struct gameState *pre, struct gameState *post, int *coinArray, int coins, int player);

int main ()
{
    //gs1 will hold state after initialization, gs2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int numCards = 10;
    int seed = 55;
    int i, j;               //Index variables
    int bonus, maxBonus = 10;
    int passTest = 0;
    int card;
    int coinsValue;
    
    //Initialize a game
    if (initializeGame(2, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
    int currPlayer = whoseTurn(gs1);
    
    //Set coins to 0 before all testing
    gs1->coins = 0;
    
    //Copy game state for comparison after call to updateCoins()
    memcpy(gs2, gs1, sizeof(struct gameState));
    
    printf("Beginning unit testing for updateCoins().\n");
    
    //Testing with no coins and no bonus (10 iterations with random hands)
    printf("Testing with no treasure cards and no bonus.\n");
    for (i = 0; i < 10; i++)
    {
        bonus = 0;
        //Fill hand with random non-treasure cards
        for (j = 0; j < 5; j++)
        {
            card = rand() % 10;
            //Update hands in both states to avoid false positives in comparison testing
            gs1->hand[currPlayer][j] = gameCards[card];
            gs2->hand[currPlayer][j] = gameCards[card];
        }
        
        updateCoins(currPlayer, gs1, bonus);
        
        //Nothing should have changed with call to updateCoins()
        if (compareStates(gs1, gs2, bonus) == -1)
            passTest = -1;
    }
    if (passTest != -1)
        printf("PASS all tests for condition with no treasure cards and no bonus.\n");
    
    
    //Testing with no coins and random bonus
    printf("Testing with no treasure cards and random bonus.\n");
    for (i = 0; i < 10; i++)
    {
        gs1->coins = 0;
        memcpy(gs2, gs1, sizeof(struct gameState));
        bonus = rand() % maxBonus;
        //Fill hand with random non-treasure cards
        for (j = 0; j < 5; j++)
        {
            card = rand() % 10;
            //Update hands in both states to avoid false positives in comparison testing
            gs1->hand[currPlayer][j] = gameCards[card];
            gs2->hand[currPlayer][j] = gameCards[card];
        }
        
        updateCoins(currPlayer, gs1, bonus);
        
        //Nothing should have changed with call to updateCoins()
        if (compareStates(gs1, gs2, bonus) == -1)
            passTest = -1;
    }
    if (passTest != -1)
        printf("PASS all tests for condition with no treasure cards and random bonus.\n");
    
    //Testing only gold coins, from 1 - 5 in hand
    printf("Testing for only gold treasure cards in hand with random bonus.\n");
    for (i = 1; i <=5; i++ )
    {
        gs1->coins = 0;
        memcpy(gs2, gs1, sizeof(struct gameState));
        bonus = rand() % maxBonus;
        for (j = 0; j < 5; j++)
        {
            if (j < i)
            {
                gs1->hand[currPlayer][j] = gold;
                gs2->hand[currPlayer][j] = gold;
            }
            else
            {
                card = rand() % 10;
                gs1->hand[currPlayer][j] = gameCards[card];
                gs2->hand[currPlayer][j] = gameCards[card];
            }
        }
        //Get value of gold coins in hand
        int goldValue = (i * 3);
        updateCoins(currPlayer, gs1, bonus);
        
        if (compareStates(gs1, gs2, bonus + goldValue) == -1)
            passTest = -1;
    }
    if (passTest != -1)
        printf("PASS all tests with only gold coins and random bonus.\n");
    
    //Testing only silver coins, from 1 - 5 in hand
    printf("Testing for only silver treasure cards in hand with random bonus.\n");
    for (i = 1; i <=5; i++ )
    {
        gs1->coins = 0;
        memcpy(gs2, gs1, sizeof(struct gameState));
        bonus = rand() % maxBonus;
        for (j = 0; j < 5; j++)
        {
            if (j < i)
            {
                gs1->hand[currPlayer][j] = silver;
                gs2->hand[currPlayer][j] = silver;
            }
            else
            {
                card = rand() % 10;
                gs1->hand[currPlayer][j] = gameCards[card];
                gs2->hand[currPlayer][j] = gameCards[card];
            }
        }
        //Get value of silver coins in hand
        int silverValue = i * 2;
        updateCoins(currPlayer, gs1, bonus);
        
        if (compareStates(gs1, gs2, bonus + silverValue) == -1)
            passTest = -1;
    }
    if (passTest != -1)
        printf("PASS all tests with only silver coins and random bonus.\n");
    
    //Testing only copper coins, from 1 - 5 in hand
    printf("Testing for only copper treasure cards in hand with random bonus.\n");
    for (i = 1; i <=5; i++ )
    {
        gs1->coins = 0;
        memcpy(gs2, gs1, sizeof(struct gameState));
        bonus = rand() % maxBonus;
        for (j = 0; j < 5; j++)
        {
            if (j < i)
            {
                gs1->hand[currPlayer][j] = copper;
                gs2->hand[currPlayer][j] = copper;
            }
            else
            {
                card = rand() % 10;
                gs1->hand[currPlayer][j] = gameCards[card];
                gs2->hand[currPlayer][j] = gameCards[card];
            }
        }
        //Get value of copper coins in hand
        int copperValue = i;
        updateCoins(currPlayer, gs1, bonus);
        
        if (compareStates(gs1, gs2, bonus + copperValue) == -1)
            passTest = -1;
    }
    if (passTest != -1)
        printf("PASS all tests with only copper coins and random bonus.\n");
    

    //Testing mix of coin values - HARD CODED
    printf("Testing mixes of coin types.\n");
    //Gold and silver
    int gsArray[5] = {gold, silver, silver, gold, silver};
    coinsValue = 12;
    if (hardCodedCompare(gs2, gs1, gsArray, coinsValue, currPlayer) != -1)
        printf("PASS test with gold and silver coins.\n");
    
    //Gold and copper
    int gcArray[5] = {copper, gold, gold, copper, copper};
    coinsValue = 9;
    if (hardCodedCompare(gs2, gs1, gcArray, coinsValue, currPlayer) != -1)
        printf("PASS test with gold and copper coins.\n");
    
    //Silver and copper
    int scArray[5] = {copper, silver, copper, copper, silver};
    coinsValue = 7;
    if (hardCodedCompare(gs2, gs1, scArray, coinsValue, currPlayer) != -1)
        printf("PASS test with silver and copper coins.\n");
    
    //Gold, silver, and copper
    int gscArray[5] = {gold, silver, copper, gold, copper};
    coinsValue = 10;
    if (hardCodedCompare(gs2, gs1, gscArray, coinsValue, currPlayer) != -1)
        printf("PASS test with gold, silver, and copper coins.\n");
    
    return 0;
}

int hardCodedCompare(struct gameState *pre, struct gameState *post, int *coinArray, int coins, int player)
{
    int i;
    int bonus = rand() % 10;
    
    //Set coins to 0 and make copy of state
    pre->coins = 0;
    //Set hand to array passed to function
    for (i = 0; i < 5; i++)
    {
        pre->hand[player][i] = coinArray[i];
        post->hand[player][i] = coinArray[i];
        
    }
    //Copy state of game to compare against state after call to updateCoins
    memcpy(post, pre, sizeof(struct gameState));
    
    updateCoins(player, post, bonus);
    if (compareStates(post, pre, bonus + coins) == -1)
        return -1;
    
    return 0;
}

/************************************************************************************
                                    compareStates()
 This function compares two game states and tests whether or not they are identical.
 It tests for equality in all attributes with the exception of whoseTurn. Returns -1
 if the two states differ in any way, 0 if they are identical. Takes into account
 expected coin change before and after call to updateCoins.
 ************************************************************************************/
int compareStates(struct gameState *a, struct gameState *b, int coinChange)
{
    int returnValue = 0;
    
    int i, j;
    
    //Testing coins - the only value that should have changed
    if (a->coins != (b->coins + coinChange))
    {
        returnValue = -1;
        printf("FAIL. Number of coins changed in game state.\n");
    }
    
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

    //Testing numBuys
    if (a->numBuys != b->numBuys)
    {
        returnValue = -1;
        printf("FAIL. Number of buys changed in game state.\n");
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
