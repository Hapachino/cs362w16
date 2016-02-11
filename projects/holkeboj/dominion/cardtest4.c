/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for Great Hall Card

Business Logic to be tested:
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

# define TESTCARD "Great Hall"

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testsRun = 0, testsPassed = 0, otherPlayer, player;
    struct gameState testGame;
    struct gameState cleanGame;
    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    
    for (player = 0; player < 2; player++) {
        otherPlayer = (player == 1) ? 0 : 1;
        initializeGame(2, k, 500, &cleanGame);
        cleanGame.whoseTurn = player;
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        cardEffect(great_hall, 0,0,0, &testGame, 0, 0);
        
        printf("---- Did player %d draw 1 card?\n", player);
        // Since we also discard a card, count should not change
        if (testGame.handCount[player] == cleanGame.handCount[player]) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d gain one action?\n",player);
        if (testGame.numActions == cleanGame.numActions + 1) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        
        

        
        printf("---- Did player %d discard a card?\n", player);
        if (testGame.discardCount[player] == cleanGame.discardCount[player] + 1) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;

        // check for game state changes
        printf("---- Was player %d's discard pile unaffected?\n", otherPlayer);
        if (testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did whoseTurn change?\n");
        if (testGame.whoseTurn == cleanGame.whoseTurn) {
            printf("No, it didn't change.  Test Passed.\n");
            testsPassed++;
        } else {
            printf("Yes, it changed. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did player count change?\n");
        if (testGame.numPlayers == cleanGame.numPlayers) {
            printf("No. Test Passed\n");
            testsPassed++;
        } else {
            printf("Yes. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did outpostPlayed change?\n");
        if (testGame.outpostPlayed == cleanGame.outpostPlayed) {
            printf("No. Test Passed\n");
            testsPassed++;
        } else {
            printf("Yes. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did outpostTurn change?\n");
        if (testGame.outpostTurn == cleanGame.outpostTurn) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did phase change?\n");
        if (testGame.phase == cleanGame.phase) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did number of buys change?\n");
        if (testGame.numBuys == cleanGame.numBuys) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did the other player's hand change?\n");
        if (testGame.handCount[otherPlayer] == cleanGame.handCount[otherPlayer]) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did the other player's deck change?\n");
        if (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did played card count increment?\n");
        if (testGame.playedCardCount == cleanGame.playedCardCount + 1) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;

    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}