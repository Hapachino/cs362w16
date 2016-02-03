/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for Council Room Card

Business Logic to be tested:
* Player who plays Council room draws 4 cards
* All other players must draw 4 cards
* Player who plays Council room receives 1 additional buy

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTCARD "Council Room"

int main() {
    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testsRun = 0, testsPassed = 0, i, otherPlayer, player;
    struct gameState testGame;
    struct gameState cleanGame;
    
    for (player = 0; player < 2; player++) {
        otherPlayer = (player == 1) ? 0 : 1;
        initializeGame(2, k, 500, &cleanGame);
        cleanGame.whoseTurn = player;
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        cardEffect(council_room, 0,0,0, &testGame, 0, 0);
        
        printf("---- Did player %d draw 4 cards?\n", player);
        if (testGame.handCount[player] == cleanGame.handCount[player] + 3) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d receive one buy?\n", player);
        if (testGame.numBuys == cleanGame.numBuys + 1) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d draw one card?\n", otherPlayer);
        if (testGame.handCount[otherPlayer] == cleanGame.handCount[otherPlayer] + 1) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
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

    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}