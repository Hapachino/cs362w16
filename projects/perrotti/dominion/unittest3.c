/*
 * unittest3.c
 * This test is for the function "updateCoins()"
 * This test ensures that the updateCoins function returns the appropriate score.
 * Requirement 1: Appropriate value should be returned based on number of copper, silver, and gold
 * Solution: Create random hands up to the max hand (500), filled with random cards
 * Requirement 2: Appropriate value should be returned including the bonus count
 * Solution: Same as above, but add in a bonus value to the calculation
 * Requirement 3: All player state values should remain the same before and after the function
 * Solution: Ensure the player state does not change (cards in hand for example) before and after the function call
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
   
    printf("Testing updateCoins().\n");
    
    struct gameState g;
    struct gameState pre;
    /* Initialize basic game state information, and assign to new game */
    int r;
    int players = 2;
    int p;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    /* TEST 1,2,3 -  Testing for all players, with randomly assigned cards/bonus 
    Also, will validate that the game state ist he same after both operations*/
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
                int cardLimit = (rand() % MAX_HAND) + 1;
                g.handCount[p] = cardLimit;
                int randBonus = rand() % 50; // Create number of bonus points at random
                int i;
                for (i = 0; i < g.handCount[p]; i++) {
                    /* This will assign cards to the players hand at random. Will only use the first 10 to ensure plenty of coins */
                    g.hand[p][i] = (rand() % 10);
                }
                
                memcpy(&pre, &g, sizeof(struct gameState));
                int oracleResult = 0;
                int d;
                for (d = 0; d < cardLimit; d++) {
                    if(pre.hand[p][d] == copper) {
                        oracleResult += 1;
                    } else if (pre.hand[p][d] == silver){
                        oracleResult += 2;
                    } else if (pre.hand[p][d] == gold){
                        oracleResult += 3;
                    }
                }
                
                // Calculate final coin total and store in pre state
                oracleResult += randBonus;
                pre.coins = oracleResult;
                 
                // Retrieve updated coins state
                updateCoins(p, &g, randBonus);
                // Compare coin count
                printf("Player %d - Expect: %d, Received: %d\n", p, oracleResult, g.coins);
                assert(pre.coins == g.coins);
                // Compare structs to ensure they remained the same
                printf("Testing matching game states\n");
                assert(memcmp(&pre, &g, sizeof(struct gameState)) == 0);
            }
        }
    }
    printf("Finished all updatedCoins() tests succesfully!\n");
    return 0;
}
