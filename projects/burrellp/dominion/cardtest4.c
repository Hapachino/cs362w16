/*
 
 cardtest3.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: great_hall card
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
 Embargo effect(s):
 +1 card, +1 action, +1 victory point
 */


/*
 Items to test:
    Player who plays card has 1 fewer card in hand
    Player who plays card has same number of cards in deck
    Player who plays card has same number of cards in discard pile
    coins is increased by 2
    numActions is decreased by 1
    embargoTokens for specified card is increased by 1
    State does not change for other players or objects
 Scenarios to test:
    Player adds embargo token to valid pile
    Player attmpts to add embargo token to pile not in play
 */

int testEmbargo(struct gameState *pre, struct gameState *post, int player, int index);

int main()
{
    //s1 will hold state after initialization, s2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers = 4;
    int seed = 55;
    int p;
    int passed = 0;
    
    //Run tests for all game sizes and for each player in game
    printf("Testing for Embargo beginning.\n");
    for (numPlayers = 2; numPlayers <= 4; numPlayers++)
    {
        printf("Testing a %d player game.\n", numPlayers);
        
        
        //Test for each player
        for (p = 0; p < numPlayers; p++)
        {
            //Initialize game and test for success
            if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
            {
                printf("Game state failed to initialize. No testing completed.\n");
                return -1;
            }
            
            printf("Testing for player %d playing Embargo card.\n", p + 1);
            //A random card will be assigned to Embargo
            int card = rand() % 5;
            gs1->hand[p][card] = embargo;
            //Embargo will be placed on baron, make sure it has cards available
            gs1->supplyCount[baron] = 5;
            gs1->whoseTurn += p;
            
            //Save state of game for comparison before and after playing Embargo
            memcpy(gs2, gs1, sizeof(struct gameState));
            if (playCard(card, baron, 0, 0, gs1) == -1)
            {
                printf("Call to playCard() did not execute successfully.\n");
                //return -1;
            }
            //Test changes that occurred during Embargo play
            if (testEmbargo(gs2, gs1, p, baron) == -1)
                passed = -1;
        }
    }
    if (passed != -1)
        printf("PASS all tests for Embargo card on valid pile.\n");
    
    //Testing embargo card for invalid pile choice
    if (initializeGame(4, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed for invalid condition.\n");
        return -1;
    }
    int card = rand() % 5;
    gs1->hand[0][card] = embargo;
    //Embargo will be placed on baron, but supply count for card will be set to 0
    gs1->supplyCount[baron] = -1;
    
    //Call to function should fail
    if (playCard(card, baron, 0, 0, gs1) != -1)
    {
        printf("FAIL. playCard() function completed successfully with invalid condition.\n");
        return -1;
    }
    else
        printf("PASS. playCard() failed with invalid condition for embargo.\n");

    
    return 0;
}


/************************************************************************************
                                testEmbargo()
 This function compares the game state before and after a call to playCard() for
 Embargo to verify that the state changes were as expected.
 Tests for player who played card:
    Size of hand has is decreased by 1
    Size of discard is unchanged
    Size of deck is unchanged
 Tests for other players:
    No change in state
 Other tests on state change:
    numPlayers is the same
    supplyCount of each card remains the same
    outpostPlayed and outpostTurn remain the same
    whoseTurn stays the same
    phase stays the same
    numActions stays the same
    numBuys stays the same
    embargoTokens for selected card is increased by 1
    playedCardCount is unchanged
 ************************************************************************************/
int testEmbargo(struct gameState *pre, struct gameState *post, int player, int index)
{
    int returnValue = 0;
    int numPlayers = pre->numPlayers;
    int i, j;
    int change;
    
    //Test for player who played card
    //Hand size should have decreased by one
    if (post->handCount[player] != (pre->handCount[player] - 1))
    {
        change = post->handCount[player] - pre->handCount[player];
        printf("FAIL. Player's hand count changed by %d.\n", change);
        returnValue = -1;
    }
    //Discard size should be unchanged
    if (post->discardCount[player] != pre->discardCount[player])
    {
        change = post->discardCount[player] - pre->discardCount[player];
        printf("FAIL. Player's discard count changed by %d.\n", change);
        returnValue = -1;
    }
    //Size of deck should be unchanged
    if (post->deckCount[player] != pre->deckCount[player])
    {
        change = pre->deckCount[player] - post->deckCount[player];
        printf("FAIL. Player's deck count changed by %d.\n", change);
        returnValue = -1;
    }
    
    //Tests for all other players
    for (i = 0; i < numPlayers; i++)
    {
        //Run tests for all players other than one who played card
        if (i != player)
        {
            //Test that deck count did not change
            if (post->deckCount[i] != pre->deckCount[i])
            {
                printf("FAIL. Player %d had invalid change in deck count.\n", i + 1);
                returnValue = -1;
            }
            //Test that hand count did not change
            if (post->handCount[i] != pre->handCount[i])
            {
                printf("FAIL. Player %d had invalid change in hand count.\n", i + 1);
                returnValue = -1;
            }
            //Test that discard count did not change
            if (post->discardCount[i] != pre->discardCount[i])
            {
                printf("FAIL. Player %d had invalid change in discard count.\n", i + 1);
                returnValue = -1;
            }
            //Test that specific cards are still the same for all other players
            for (j = 0; j < MAX_HAND; j++)
            {
                if (post->hand[i][j] != pre->hand[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d hand.\n", j, i + 1);
                    returnValue = -1;
                }
            }
            for (j = 0; j < MAX_DECK; j++)
            {
                if (post->deck[i][j] != pre->deck[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d deck.\n", j, i + 1);
                    returnValue = -1;
                }
                if (post->discard[i][j] != pre->discard[i][j])
                {
                    printf("FAIL. Invalid change to card %d in player %d discard.\n", j, i + 1);
                    returnValue = -1;
                }
            }
        }
        
    }
    
    
    //General tests on the state change
    //Coins should increase by 2
    if (post->coins != pre->coins + 2)
    {
        change = post->coins - pre->coins;
        printf("FAIL. Number of coins did not increase by 2. It changed by %d.\n", change);
        returnValue = -1;
    }
    
    //numPlayers should be unchangd
    if (post->numPlayers != pre->numPlayers)
    {
        printf("FAIL. numPlayers changed.\n");
        returnValue = -1;
    }
    //supplyCount should stay the same for all cards. embargo token should increase for only one
    for (i = 0; i < treasure_map + 1; i++)
    {
        if (post->supplyCount[i] != pre->supplyCount[i])
        {
            printf("FAIL. supplyCount changed for card %d.\n", i);
            returnValue = -1;
        }
        
        if (post->embargoTokens[i] != pre->embargoTokens[i])
        {
            if (i == index)
            {
                if (post->embargoTokens[i] != pre->embargoTokens[i] + 1)
                {
                    printf("Selected pile did not gain an embargo token.\n");
                    returnValue = -1;
                }
            }
            else
            {
                printf("FAIL. embargoTokens changed for card %d.\n", i);
                returnValue = -1;
            }
        }
    }
    //outpostPlayed should be unchanged
    if (post->outpostPlayed != pre->outpostPlayed)
    {
        printf("FAIL. outpostPlayed changed.\n");
        returnValue = 1;
    }
    //outpostTurn should be unchanged
    if (post->outpostTurn != pre->outpostTurn)
    {
        printf("FAIL. outpostTurn changed.\n");
        returnValue = -1;
    }
    //whoseTurn should be unchanged
    if (post->whoseTurn != pre->whoseTurn)
    {
        printf("FAIL. whoseTurn changed.\n");
        returnValue = -1;
    }
    //phase should be unchanged
    if (post->phase != pre->phase)
    {
        printf("FAIL. phase changed.\n");
        returnValue = -1;
    }
    //numActions should decrease by 1
    if (post->numActions != pre->numActions - 1)
    {
        change = post->numActions - pre->numActions;
        printf("FAIL. numActions changed by %d.\n", change);
        returnValue = -1;
    }
    //numBuys should be unchanged
    if (post->numBuys != pre->numBuys)
    {
        printf("FAIL. numBuys changed.\n");
        returnValue = -1;
    }
    //playedCardCount should increase by 1
    if (post->playedCardCount != pre->playedCardCount)
    {
        change = post->playedCardCount - pre->playedCardCount;
        printf("FAIL. playedCardCount changed by %d.\n", change);
        returnValue = -1;
    }
    
    return returnValue;
}


