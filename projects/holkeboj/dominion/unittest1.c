/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for function isGameOver()

Business Logic to be tested:

* Take a game state as input
* If stack of Province cards is empty, return 1 (game ends)
* If three supply piles are at 0, return 1 (game ends)
* If neither of the above conditions is met, return 0 (game continues)
* Function does not affect game state

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTFUNCTION "isGameOver"

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
    int i, testResult, stateResult, testsRun = 0, testsPassed = 0;
    
    struct gameState cleanGame;
    struct gameState testGame;  // Passed to function to test
    struct gameState testCleanGame; // control for before running test
    
    printf("---------- Testing Function: %s --------------\n", TESTFUNCTION);
    
    printf("---- Case: Stack of province cards is empty ---\n");
    printf("---- Expecting: 1\n");
    // initialize game with empty province card stack
    initializeGame(2, k, 500, &cleanGame);
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    testGame.supplyCount[province] = 0;
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
    
    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 1) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    
    printf("---- Case: Stack of province cards is not empty");
    printf("---- Expecting: 0\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    testGame.supplyCount[province] = 1;
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
    
    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 0) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    
    printf("---- Case: Four supply piles are at 0");
    printf("---- Expecting: 1\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    testGame.supplyCount[0] = 0;
    testGame.supplyCount[1] = 0;
    testGame.supplyCount[2] = 0;
    testGame.supplyCount[3] = 0;
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
    
    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 1) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    
    printf("---- Case: Three supply piles are at 0");
    printf("---- Expecting: 1\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    testGame.supplyCount[0] = 0;
    testGame.supplyCount[1] = 0;
    testGame.supplyCount[2] = 0;
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
    
    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 1) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    
    printf("---- Case: Two supply piles are at 0");
    printf("---- Expecting: 0\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    testGame.supplyCount[0] = 0;
    testGame.supplyCount[1] = 0;
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));

    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 0) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    
    printf("---- Case: All supply piles are at 0");
    printf("---- Expecting: 1\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    for (i = 0; i < 25; i++) {
        testGame.supplyCount[i] = 0;
    }
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
    
    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 1) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;

    printf("---- Case: No supply piles are at 0");
    printf("---- Expecting: 0\n");
    memcpy(&testGame,&cleanGame,sizeof(struct gameState));
    for (i = 0; i < 25; i++) {
        testGame.supplyCount[i] = 1;
    }
    memcpy(&testCleanGame,&testGame,sizeof(struct gameState));

    testResult = isGameOver(&testGame);
    printf("Received: %d\n", testResult);
    stateResult = memcmp(&testGame, &testCleanGame, sizeof(struct gameState));
    printf("Game state altered? %d\n", stateResult);
    if ((testResult == 0) && (stateResult == 0)) {
        printf("Test Passed.\n\n");
        testsPassed++;
    } else {
        printf("Test Failed.\n\n");
    }
    testsRun++;
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));
    
    printf("---------- Testing %s Function Complete ------\n\n", TESTFUNCTION);

    return 0;
}