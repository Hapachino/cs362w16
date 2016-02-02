/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for function updateCoins

Business logic to be tested:
* Function should give player the correct amount of coins
* Coppers give one coin each
* Silvers give two coins each
* Golds give three coins each
* Bonus is added to player's coin count

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTFUNCTION "updateCoins"

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int testResult, testsRun = 0, testsPassed = 0;
    int hand_size = 5;
    int player_count = 2;
    int player, bonus;
    
    struct gameState cleanGame;
    struct gameState testGame;  // Passed to function to test
    struct gameState testCleanGame; // control for before running test

    printf("---------- Testing Function: %s --------------\n", TESTFUNCTION);
    int hand1[hand_size], hand2[hand_size], hand3[hand_size], 
        hand4[hand_size], hand5[hand_size], hand6[hand_size];
    
    // generate test hands
    for (int i = 0; i < 5; i++) {
        hand1[i] = copper;
        hand2[i] = silver;
        hand3[i] = gold;
        hand4[i] = (i % 2 == 0) ? copper : silver;
        hand5[i] = (i % 2 == 0) ? silver : gold;
        hand6[i] = (i % 2 == 0) ? gold : copper;
    }
    
    initializeGame(2, k, 500, &cleanGame);
    for (player = 0; player < player_count; player++) {
        for (bonus = 0; bonus <= 10; bonus++) {
            printf("------ Testing Player %d, Bonus %d\n", player + 1, bonus);

            printf("---- Case: All coppers ---\n");
            printf("---- Expecting: %d coins ----\n", 5 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand1, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 5 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
            
            printf("---- Case: All silvers ---\n");
            printf("---- Expecting: %d coins ----\n", 10 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand2, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 10 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
            
            printf("---- Case: All golds ---\n");
            printf("---- Expecting: %d coins ----\n", 15 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand3, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 15 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
            
            
            printf("---- Case: Three coppers, two silvers ---\n");
            printf("---- Expecting: %d coins ----\n", 7 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand4, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 7 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
            
            printf("---- Case: Three silvers, two golds ---\n");
            printf("---- Expecting: %d coins ----\n", 12 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand5, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 12 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
            
            printf("---- Case: Three golds, two coppers ---\n");
            printf("---- Expecting: %d coins ----\n", 11 + bonus);
            memcpy(&testGame,&cleanGame,sizeof(struct gameState));
            testGame.handCount[player] = hand_size;
            memcpy(testGame.hand[player], hand6, sizeof(int) * hand_size);
            memcpy(&testCleanGame,&testGame,sizeof(struct gameState));
            updateCoins(player, &testGame, bonus);
            testResult = testGame.coins;
            printf("---- Received: %d coins\n", testResult);
            if (testResult == 11 + bonus) {
                testsPassed++;
                printf("Test Passed.\n");
            } else {
                printf("Test Failed.\n");
            }
            testsRun++;
        }
 
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));
    printf("---------- Testing %s Function Complete ------\n", TESTFUNCTION);
    return 0;
}