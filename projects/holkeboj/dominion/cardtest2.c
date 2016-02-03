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

# define TESTCARD "Adventurer"

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testsRun = 0, testsPassed = 0, i, preTreasureCount = 0, postTreasureCount = 0, otherPlayer, player, handPos;
    struct gameState testGame;
    struct gameState cleanGame;


    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    for (player = 0; player < 2; player++) {
        initializeGame(2, k, 500, &cleanGame);
        cleanGame.whoseTurn = player;
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        for (i = 0; i < testGame.handCount[player]; i++) {
            if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
                || testGame.hand[player][i] == gold) {
                preTreasureCount++;   
            }
        }
        cardEffect(adventurer,0,0,0,&testGame,0,0);
        otherPlayer = (player == 1) ? 0 : 1;
        for (i = 0; i < testGame.handCount[player]; i++) {
            if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
                || testGame.hand[player][i] == gold) {
                postTreasureCount++;   
            }
        }        
        printf("Top Card: %d\n", testGame.hand[player][testGame.handCount[player]]);
        printf("---- Did player %d receive two cards ?\n", player);
        if (testGame.handCount[player] == cleanGame.handCount[player] + 1) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d receive two treasure cards?\n", player);
        printf("Pre: %d\tPost: %d\n",preTreasureCount,postTreasureCount);
        if (preTreasureCount + 2 == postTreasureCount) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
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