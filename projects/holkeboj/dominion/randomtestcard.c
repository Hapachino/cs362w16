/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu
Assignment 4

Random Test for Great Hall Card

Business logic to be tested:
* Player who plays the Great Hall draws one card
* Player who plays the Great Hall gains one action
* Other players are not affected

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

# define TESTCARD "Great Hall"

void checkGreatHall(int player, struct gameState testGame, int *testsRun, int *testsPassed);

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testNumber, testsToRun = 1000, testsRun = 0, testsPassed = 0,
        player, playerCount, i, j;
    struct gameState testGame;

    // random seed
    srand(time(NULL));

    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    for (testNumber = 0; testNumber < testsToRun; testNumber++) {
        playerCount = rand() % 4 + 1;
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
            for (j = 0; j < testGame.deckCount[i], j++) {
                testGame.deck[i][j] = rand() % 27;
            }
            // give each player a random discard pile
            for (j = 0; j < testGame.discardCount[i], j++) {
                testGame.discard[i][j] = rand() % 27;
            }
        }
        
        // make sure the player being tested has a Great Hall card
        testGame.hand[player][rand() % testGame.handCount[player]] = great_hall;

        // check random test case
        checkGreatHall(player, testGame, &testsRun, &testsPassed);
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}

void checkGreatHall(int player, struct gameState testGame, int *testsRun, int *testsPassed) {
    int otherPlayer, localTestsRun = 0, localTestsPassed = 0;
    struct gameState cleanGame;
    
    otherPlayer = (player == 1) ? 0 : 1;
    
    // play Great Hall card
    testGame.whoseTurn = player;
    memcpy(&cleanGame, &testGame, sizeof(struct gameState));
    cardEffect(great_hall,0,0,0,&testGame,0,0);

    // test conditions for Great Hall
    // Since we also discard a card, count should not change
    if (testGame.handCount[player] == cleanGame.handCount[player]) {
        // printf("Test Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d draw 1 card?\n", player);
        printf("Test Failed.\n");
    }
    localTestsRun++;
    
    if (testGame.numActions == cleanGame.numActions + 1) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d gain one action?\n",player);
        printf("Test Failed.\n");
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
    if (testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]) {
        // printf("Test Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Was player %d's discard pile unaffected?\n", otherPlayer);
        printf("Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.whoseTurn == cleanGame.whoseTurn) {
        // printf("No, it didn't change.  Test Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did whoseTurn change?\n");
        printf("Yes, it changed. Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.numPlayers == cleanGame.numPlayers) {
        // printf("No. Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did player count change?\n");
        printf("Yes. Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.outpostPlayed == cleanGame.outpostPlayed) {
        // printf("No. Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did outpostPlayed change?\n");
        printf("Yes. Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.outpostTurn == cleanGame.outpostTurn) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did outpostTurn change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.phase == cleanGame.phase) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did phase change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;
    
    if (testGame.numBuys == cleanGame.numBuys) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did number of buys change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.handCount[otherPlayer] == cleanGame.handCount[otherPlayer]) {
        // printf("Test Passed.\n");
        localTestsPassed++;
    } else {
        printf("---- Did the other player's hand change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;

    if (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did the other player's deck change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;

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