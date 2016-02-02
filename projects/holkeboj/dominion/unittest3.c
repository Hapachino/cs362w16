/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for function discardCard

Business logic to be tested:
* If card is not trashed, add to Played pile
* Card is removed from the player's hand



**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTFUNCTION "discardCard"

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    int testResult, testsRun = 0, testsPassed = 0;
    
    int max_hand_count = 5;
    int trashFlag;
    int otherPlayer;
    
    struct gameState testGame;
    struct gameState cleanGame;
    
    
    printf("---------- Testing Function: %s --------------\n", TESTFUNCTION);
    
    for (trashFlag = 0; trashFlag < 2; trashFlag++) {
        for (int handCount = 0; handCount < 5; handCount++) {
            for (int player = 0; player < 2; player++) {
                printf("---- Testing Player %d, Trash Flag %d, Hand Count %d\n",player,trashFlag,handCount);
                initializeGame(2, k, 500, &cleanGame);
                memcpy(&testGame, &cleanGame, sizeof(struct gameState));
                //testGame.handCount[player] = handCount;
                discardCard(handCount, player, &testGame, trashFlag);
                
                otherPlayer = (player == 1) ? 0 : 1;

                printf("---- Was the card played? ----\n");
                testResult = ((testGame.playedCardCount == cleanGame.playedCardCount + 1) && testGame.playedCards[testGame.playedCardCount] == cleanGame.hand[player][handCount]);
                if (testResult && trashFlag < 1) {
                    printf("Yes. \nTest Passed.\n");
                    testsPassed++;
                } else if (testResult && trashFlag) {
                    printf("Yes but it was supposed to be trashed.\nTest Failed\n");
                } else if (!testResult && trashFlag < 1) {
                    printf("No, but it was supposed to be played.\nTest Failed\n");
                } else if (!testResult && trashFlag) {
                    printf("Yes, and it was supposed to be trashed.\nTest Passed.\n");
                    testsPassed++;
                }
                testsRun++;
                
                printf("---- Was the current player's hand affected? ----\n");
                testResult = (testGame.handCount[player] == cleanGame.handCount[player] - 1);
                if (testResult) {
                    printf("Yes. Test Passed.\n");
                    testsPassed++;
                } else {
                    printf("No. Test Failed.\n");
                }
                testsRun++;
                
                printf("---- Was the current player's deck affected? ----\n");
                testResult = (testGame.deckCount[player] == cleanGame.deckCount[player]);
                if (testResult) {
                    printf("No. Test Passed.\n");
                    testsPassed++;
                } else {
                    printf("Yes. Test Failed.\n");
                }
                testsRun++;
                
                printf("---- Was the other player's hand affected? ----\n");
                testResult = (testGame.handCount[otherPlayer] == cleanGame.handCount[otherPlayer]);
                if (testResult) {
                    printf("No. Test Passed.\n");
                    testsPassed++;
                } else {
                    printf("Yes. Test Failed.\n");
                }
                testsRun++;

                printf("---- Was the other player's deck affected? ----\n");
                testResult = (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]);
                if (testResult) {
                    printf("No. Test Passed.\n");
                    testsPassed++;
                } else {
                    printf("Yes. Test Failed.\n");
                }
                testsRun++;
                
                // check for game state changes
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
            }
        }
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));
    printf("---------- Testing %s Function Complete ------\n", TESTFUNCTION);
    return 0;
}