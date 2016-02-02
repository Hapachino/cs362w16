/*
 
                                                    cardtest2.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Test for: Smithy (playAdventurer() function)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/*
 adventurer effects:
    Reveal cards from your deck until you reveal two treasure cards
    Add two treasure cards to hand
    Discard other revealed cards
 
 */

/*
 Scenarios to test will be hard coded:
    Player grabs two gold cards
    Player grabs two silver cards
    Player grabs two copper cards
    Player grabs a gold and silver card
    Player grabs a gold and copper card
    Player grabs a silver and copper card
    Player goes through deck and must reshuffle before reaching two treasure cards
 Outcomes to test:
    Player's coins increase by appropriate amount
    Player's discardCount increases by appropriate amount
    Player's handCount decreases by appropriate amount
 */

int testAdventurer(struct gameState *pre, struct gameState *post, int player, int numDiscarded, int coinIncrease);

int main()
{
    //s1 will hold state after initialization, s2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int numPlayers;
    int seed = 55;
    int player, i;
    int passed = 0;
    int numDiscarded;
    int coinIncrease;
    int tempHand[MAX_HAND];
    
    numPlayers = 4;
    if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
    player = 0;
    
//Test for two gold cards taken from top of deck
    //Set up the deck for testing with only two treasure cards in desired spots
    for (i = 0; i < gs1->deckCount[player]; i++)
    {
        if (i == (gs1->deckCount[player] - 1) || i == (gs1->deckCount[player] - 2))
            gs1->deck[player][i] = gold;
        else
            gs1->deck[player][i] = estate;
    }
    //Put adventurer card in player's hand and set rest of cards to estate
    for (i = 0; i < gs1->handCount[player]; i++)
    {
        if (i == 0)
            gs1->hand[player][i] = adventurer;
        else
            gs1->hand[player][i] = estate;
    }
    //Set up state so that card can be played
    gs1->coins = 0;
    gs1->numActions = 1;
    gs1->phase = 0;
    
    //Copy state for comparison after call to playAdventurer
    memcpy(gs2, gs1, sizeof(struct gameState));
    numDiscarded = 0;
    coinIncrease = 6;
    //playAdventurer(player, 0, 0, tempHand, gs1);
    if (playCard(0, 0, 0, 0, gs1) == -1)
        printf("Error in call to playCard() for adventurer.\n");
    printf("Testing two gold coins at top of deck.\n");
    if (testAdventurer(gs2, gs1, player, numDiscarded, coinIncrease) != -1)
        printf("PASS all tests for two gold coins at top of deck.\n");
    
    //Reset game state to original state before next test
    memcpy(gs1, gs2, sizeof(struct gameState));
    
    
    if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
//Test for two silver cards at bottom of deck
    //Set up the deck for testing with only two treasure cards in desired spots
    for (i = 0; i < gs1->deckCount[player]; i++)
    {
        if (i == 0 || i == 1)
            gs1->deck[player][i] = silver;
        else
            gs1->deck[player][i] = estate;
    }
    //Put adventurer card in player's hand and set rest of cards to estate
    for (i = 0; i < gs1->handCount[player]; i++)
    {
        if (i == 0)
            gs1->hand[player][i] = adventurer;
        else
            gs1->hand[player][i] = estate;
    }
    //Set up state so that card can be played
    gs1->coins = 0;
    gs1->numActions = 1;
    gs1->phase = 0;
    
    //Copy state for comparison after call to playAdventurer
    memcpy(gs2, gs1, sizeof(struct gameState));
    numDiscarded = 3;
    coinIncrease = 4;
    //playAdventurer(player, 0, 0, tempHand, gs1);
    if (playCard(0, 0, 0, 0, gs1) == -1)
        printf("Error in call to playCard() for adventurer.\n");
    printf("Testing two silver coins at bottom of deck.\n");
    if (testAdventurer(gs2, gs1, player, numDiscarded, coinIncrease) != -1)
        printf("PASS all tests for two silvers at bottom of deck.\n");

    if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
//Test for gold and silver split in deck
    //Set up the deck for testing with only two treasure cards in desired spots
    for (i = 0; i < gs1->deckCount[player]; i++)
    {
        if (i == 0)
            gs1->deck[player][i] = gold;
        else if (i == gs1->deckCount[player] - 1)
            gs1->deck[player][i] = silver;
        else
            gs1->deck[player][i] = estate;
    }
    //Put adventurer card in player's hand and set rest of cards to estate
    for (i = 0; i < gs1->handCount[player]; i++)
    {
        if (i == 0)
            gs1->hand[player][i] = adventurer;
        else
            gs1->hand[player][i] = estate;
    }
    //Set up state so that card can be played
    gs1->coins = 0;
    gs1->numActions = 1;
    gs1->phase = 0;
    
    //Copy state for comparison after call to playAdventurer
    memcpy(gs2, gs1, sizeof(struct gameState));
    numDiscarded = 3;
    coinIncrease = 5;
    //playAdventurer(player, 0, 0, tempHand, gs1);
    if (playCard(0, 0, 0, 0, gs1) == -1)
        printf("Error in call to playCard() for adventurer.\n");
    printf("Testing gold and silver coins split in deck.\n");
    if (testAdventurer(gs2, gs1, player, numDiscarded, coinIncrease) != -1)
        printf("PASS all tests for gold and silver split in deck.\n");

    if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
//Test for gold and copper split deck
    //Set up the deck for testing with only two treasure cards in desired spots
    for (i = 0; i < gs1->deckCount[player]; i++)
    {
        if (i == 0)
            gs1->deck[player][i] = copper;
        else if (i == 4)
            gs1->deck[player][i] = gold;
        else
            gs1->deck[player][i] = estate;
    }
    //Put adventurer card in player's hand and set rest of cards to estate
    for (i = 0; i < gs1->handCount[player]; i++)
    {
        if (i == 0)
            gs1->hand[player][i] = adventurer;
        else
            gs1->hand[player][i] = estate;
    }
    //Set up state so that card can be played
    gs1->coins = 0;
    gs1->numActions = 1;
    gs1->phase = 0;
    
    //Copy state for comparison after call to playAdventurer
    memcpy(gs2, gs1, sizeof(struct gameState));
    numDiscarded = 3;
    coinIncrease = 4;
    //playAdventurer(player, 0, 0, tempHand, gs1);
    if (playCard(0, 0, 0, 0, gs1) == -1)
        printf("Error in call to playCard() for adventurer.\n");
    printf("Testing gold and copper coins split deck.\n");
    if (testAdventurer(gs2, gs1, player, numDiscarded, coinIncrease) != -1)
        printf("PASS all tests for gold and copper split in deck.\n");
    
    if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
    {
        printf("Game state failed to initialize. No testing completed.\n");
        return -1;
    }
//Testing silver and copper requiring a shuffle
    //Set all cards in deck to non-treasure cards so playAdventurer will call shuffle
    for (i = 0; i < 5; i++)
        gs1->hand[player][i] = estate;
    
    //Set up deck with two treasure cards that should be drawn after shuffle
    gs1->deckCount[player] = 2;
    gs1->deck[player][0] = silver;
    gs1->deck[player][1] = copper;
    
    //Set up player's hand and game state conditions
    for (i = 0; i < gs1->handCount[player]; i++)
    {
        if (i == 0)
            gs1->hand[player][i] = adventurer;
        else
            gs1->hand[player][i] = estate;
    }
    //Set up state so that card can be played
    gs1->coins = 0;
    gs1->numActions = 1;
    gs1->phase = 0;
    
    //Copy state for comparison after call to playAdventurer
    memcpy(gs2, gs1, sizeof(struct gameState));
    numDiscarded = 5;
    coinIncrease = 3;
    //playAdventurer(player, 0, 0, tempHand, gs1);
    if (playCard(0, 0, 0, 0, gs1) == -1)
        printf("Error in call to playCard() for adventurer.\n");
    printf("Testing silver and copper coins in shuffle scenario.\n");
    printf("Ignore error messages related to discard count or deck count.\n");
    if (testAdventurer(gs2, gs1, player, numDiscarded, coinIncrease) != -1)
        printf("PASS all tests for silver and copper split in shuffle scenario.\n");

    
}


/************************************************************************************
                    testAdventurer()
 This function compares the game state before and after a call to playSmithy() to
 verify that the state changes were as expected.
 Tests for player who played card:
    Size of hand has increased by 2
    Size of discard has increased by expected amount
    Size of deck has decreased by expected amount
    Coin total has increased by expected amount
    Expected cards are at top of discard pile
 Tests for other players:
 No change in state
 Other tests on state change:
    numPlayers is the same
    supplyCount of each card remains the same
    embargoTokens count for each card remains the same
    outpostPlayed and outpostTurn remain the same
    whoseTurn stays the same
    phase stays the same
    numActions stays the same
    numBuys stays the same
    playedCardCount increases by 1
 ************************************************************************************/
int testAdventurer(struct gameState *pre, struct gameState *post, int player, int discardCount, int coinIncrease)
{
    int returnValue = 0;
    int numPlayers = pre->numPlayers;
    int i, j, change;
    
    //Test for player who played card
    //Hand size should have increased by two cards
    if (post->handCount[player] != (pre->handCount[player] + 2))
    {
        change = post->handCount[player] - pre->handCount[player];
        printf("FAIL. Player's hand count did not increase by 2. It changed by %d.\n", change);
        returnValue = -1;
    }
    //Discard size should have increased by discardCount
    if (post->discardCount[player] != (pre->discardCount[player] + discardCount))
    {
        change = post->discardCount[player] - pre->discardCount[player];
        printf("FAIL. Player's discard count did not increase by %d. It changed by %d.\n", discardCount, change);
        returnValue = -1;
    }
    //Size of deck should have decreased by (discardCount + 2)
    if (post->deckCount[player] != (pre->deckCount[player] - (discardCount + 2)))
    {
        change = pre->deckCount[player] - post->deckCount[player];
        printf("FAIL. Player's deck count did not decrease by %d. it changed by %d.\n", discardCount + 2, change);
        returnValue = -1;
    }
    //Number of coins should have increased by coinIncrease
    if (post->coins != pre->coins + coinIncrease)
    {
        change = post->coins - pre->coins;
        printf("FAIL. Player's coin total did not increase by %d. It increased by %d.\n", coinIncrease, change);
    }
    //Cards in discard pile should be as expected
    for (i = 1; i <= discardCount; i++)
    {
        if (post->discard[player][post->discardCount[player] - i] != estate)
        {
            printf("FAIL. Unexpected card in discard pile.\n");
            returnValue = -1;
        }
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
                printf("FAIL. Player %d had invalid change in deck count.\n", i);
                returnValue = -1;
            }
            //Test that hand count did not change
            if (post->handCount[i] != pre->handCount[i])
            {
                printf("FAIL. Player %d had invalid change in hand count.\n", i);
                returnValue = -1;
            }
            //Test that discard count did not change
            if (post->discardCount[i] != pre->discardCount[i])
            {
                printf("FAIL. Player %d had invalid change in discard count.\n", i);
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
    //numPlayers should be unchangd
    if (post->numPlayers != pre->numPlayers)
    {
        printf("FAIL. numPlayers changed.\n");
        returnValue = -1;
    }
    //supplyCount and embargoToken should stay the same for all cards
    for (i = 0; i < treasure_map + 1; i++)
    {
        if (post->supplyCount[i] != pre->supplyCount[i])
        {
            printf("FAIL. supplyCount changed for card %d.\n", i);
            returnValue = -1;
        }
        if (post->embargoTokens[i] != pre->embargoTokens[i])
        {
            printf("FAIL. embargoTokens changed for card %d.\n", i);
            returnValue = -1;
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
        printf("FAIL. numActions did not decrease by 1.\n");
        returnValue = -1;
    }
    //numBuys should be unchanged
    if (post->numBuys != pre->numBuys)
    {
        printf("FAIL. numBuys changed.\n");
        returnValue = -1;
    }

    
    return returnValue;
}





