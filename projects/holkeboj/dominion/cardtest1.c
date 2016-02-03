/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu

Test for Smithy Card

Business Logic to be Tested:
* Player who plays Smithy draws 3 cards
* Card is discarded 
* Other players are not affected

**************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

# define TESTCARD "Smithy"

int main() {
    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testsRun = 0, testsPassed = 0, otherPlayer, player, handPos;
    struct gameState testGame;
    struct gameState cleanGame;
    
    for (player = 0; player < 2; player++) {
        for (handPos = 0; handPos < 5; handPos++) {
            printf("---- Testing Player %d Hand Position %d ----\n", player, handPos);
            initializeGame(2, k, 500, &cleanGame);
            memcpy(&testGame, &cleanGame, sizeof(struct gameState));
            otherPlayer = (player == 1) ? 0 : 1;
            smithy_card(handPos, player, &testGame);
            
            printf("---- Did player's hand count go up by 3?\n");
            if (cleanGame.handCount[player] == testGame.handCount[player] - 2) {
                printf("Yes. Test Passed.\n");
                testsPassed++;
            } else {
                printf("No. Test Failed.\n");
                printf("test: %d\tclean: %d\n", cleanGame.handCount[player],testGame.handCount[player]);
            }
            testsRun++;
            printf("---- Did other player's hand change?\n");
            if (testGame.handCount[otherPlayer] == cleanGame.handCount[otherPlayer]) {
                printf("No. Test Passed.\n");
                testsPassed++;
            } else {
                printf("Yes.  Test Failed.\n");
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

    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}