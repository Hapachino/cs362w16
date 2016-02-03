/*
 * cardtest1.c
 * This test is for the function "smithy" card, controlled by "playSmithy()" function
 * This test ensures that the playSmithy() function places the appropriate number of cards in the players hand.
 * Requirement 1: Ensure other players hands and decks have not been modified by the smithy operation
 * Solution: Assert all remaining players have the same number of cards as they did before the operation.
 * Requirement 2: Current player should receive exactly 3 cards when playing this card
 * Solution: Create an Oracle that adds 3 cards to the players hand from the deck, using the shuffle function if required.
 * Requirement 3: Ensure no state change occured for other portions of the game, by memcmp before and after
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
   
    printf("Testing playSmithy().\n");
    
    struct gameState g;
    struct gameState pre;
    /* Initialize basic game state information, and assign to new game */
    int r;
    int players = 4;
    int p;
    int k[10] = {adventurer, gardens, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    
    /* TEST 1,2,3 -  Testing for all players, with randomly assigned hand, discard, and deck 
    Also, will validate that the game state is the same after both operations*/
    for (p = 0; p < players; p++) {
        int y;
        // How many times we want to run the test per player
        for (y = 0; y < 10000; y++) {
            // Create gamestate, and then copy to pre state
            memset(&g, 0, sizeof(struct gameState));
            r = initializeGame(players, k, ((rand() % 1000) + 1), &g);
            g.whoseTurn = p;
            
            // Ensure the game state was created properly
            if (r == -1) {
                printf("Game state failed to initialize\n");
            } else {
                // Calculate the number of cards we will place in the hand, and place using for loop
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
                
                // Ensure player has a smithy card to play
                g.hand[p][i] = smithy;
      
                // Copy over game state and run the Oracle
                memcpy(&pre, &g, sizeof(struct gameState));
                // Oracle runs to get the results we would expect
                // Draw three cards
                drawCard(p, &pre);
                drawCard(p, &pre);
                drawCard(p, &pre);
                // Discard the smithy card
                discardCard(0, p, &pre, 0);
                
                // Retrieve game status after calling "playSmithy"
                playSmithy(&g, 0);
                
                // TEST1: Ensure other players hands are not corrupt by comparing card counts before and after
                printf("Test 1 - Other player card count - ");
                for (i = 0; i < players; i++) {
                    
                    if (i == p) {
                        // do nothing because this isn't the other players
                    } else {
                        printf("Player %d - Expect: %d, %d, %d, Results: %d, %d, %d", i, pre.handCount[i], pre.deckCount[i], pre.discardCount[i], g.handCount[i], g.deckCount[i], g.discardCount[i]); 
                        assert(pre.handCount[i] == g.handCount[i]);
                        assert(pre.deckCount[i] == g.deckCount[i]);
                        assert(pre.discardCount[i] == g.discardCount[i]);
                    }
                }
                printf(" - PASS\n");
                
                // TEST2: Ensure player received 3 cards, and discard, deck, and hand are same size in all scenarios
                printf("Test 2 - Current player gets 3 cards - ");
                printf("Player %d - Expect: %d, %d, %d, Received: %d, %d, %d", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], g.handCount[p], g.deckCount[p], g.discardCount[p]);
                assert(pre.handCount[p] == g.handCount[p]);
                assert(pre.deckCount[p] == g.deckCount[p]);
                assert(pre.discardCount[p] == g.discardCount[p]);
                printf(" - PASS\n");
                // TEST3: Ensure entire game state matches
                printf("Test 3 - Testing matching game states\n");
                assert(memcmp(&pre, &g, sizeof(struct gameState)) == 0);
                printf(" - PASS\n");
            }
        }
    }
    printf("Finished all playSmithy() tests succesfully!\n");
    return 0;
}
