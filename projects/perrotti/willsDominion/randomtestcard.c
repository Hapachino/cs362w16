/*
 * randomtestcard.c
 * This test is for the function "outpost" card, controlled by "cardEffect()" function
 * This test ensures that when the outpost card is played, the outpost flag is set within the system. It also
 * ensures that the card is properly discarded, and the player hand, discard, and deck are appropriately incremented
 * Requirement 1: Ensure outpost flag has been set by playing the outpost card
 * Solution: Assert that the outpost flag is set in both pre and post game states
 * Requirement 2: Ensure current player has the appropriate card counts after discarding the card
 * Solution: Assert the card count between Oracle and game state are the same
 * Requirement 3: Ensure entire gamestate matches between the two systems after the call
 * Solution: This will ensure that no other random data was accidently changed, including other players cards
 * Requirement 4: The outpost should be set to 0 after initializing the game
 * Solution: Ensure outpost is 0 after the game is initialized
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
    int failCount0 = 0;
    int failCount1 = 0;
    int failCount2 = 0;
    int failCount3 = 0;
    printf("Testing outpost card.\n");
    
    struct gameState g;
    struct gameState pre;
    /* Initialize basic game state information, and assign to new game */
    int r;
    int players = 4;
    int p;
    int k[10] = {adventurer, gardens, village, outpost, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    /* TEST 1,2,3,4 -  Testing for all players, with randomly assigned hand, discard, and deck 
    Also, will validate that the game state is the same after both operations*/
    for (p = 0; p < players; p++) {
        int y;
        // How many times we want to run the test per player
        for (y = 0; y < 1000; y++) {
            // Create gamestate, and then copy to pre state
            memset(&g, 0, sizeof(struct gameState));
            r = initializeGame(players, k, ((rand() % 1000) + 1), &g);
            g.whoseTurn = p;
            
            // Ensure the game state was created properly
            if (r == -1) {
                printf("Game state failed to initialize\n");
            } else {
                
                // Test 4, ensure the outpost is set to 0 when starting the game
                printf("Test 4 - Testing outpost played is 0 at game initialize");
                if(g.outpostPlayed != 0) {
                    printf(" - FAIL \n");
                    failCount0++;
                } else {
                    printf(" - PASS\n");
                }
                
                /* Place a random number of cards into the players hand */
                int handLimit = (((rand() % MAX_HAND) / 3) + 1);
                int deckLimit = (((rand() % MAX_HAND) / 3) + 1);
                int discardLimit = (((rand() % MAX_HAND) / 3) + 1);
                g.handCount[p] = handLimit;
                g.deckCount[p] = deckLimit;
                g.discardCount[p] = discardLimit;
                int i;
                // Fill with random cards
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
                
                // Ensure player has a outpost card to play
                g.hand[p][i] = outpost;
      
                // Copy over game state and run the Oracle
                memcpy(&pre, &g, sizeof(struct gameState));
                
                // Oracle runs to get the results we would expect
                // Set the outpost flag (90% of the time)
                if ((rand() % 10) >= 1) {
                    pre.outpostPlayed += 1;
                    // Discard the outpost card
                    discardCard(0, p, &pre, 0);
              
                    // Retrieve game status after calling "cardEffect(outpost,...)"
                    cardEffect(g.hand[p][i], 0, 0, 0, &g, 0, 0);
                }
                
                // TEST1: Ensure outpost flag has been set if appropriate in both systems. 90% chance outpost card played
                printf("Test 1 - Outpost Flag Set - ");
                printf("Player %d - Expect: %d Results: %d", p, pre.outpostPlayed, g.outpostPlayed);
                if(pre.outpostPlayed != g.outpostPlayed) {
                    printf(" - FAIL \n");
                    failCount1++;
                } else {
                    printf(" - PASS\n");
                }
                
                // TEST2: Ensure current player total cards total between the Oracle and the function
                int tmpOracle = pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p];
                int tmpGame = g.handCount[p] + g.deckCount[p] + g.discardCount[p];
                printf("Test 2 - Testing matching card counts - Expected: %d, Received %d", tmpOracle, tmpGame);
                if(tmpOracle != tmpGame) {
                    printf(" - FAIL \n");
                    failCount2++;
                } else {
                    printf(" - PASS\n");
                }
                
                // TEST3: Ensure entire game state matches
                printf("Test 3 - Testing matching game states");
                if(memcmp(&pre, &g, sizeof(struct gameState)) != 0) {
                    printf(" - FAIL \n");
                    failCount3++;
                } else {
                    printf(" - PASS\n");
                }
            }
        }
    }
    int totalFails = failCount0 + failCount1 + failCount2 + failCount3;
    if (totalFails == 0) {
        printf("Finished all outpost card tests succesfully!\n");
    } else {
        printf("Finished all outpost card tests.\nFAILS 0: %d, FAILS 1: %d, FAILS 2: %d, FAILS 3: %d\n", failCount0, failCount1, failCount2, failCount3);
    }
    return 0;
}
