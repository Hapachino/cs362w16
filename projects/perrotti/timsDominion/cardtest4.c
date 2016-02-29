/*
 * cardtest4.c
 * This test is for the function "playVillage()"
 * This test ensures that when the village card is played, the outpost flag is set within the system. It also
 * ensures that the card is properly discarded, and the player hand, discard, and deck are appropriately incremented
 * Requirement 1: Ensure 1 new card is added to the current players hand, but one was discareded (net 0)
 * Solution: Assert that starting hand size equals ending hand size, and equal between both game states
 * Requirement 2: Ensure current player has two actions added after playing the card
 * Solution: Since actions are not removed until after card effects, expect +2 actions over the starting actions
 * Requirement 3: Ensure entire card state matches for all other players matches
 * Solution: Loop through the decks of all other players to make sure cards were not changed for them
 * Not able to check entire game state due to the random nature of shuffling the discard pile in case no cards 
 * were available after draw took place, so just going to check deck counts
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
    
    /* TEST 1,2,3 -  Testing for all players, with randomly assigned hand, discard, and deck 
    Also, will validate that the game state is the same after both operations*/
    for (p = 0; p < players; p++) {
        int y;
        // How many times we want to run the test per player
        for (y = 0; y < 500; y++) {
            // Create gamestate, and then copy to pre state
            memset(&g, 0, sizeof(struct gameState));
            r = initializeGame(players, k, ((rand() % 1000) + 1), &g);
            g.whoseTurn = p;
            
            // Ensure the game state was created properly
            if (r == -1) {
                printf("Game state failed to initialize\n");
            } else {
                /* Place a random number of cards into the players hand */
                int handLimit = ((rand() % 10) + 1);
                int deckLimit = ((rand() % 10) + 1);
                int discardLimit = ((rand() % 10) + 1);
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
                g.hand[p][i] = village;
                
                // Copy over game state and run the Oracle
                memcpy(&pre, &g, sizeof(struct gameState));
                
                int originalActions = pre.numActions;
                
                // Oracle runs to get the results we would expect
                // Draw a card for the current player
                drawCard(p, &pre);
                // Add two actions for the current player
                pre.numActions += 2;
                // Discard the village card
                discardCard(0, p, &pre, 0);
                
                // Run normal game function
                cardEffect(15, 0, 0, 0, &g, 0, 0);
                
                // TEST1: Ensure 1 additional card was added to the players hand, but that one card was discareded (net 0)
                printf("Test 1 - Card Added/Card Removed - ");
                printf("Player %d - Expect: %d -> %d Results: %d -> %d\n", p, handLimit, pre.handCount[p], handLimit, g.handCount[p]);
                if(handLimit != pre.handCount[p] || pre.handCount[p] != g.handCount[p]) {
                    printf(" - FAIL \n");
                    failCount1++;
                } else {
                    printf(" - PASS\n");
                }
                
                // TEST2: Ensure two actions were added. Should bet NET 2 because we don't call the actions-- in our scope
                printf("Test 2 - Testing Action Count - Expected: %d, Received %d", pre.numActions, g.numActions);
                if(pre.numActions != g.numActions || originalActions != (pre.numActions - 2)) {
                    printf(" - FAIL \n");
                    failCount2++;
                } else {
                    printf(" - PASS\n");
                }
                
                // TEST3: Ensure other players hands are not corrupt by comparing card counts before and after
                printf("Test 3 - Other player card count - ");
                for (i = 0; i < players; i++) {
                    if (i == p) {
                        // do nothing because this isn't the other players
                    } else {
                        printf("Player %d - Expect: %d, %d, %d, Results: %d, %d, %d", i, pre.handCount[i], pre.deckCount[i], pre.discardCount[i], g.handCount[i], g.deckCount[i], g.discardCount[i]); 
                        if(pre.handCount[i] != g.handCount[i] || pre.deckCount[i] != g.deckCount[i] || pre.discardCount[i] != g.discardCount[i]) {
                            printf(" - FAIL \n");
                            failCount3++;
                        } else {
                            printf(" - PASS\n");
                        }
                    }
                }
            }
        }
    }
    int totalFails = failCount1 + failCount2 + failCount3;
    if (totalFails == 0) {
        printf("Finished all playVillage() tests succesfully!\n");
    } else {
        printf("Finished all playVillage() tests.\nFAILS 1: %d, FAILS 2: %d, FAILS 3: %d\n", failCount1, failCount2, failCount3);
    }
    return 0;
}
