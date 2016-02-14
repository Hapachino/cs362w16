/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu
Assignment 4

Random Test for Adventurer Card

Business logic to be tested:
* Reveal card from the deck until you get 2 treasure cards
* 2 Treasure cards are added to hand
* Non-treasure cards are discarded

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

# define TESTCARD "Adventurer"

void checkAdventurer(int player, struct gameState testGame, int *testsRun, int *testsPassed);

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int treasure, testNumber, testsToRun = 1000, testsRun = 0, testsPassed = 0, i, j,
        player, playerCount, randomTreasure, randomDeckPos;
    struct gameState testGame;

    // random seed
    srand(time(NULL));

    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    for (testNumber = 0; testNumber < testsToRun; testNumber++) {
        playerCount = 2 + (rand() % (MAX_PLAYERS - 1));
        player = rand() % playerCount;
        
        // clear game state and initialize
        bzero(&testGame, sizeof(struct gameState));
        initializeGame(2, k, 500, &testGame);
       
        // create random test case
        for (i = 0; i < playerCount; i++) {
            testGame.deckCount[i] = rand() % MAX_DECK; // random deck count
            testGame.discardCount[i] = rand() % MAX_DECK; // random discard count
            testGame.handCount[i] = rand () % MAX_HAND + 1; // random hand count
            
            // give each player a random hand
            for (j = 0; j < testGame.handCount[i]; j++) {
                testGame.hand[i][j] = rand() % 27;   
            }
            // give each player a random deck
            for (j = 0; j < testGame.deckCount[i]; j++) {
                testGame.deck[i][j] = rand() % 27;
            }
            // give each player a random discard pile
            for (j = 0; j < testGame.discardCount[i]; j++) {
                testGame.discard[i][j] = rand() % 27;
            }
        }
        
        // make sure the player being tested has an adventurer card
        testGame.hand[player][rand() % testGame.handCount[player]] = adventurer;
        
        // make sure there are at least two treasure cards in the deck
        for (treasure = 0; treasure < 2; treasure++) {
            randomTreasure = rand() % 3;
            randomDeckPos = rand() % MAX_DECK;
            if (randomTreasure == 0) {
                // add a gold to the deck
                testGame.deck[player][randomDeckPos] = gold;
            } else if (randomTreasure == 1) {
                // add a copper to the deck
                testGame.deck[player][randomDeckPos] = silver;
            } else {
                testGame.deck[player][randomDeckPos] = copper;
            }
        }
        
        // check random test case
        checkAdventurer(player, testGame, &testsRun, &testsPassed);
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}

void checkAdventurer(int player, struct gameState testGame, int *testsRun, int *testsPassed) {
    int i, otherPlayer, preTreasureCount = 0, postTreasureCount = 0, localTestsRun = 0, localTestsPassed = 0;
    struct gameState cleanGame;
    
    otherPlayer = (player == 1) ? 0 : 1;

    // get treasure count
    for (i = 0; i < testGame.handCount[player]; i++) {
        if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
            || testGame.hand[player][i] == gold) {
            preTreasureCount++;   
        }
    }
    
    // play adventurer card
    testGame.whoseTurn = player;
    memcpy(&cleanGame, &testGame, sizeof(struct gameState));
    cardEffect(adventurer,0,0,0,&testGame,0,0);

    // count treasure cards after playing
    for (i = 0; i < testGame.handCount[player]; i++) {
        if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
            || testGame.hand[player][i] == gold) {
            postTreasureCount++;   
        }
    } 

    // test conditions for adventurer
    if (testGame.handCount[player] == cleanGame.handCount[player] + 1) {
        // printf("Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d receive two cards ?\n", player);
        printf("Failed.\n");
    }
    localTestsRun++;

    if (preTreasureCount + 2 == postTreasureCount) {
        // printf("Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d receive two treasure cards?\n", player);
        printf("Failed.\n");
    }
    localTestsRun++;
    
    if (testGame.discardCount[player] == cleanGame.discardCount[player] + 1) {
        // printf("Test Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d discard a card?\n", player);
        printf("Test Failed.\n");
    }
    localTestsRun++;
    
    // check for game state changes
    // if (testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]) {
    //     // printf("Test Passed.\n");
    //     localTestsPassed++;
    // } else {
    //         printf("---- Was player %d's discard pile unaffected?\n", otherPlayer);
    //     printf("Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]);
    localTestsPassed++;

    // if (testGame.whoseTurn == cleanGame.whoseTurn) {
    //     // printf("No, it didn't change.  Test Passed.\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did whoseTurn change?\n");
    //     printf("Yes, it changed. Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]);
    localTestsPassed++;

    // if (testGame.numPlayers == cleanGame.numPlayers) {
    //     // printf("No. Test Passed\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did player count change?\n");
    //     printf("Yes. Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.numPlayers == cleanGame.numPlayers);
    localTestsPassed++;

    // if (testGame.outpostPlayed == cleanGame.outpostPlayed) {
    //     // printf("No. Test Passed\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did outpostPlayed change?\n");
    //     printf("Yes. Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.outpostPlayed == cleanGame.outpostPlayed);
    localTestsPassed++;

    // if (testGame.outpostTurn == cleanGame.outpostTurn) {
    //     // printf("Test Passed\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did outpostTurn change?\n");
    //     printf("Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.outpostTurn == cleanGame.outpostTurn);
    localTestsPassed++;

    // if (testGame.phase == cleanGame.phase) {
    //     // printf("Test Passed\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did phase change?\n");
    //     printf("Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.phase == cleanGame.phase);
    localTestsPassed++;

    // if (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]) {
    //     // printf("Test Passed\n");
    //     localTestsPassed++;
    // } else {
    //     printf("---- Did the other player's deck change?\n");
    //     printf("Test Failed.\n");
    // }
    localTestsRun++;
    assert(testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]);
    localTestsPassed++;

    if (testGame.playedCardCount == cleanGame.playedCardCount + 1) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did played card count increment?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;    
    
    // increment test count
    *testsRun += localTestsRun;
    *testsPassed += localTestsPassed;
}