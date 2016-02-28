/*
 * unittest1.c
 * This test is for the function "isGameOver()"
 * This test ensures that this procedure works given a random generated game
 * state, and with sometimes specifically assigned supply stacks with 0 remaining.
 * Requirement 1: Game over state returns 1 if provinces remaining = 0
 * Solution: Initialize game state where provinces = 0. Test function.
 * Requirement 2: Game over state returns 1 if 3 supply stacks are 0
 * Solution: Initialize game state, and then randomly generate stack counts for cards selected.
 * Requirement 3: Provinces are not empty, and  1 or 2 supply stacks are empty
 * Solution: Test when 1 or 2 randomly selected stacks have 0 remaining cards
 * Requirement 4: Ensure gameState is the same before and after running the function (nothing should change)
 * Solution: Assert pre and post game states are equivalant. This will be tested on all
 *
 * TEST FAILS ON TEST 2 BECAUSE BUG FOUND!!! Unable to test 3 and 4 due to the asserts, so didn't implement.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main () {
    srand(time(NULL));
    int failCount1 = 0;
    int failCount2 = 0;
    int failCount3 = 0;
    int failCount4 = 0;
    struct gameState g;
    struct gameState pre;
    int i, r;
    int players = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int randSeed = rand() % 1000;
    
    printf("Starting test 1:\n");
    // TEST Requirement 1 (and 4)
    for (i = 0; i < 100; i++) {
        printf("Test 1: #%d - ", i);
        
        // Create gamestate, and then copy to pre state
        memset(&g, 0, sizeof(struct gameState));
        r = initializeGame(players, k, randSeed, &g);
        
        // Ensure the game state was created properly
        if (r == -1) {
            printf("Game state failed to initialize\n");
        } else {
            // Set provinces to zero
            g.supplyCount[province] = 0;
            // Copy a pre version of game state
            memcpy(&pre, &g, sizeof(struct gameState));
            int result = isGameOver(&g);
            printf("Expect: 1, Received: %d\n", result);
            if(result != 1) {
                printf(" FAIL \n");
                failCount1++;
            }
            printf("Testing matching game states\n");
            if(memcmp(&pre, &g, sizeof(struct gameState)) != 0) {
                printf(" FAIL \n");
                failCount2++;
            }
        }
    }
    
    // TEST Requirement 2 (and 4)
    // Running numerous tests to ensure most combos are covered
    for (i = 0; i < 10000; i++) {
        printf("Test 2: #%d - ", i);
        memset(&g, 0, sizeof(struct gameState));
        r = initializeGame(players, k, randSeed, &g);
        
        // Array to hold card taht we will be switching to 0
        int arr[3] = {-1, -1, -1};
        
        // Randomly select a card in the deck to be set to 0 remaining
        int y = 0;        
        while (y < 3) {
            arr[y] = rand() % 27;
            int w;
            int unique = 1;
            for (w = 0; w < 3; w++) {
                // Ensure not duplicating the cards to change
                if (y != w && arr[y] == arr[w]) {
                    unique = 0;
                }
            }
            // Ensure unique cards were chosen
            if (unique == 1) {
                y++;
            }
        }
        
        // Set the card count to 0 for the specified cards
        printf("Cards: %d %d %d - ", arr[0], arr[1], arr[2]);
        g.supplyCount[arr[0]] = 0;
        g.supplyCount[arr[1]] = 0;
        g.supplyCount[arr[2]] = 0;
        printf("%d %d %d", g.supplyCount[arr[0]], g.supplyCount[arr[1]], g.supplyCount[arr[2]]);
        
        // After cards are set up, copy game state over
        memcpy(&pre, &g, sizeof(struct gameState));
        
        // Ensure game state was createad properly
        if (r == -1) {
            printf("Game state failed to initialize\n");
        } else {
            // Check if the game is over 
            int result = isGameOver(&g);
            printf("Expect: 1, Received: %d\n", result);
            if(result != 1){
                printf(" FAIL \n");
                failCount3++;
            }
            printf("Testing matching game states\n");
            if(memcmp(&pre, &g, sizeof(struct gameState)) != 0) {
                printf(" FAIL \n");
                failCount4++;
            }
        }
    }
    int totalFails = failCount1 + failCount2 + failCount3 + failCount4;
    if (totalFails == 0) {
        printf("Finished all scoreFor() tests succesfully!\n");
    } else {
        printf("Finished all scoreFor() tests.\nFAILS 1: %d, FAILS 2: %d, FAILS 3: %d, FAILS 4: %d\n", failCount1, failCount2, failCount3, failCount4);
    }
    return 0;
}