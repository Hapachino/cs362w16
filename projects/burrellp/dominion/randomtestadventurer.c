/*
 
                                        randomtestadventurer.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 4
 Random test for: Adventurer (playAdventurer() function)
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
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
 Elements of game state that wil be randomized:
    How many players in the game
    Which player's turn it is
    Number of coin cards in player's deck
    Type of coin cards (gold, silver, copper)
    Which card in player's hand is Adventurer
 Outcomes to test:
    Player's coins increase by appropriate amount
    Player's discardCount increases by appropriate amount
    Player's handCount decreases by appropriate amount
 */

int testAdventurer(struct gameState *pre, struct gameState *post, int player, int discardCount, int coinIncrease, int numCoinCards);
void randomize (int arr[], struct gameState *gs, int player);
const int TRIALS = 1000;        //Number of times random test will be run

int main()
{
    //s1 will hold state after initialization, s2 will be state after draw card
    struct gameState *gs1 = malloc(sizeof(struct gameState));
    struct gameState *gs2 = malloc(sizeof(struct gameState));
    srand(time(NULL));
    //Cards used in test instance of game
    int gameCards[10] = {smithy, adventurer, council_room, feast, gardens, mine, remodel,
        village, baron, great_hall};
    int seed = rand();
    int i, j;           //Index variables
    int tempHand[MAX_HAND];
    //Variables to be randomized
    int numPlayers;
    int currPlayer;
    int numCoinCards;
    int adventurerIdx;
    //Treasure card indices from game set up
    int copper = 4;
    int silver = 5;
    int gold = 6;
    
    //1000 iterations with randomization for each
    for (i = 0; i < TRIALS; i++) {
        int coinIncrease = 0;
        int numDiscarded = 0;
        
        printf("TEST %d\n", i + 1);
        
        //Randomize game state components;
        numPlayers = (rand() % 3) + 2;   // 2 - 4 players
        numCoinCards = (rand() % 6);     // 0 - 5 coin cards in deck
        adventurerIdx = (rand() % 5);    // Card 0 - 4 in hand will be Adventurer
        currPlayer = (rand() % (numPlayers));
        
        printf("Player %d in %d player game. %d coin cards in deck.\n", currPlayer + 1, numPlayers, numCoinCards);
        
        if (initializeGame(numPlayers, gameCards, seed, gs1) == -1)
        {
            printf("Game state failed to initialize. No testing completed.\n");
            return -1;
        }
        
        //Randomize cards in player's hand
        for (j = 0; j < gs1->handCount[currPlayer]; j++){
            int idx = rand() % 10;
            int card = gameCards[idx];
            gs1->hand[currPlayer][j] = card;
        }
        //Randomize cards in player's deck, initially with no coin cards
        for (j = 0; j < gs1->deckCount[currPlayer]; j++) {
            int idx = rand() % 10;
            int card = gameCards[idx];
            gs1->deck[currPlayer][j] = card;
        }
        //Randomize cards in player's discard pile, initially with no coin cards
        for (j = 0; j < gs1->discardCount[currPlayer]; j++) {
            int idx = rand() % 10;
            int card = gameCards[idx];
            gs1->discard[currPlayer][j] = card;
        }
        
        //Make sure one of those cards is an Adventurer card
        adventurerIdx = rand() % 5;
        gs1->hand[currPlayer][adventurerIdx] = adventurer;
        
        //Special case where no coin cards are in deck - must add them to discard pile
        if (numCoinCards == 0) {
            //Randomly choose two treasure cards to add to discard
            int coin1 = (rand() % 3) + 4;          // Result is 4-6, e.g. coin indices
            int coin2 = (rand() % 3) + 4;
            
            coinIncrease += (coin1 - 3);      //Add value of coins for testing
            coinIncrease += (coin2 - 3);
            
            //Put two coin cards in discard pile so that they will be shuffled in to deck
            gs1->discard[currPlayer][gs1->discardCount[currPlayer]] = coin1;
            gs1->discardCount[currPlayer]++;
            gs1->discard[currPlayer][gs1->discardCount[currPlayer]] = coin2;
            gs1->discardCount[currPlayer]++;
        }
        //Special case where one coin card is in deck - must add one to discard pile
        if (numCoinCards == 1) {
            //Randomly choose one treasure card to add to discard
            int coin1 = (rand() % 3) + 4;          // Result is 4-6, e.g. coin indices
            
            coinIncrease += (coin1 - 3);      //Add value of coins for testing
            
            //Put one coin card in discard pile so that it will be shuffled in to deck
            gs1->discard[currPlayer][gs1->discardCount[currPlayer]] = coin1;
            gs1->discardCount[currPlayer]++;
        }

        //Put appropriate number of coin cards in player's deck
        for (j = 0; j < numCoinCards; j++) {
            //Randomly assign position of coin
            int randCoin = (rand() % 3) + 4;        //Choose coin randomly
            gs1->deck[currPlayer][j] = randCoin;    //Put coin card in deck
        }
        //Player deck now has correct number of coins, put cards in random order
        randomize(gs1->deck[currPlayer], gs1, currPlayer);
        
        //Find out where the first two coin cards are to determine how many cards should have been discarded
        if (numCoinCards != 0) {
            int coinCards = 0;
            //Special case where only looking for one coin card in hand
            if (numCoinCards == 1) {
                coinCards = 1;
            }
            while (coinCards < 2)
            {
                for (j = gs1->deckCount[currPlayer] - 1; j >= 0; j--) {
                    //Test for coin cards
                    if ((gs1->deck[currPlayer][j] == 4 || gs1->deck[currPlayer][j] == 5
                        || gs1->deck[currPlayer][j] == 6) && (coinCards < 2)) {
                        coinCards++;
                        coinIncrease += (gs1->deck[currPlayer][j] - 3);
                    }
                    //All other cards will be discarded
                    else {
                        numDiscarded++;
                    }
                }
            } //End while loop
        }
        //Set up state so that card can be played
        gs1->coins = 0;
        gs1->numActions = 1;
        gs1->phase = 0;
        
        //Copy state for comparison after call to playAdventurer
        memcpy(gs2, gs1, sizeof(struct gameState));
        if (playCard(adventurerIdx, 0, 0, 0, gs1) == -1) {
            printf("Error in call to playCard() for adventurer.\n");
        }
        
        else {
            if (testAdventurer(gs2, gs1, currPlayer, numDiscarded, coinIncrease, numCoinCards) != -1)
                printf("PASS all tests for test %d.\n", i + 1);
        }
        
    }//End outer for loop (1000 trials)
    
    
    return 0;
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
    numActions decreased by 1
    numBuys stays the same
    playedCardCount increases by 1
 ************************************************************************************/
int testAdventurer(struct gameState *pre, struct gameState *post, int player, int discardCount, int coinIncrease, int numCoinCards)
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
    //Number of coins should have increased by coinIncrease
    if (post->coins != pre->coins + coinIncrease)
    {
        change = post->coins - pre->coins;
        printf("FAIL. Player's coin total did not increase by %d. It increased by %d.\n", coinIncrease, change);
        returnValue = -1;
    }
    //Changes to deck and discard count are only predictable when 2+ coins were in deck
    if (numCoinCards > 1) {
        //Cards in discard pile should be as expected
        for (i = 1; i <= discardCount; i++)
        {
            if (post->discard[player][post->discardCount[player] - i] !=
                pre->discard[player][pre->discardCount[player] - i])
            {
                printf("FAIL. Unexpected card in discard pile.\n");
                returnValue = -1;
            }
        }
        //Size of deck should have decreased by (discardCount + 2)
        if (post->deckCount[player] != (pre->deckCount[player] - (discardCount + 2)))
        {
            change = pre->deckCount[player] - post->deckCount[player];
            printf("FAIL. Player's deck count did not decrease by %d. it changed by %d.\n", discardCount + 2, change);
            returnValue = -1;
        }
        //Discard size should have increased by discardCount
        if (post->discardCount[player] != (pre->discardCount[player] + discardCount))
        {
            change = post->discardCount[player] - pre->discardCount[player];
            printf("FAIL. Player's discard count did not increase by %d. It changed by %d.\n", discardCount, change);
            returnValue = -1;
        }
    }
    //Test that total number of cards for player hasn't changed
    if (post->deckCount[player] + post->handCount[player] + post->discardCount[player]
        != pre->deckCount[player] + pre->handCount[player] + pre->discardCount[player]) {
        printf("FAIL. Player's total number of cards changed.\n");
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

/*******************************************************************************
 *                              swap()
 * Swaps two ints
 ******************************************************************************/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/*******************************************************************************
 *                              randomize()
 * Puts the items in an array into random order
 * Function "borrowed" from http://www.geeksforgeeks.org/shuffle-a-given-array/
 ******************************************************************************/
void randomize (int arr[], struct gameState *gs, int player) {
    int i;
    
    //Start from last element in array and swap one by one
    for (i = gs->deckCount[player] - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap (&arr[i], &arr[j]);
    }
}
