/* -----------------------------------------------------------------------
  updateCoins() Unit Testing file
  Author: James Linnenburger - Oregon State CS362 Spring 2016

  testUnit3: unittest3.c dominion.o rngs.o
 	gcc -0 unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)

 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"


//Determine if two gameStates are identical or not: Return 1 if identical, 0 if not
int statesAreEqual(struct gameState *g1, struct gameState *g2)
{
    int i, j;

    if(g1->numPlayers != g2->numPlayers) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    if(g1->numActions != g2->numActions) return 01;
   // if(g1->coins != g2->coins) return 0;     //only thing that should be changed in updateCoin
    if(g1->numBuys != g2->numBuys) return 0;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(g1->handCount[i] != g2->handCount[i]) return 0;
        if(g1->deckCount[i] != g2->deckCount[i]) return 0;
        if(g1->discardCount[i] != g2->discardCount[i]) return 0;

        for(j = 0; j < MAX_HAND; j++)
            if(g1->hand[i][j] != g2->hand[i][j]) return 0;

        for(j = 0; j < MAX_DECK; j++)
            if(g1->deck[i][j] != g2->deck[i][j]) return 0;
    }

    for(i = 0; i < MAX_DECK; i++)
        if(g1->playedCards[i] != g2->playedCards[i]) return 0;

    if(g1->playedCardCount != g2->playedCardCount) return 0;

    return 1;
}


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0
int main() {
    int i, player;
    int seed = 500;          //random seeds
    int numPlayers = 4;
    int maxBonus = 10;      //set maximum bonus options
    int handCount, bonus, expected;
    int maxHandCount = 10;      //maximum number of cards in a players hand
    int pass = 0, fail = 0, tests = 0;  //counts of passed and failed tests
    char *testStatus;

    int k[10] = {adventurer, council_room, feast, gardens, mine,   //establish a card set for the game
                 remodel, smithy, village, baron, great_hall};


    struct gameState game, test;
    int randCard;
    srand(seed);
    //build Array of all copper, silver and gold cards
    int copperCards[MAX_HAND];
    int silverCards[MAX_HAND];
    int goldCards[MAX_HAND];
    int noCoins[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++)
    {
        copperCards[i] = copper;
        silverCards[i] = silver;
        goldCards[i] = gold;
        randCard = -1;
        while(randCard == -1 && randCard > 2 && randCard < 7)
            randCard = rand() % 26;
        noCoins[i] = randCard;
    }

    //Testing Part 1:  Test all Players with hands of all coppers, silvers
    //and golds with all possible bonus values.
    #if (NOISY_TEST == 1)
    printf("Testing: [coins][expected]\t[P#]\t[#C]\t[#S]\t[#G]\t[#B]\n");
    printf("-------------------------------------------------------------------------\n");
    #endif

//TESTING ALL COPPERS IN HAND
    for(player = 0; player < numPlayers; player++)                  //loop through players
    {
        for(handCount = 0; handCount < maxHandCount; handCount++)  //loop through all possible size hands
        {
            for(bonus = 0; bonus <= maxBonus; bonus++)             //loop through all possible bonus values
            {
                tests++;
                memset(&game, 0, sizeof(struct gameState));          // clear the game state
                initializeGame(numPlayers, k, seed, &game);           // initialize a new game
                game.handCount[player] = handCount;                 // set the number of cards on hand
                memcpy(game.hand[player], copperCards, sizeof(int) * handCount); // set all the cards to copper
                memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state
                updateCoins(player, &game, bonus);
                expected = handCount*1 + bonus;
                //tests pass if coins are as expected and nothing other than coins have changed
                //in the gamestate.
                if(game.coins == expected && statesAreEqual(&game, &test))
                {
                    pass++;
                    testStatus = "PASSED";
                }
                else
                {
                    fail++;
                    testStatus = "FAILED";
                }
                #if (NOISY_TEST == 1)
                printf("%s: [%d][%d]", testStatus, game.coins,  expected );
                if(expected < 10 || game.coins < 10)
                    printf("\t");
                printf("\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",player, handCount, 0, 0, bonus);
                #endif

            } //end bonus loop

        } // end handCount loop
    } //end player loop
    if(pass == tests)
        printf("HANDS OF ALL COPPERS --- ALL PASS!\n");
    else
        printf("There were %d failures in hands of all copper.\n", fail);
    tests = 0;
    pass = 0;
    fail = 0;

//TESTING ALL SILVERS IN HAND
    for(player = 0; player < numPlayers; player++)                  //loop through players
    {
        for(handCount = 0; handCount < maxHandCount; handCount++)  //loop through all possible size hands
        {
            for(bonus = 0; bonus <= maxBonus; bonus++)             //loop through all possible bonus values
            {
                tests++;
                memset(&game, 0, sizeof(struct gameState));          // clear the game state
                initializeGame(numPlayers, k, seed, &game);           // initialize a new game
                game.handCount[player] = handCount;                 // set the number of cards on hand
                memcpy(game.hand[player], silverCards, sizeof(int) * handCount); // set all the cards to silver
                memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state
                updateCoins(player, &game, bonus);
                expected = handCount*2 + bonus;
                //tests pass if coins are as expected and nothing other than coins have changed
                //in the gamestate.
                if(game.coins == expected && statesAreEqual(&game, &test))
                {
                    pass++;
                    testStatus = "PASSED";
                }
                else
                {
                    fail++;
                    testStatus = "FAILED";
                }
                #if (NOISY_TEST == 1)
                printf("%s: [%d][%d]", testStatus, game.coins,  expected );
                if(expected < 10 || game.coins < 10)
                    printf("\t");
                printf("\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",player, 0, handCount, 0, bonus);
                #endif

            } //end bonus loop

        } // end handCount loop
    } //end player loop
     if(pass == tests)
        printf("HANDS OF ALL SILVER --- ALL PASS!\n");
    else
        printf("There were %d failures in hands of all silver.\n", fail);
    tests = 0;
    pass = 0;
    fail = 0;

//TESTING ALL GOLD IN HAND
    for(player = 0; player < numPlayers; player++)                  //loop through players
    {
        for(handCount = 0; handCount < maxHandCount; handCount++)  //loop through all possible size hands
        {
            for(bonus = 0; bonus <= maxBonus; bonus++)             //loop through all possible bonus values
            {
                tests++;
                memset(&game, 0, sizeof(struct gameState));          // clear the game state
                initializeGame(numPlayers, k, seed, &game);           // initialize a new game
                game.handCount[player] = handCount;                 // set the number of cards on hand
                memcpy(game.hand[player], goldCards, sizeof(int) * handCount); // set all the cards to golf
                memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state
                updateCoins(player, &game, bonus);
                expected = handCount*3 + bonus;
                //tests pass if coins are as expected and nothing other than coins have changed
                //in the gamestate.
                if(game.coins == expected && statesAreEqual(&game, &test))
                {
                    pass++;
                    testStatus = "PASSED";
                }
                else
                {
                    fail++;
                    testStatus = "FAILED";
                }
                #if (NOISY_TEST == 1)
                printf("%s: [%d][%d]", testStatus, game.coins,  expected );
                if(expected < 10 || game.coins < 10)
                    printf("\t");
                printf("\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",player, 0, 0, handCount, bonus);
                #endif

            } //end bonus loop

        } // end handCount loop
    } //end player loop
     if(pass == tests)
        printf("HANDS OF ALL GOLD --- ALL PASS!\n");
    else
        printf("There were %d failures in hands of all gold.\n", fail);
    tests = 0;
    pass = 0;
    fail = 0;

//TESTING NO COINS IN HAND
    for(player = 0; player < numPlayers; player++)                  //loop through players
    {
        for(handCount = 0; handCount < maxHandCount; handCount++)  //loop through all possible size hands
        {
            for(bonus = 0; bonus <= maxBonus; bonus++)             //loop through all possible bonus values
            {
                tests++;
                memset(&game, 0, sizeof(struct gameState));          // clear the game state
                initializeGame(numPlayers, k, seed, &game);           // initialize a new game
                game.handCount[player] = handCount;                 // set the number of cards on hand
                memcpy(game.hand[player], noCoins, sizeof(int) * handCount); // set all the cards to non coin cards
                memcpy(&test, &game, sizeof(struct gameState));     //establish a cloned game state
                updateCoins(player, &game, bonus);
                expected = 0 + bonus;
                //tests pass if coins are as expected and nothing other than coins have changed
                //in the gamestate.
                if(game.coins == expected && statesAreEqual(&game, &test))
                {
                    pass++;
                    testStatus = "PASSED";
                }
                else
                {
                    fail++;
                    testStatus = "FAILED";
                }
                #if (NOISY_TEST == 1)
                printf("%s: [%d][%d]", testStatus, game.coins,  expected );
                if(expected < 10 || game.coins < 10)
                    printf("\t");
                printf("\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\n",player, 0, 0, 0, bonus);
                #endif

            } //end bonus loop

        } // end handCount loop
    } //end player loop
    if(pass == tests)
        printf("HANDS OF NO COINS --- ALL PASS!\n");
    else
        printf("There were %d failures in hands of no coins.\n", fail);
    tests = 0;
    pass = 0;
    fail = 0;
    pass = 0;
    fail = 0;

 return 0;
}


