/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for Adventurer Card

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

void checkAdventurer(int player, struct gameState *testGame, int *testsRun, int *testsPassed) {
    int preTreasureCount, localTestsRun = 0, localTestsPassed = 0;
    struct gameState cleanGame;

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
    
    // test conditions
    printf("---- Did player %d receive two cards ?\n", player);
    if (testGame.handCount[player] == cleanGame.handCount[player] + 1) {
        // printf("Passed.\n");
        localTestsPassed++;
    } else {
        printf("Failed.\n");
    }
    localTestsRun++;
    
    printf("---- Did player %d receive two treasure cards?\n", player);
    if (preTreasureCount + 2 == postTreasureCount) {
        // printf("Passed.\n");
        localTestsPassed++;
    } else {
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

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testNumber, testsToRun = 1000, testsRun = 0, testsPassed = 0, i, preTreasureCount = 0, postTreasureCount = 0, otherPlayer, player;
    struct gameState testGame;

    // random seed
    srand(time(NULL));

    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    for (testNumber = 0; testNumber < testsToRun; testNumber++) {
        player = random() % 2;
        otherPlayer = (player == 1) ? 0 : 1;
        initializeGame(2, k, 500, &testGame);
       
        // create random test case
        
        // check random test case
        checkAdventurer(player, &testGame, &testsRun, &testsPassed);
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}