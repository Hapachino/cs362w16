/*
 * unittest4.c
 * This test is for the function "scoreFor()"
 * This test ensures that the updateCoins function returns the appropriate score.
 * Requirement 1: Appropriate score should be returned based on curse, estate, duchy, province, and great hall cards.
 * Solution: Create an oracle that totals these cards in a players hands (which were assigned random)
 * Requirement 2: The Oracle and game accurately reflect points scored by owning a garden, based on total cards the player has
 * Solution: Need to ensure that both scoreFor() and the Oracle count total deck size accurately
 * Requirement 3: Ensure that the game state is not changed during this operation
 * Solution: Compare pre and post game states, and ensure that the scoreFor() function doesn't modify game state
 *
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
   
    printf("Testing scoreFor().\n");
    
    struct gameState g;
    struct gameState pre;
    /* Initialize basic game state information, and assign to new game */
    int r;
    int players = 2;
    int p;
    int k[10] = {adventurer, gardens, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    /* TEST 1,2,3 -  Testing for all players, with randomly assigned cards 
    Also, will validate that the game state is the same after both operations*/
    for (p = 0; p < players; p++) {
        int y;
        // How many times we want to run the test per player
        for (y = 0; y < 10000; y++) {
            // Create gamestate, and then copy to pre state
            memset(&g, 0, sizeof(struct gameState));
            r = initializeGame(players, k, ((rand() % 1000) + 1), &g);
            
            // Ensure the game state was created properly
            if (r == -1) {
                printf("Game state failed to initialize\n");
            } else {
                // Calculate the number of cards we will place in the hand, and place using for loop
                int handLimit = ((rand() % MAX_DECK ) / 3) + 1;
                int deckLimit = ((rand() % MAX_DECK ) / 3) + 1;
                int discardLimit = ((rand() % MAX_DECK ) / 3) + 1;
                g.handCount[p] = handLimit;
                g.deckCount[p] = deckLimit;
                g.discardCount[p] = discardLimit;
                int i;
                // Fill hand with random cards
                for (i = 0; i < g.handCount[p]; i++) {
                    /* Assign a random card out of the 27 possible cards */
                    g.hand[p][i] = (rand() % 27);
                }
                // Fill deck with random cards
                for (i = 0; i < g.deckCount[p]; i++) {
                    /* Assign a random card out of the 27 possible cards */
                    g.deck[p][i] = (rand() % 27);
                }
                // Fill discard with random cards
                for (i = 0; i < g.discardCount[p]; i++) {
                    /* Assign a random card out of the 27 possible cards */
                    g.discard[p][i] = (rand() % 27);
                }
      
                // Copy over game state and run the Oracle
                memcpy(&pre, &g, sizeof(struct gameState));
                int oracleResult = 0;
                int d;
                // Oracle runs a for loop on pre for each card type, and totals up the points
                for (d = 0; d < handLimit; d++) {
                    if(pre.hand[p][d] == curse) { 
                        oracleResult -= 1;
                    } else if (pre.hand[p][d] == estate) {
                        oracleResult += 1;
                    } else if (pre.hand[p][d] == duchy) {
                        oracleResult += 3;
                    } else if (pre.hand[p][d] == province) {
                        oracleResult += 6;
                    } else if (pre.hand[p][d] == great_hall) {
                        oracleResult += 1;
                    } else if (pre.hand[p][d] == gardens) {
                        oracleResult += ((pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p]) / 10);
                    }
                }
                for (d = 0; d < deckLimit; d++) {
                    if(pre.deck[p][d] == curse) { 
                        oracleResult -= 1;
                    } else if (pre.deck[p][d] == estate) {
                        oracleResult += 1;
                    } else if (pre.deck[p][d] == duchy) {
                        oracleResult += 3;
                    } else if (pre.deck[p][d] == province) {
                        oracleResult += 6;
                    } else if (pre.deck[p][d] == great_hall) {
                        oracleResult += 1;
                    } else if (pre.deck[p][d] == gardens) {
                        oracleResult += ((pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p]) / 10);
                    }
                }
                for (d = 0; d < discardLimit; d++) {
                    if(pre.discard[p][d] == curse) { 
                        oracleResult -= 1;
                    } else if (pre.discard[p][d] == estate) {
                        oracleResult += 1;
                    } else if (pre.discard[p][d] == duchy) {
                        oracleResult += 3;
                    } else if (pre.discard[p][d] == province) {
                        oracleResult += 6;
                    } else if (pre.discard[p][d] == great_hall) {
                        oracleResult += 1;
                    } else if (pre.discard[p][d] == gardens) {
                        oracleResult += ((pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p]) / 10);
                    }
                }
                
                // Retrieve updated coins state
                int funcResult = scoreFor(p, &g);
                // Compare coin count
                printf("Player %d - Expect: %d, Received: %d\n", p, oracleResult, funcResult);
                assert(oracleResult == funcResult);
                // Compare structs to ensure they remained the same
                printf("Testing matching game states\n");
                assert(memcmp(&pre, &g, sizeof(struct gameState)) == 0);
            }
        }
    }
    printf("Finished all scoreFor() tests succesfully!\n");
    return 0;
}
