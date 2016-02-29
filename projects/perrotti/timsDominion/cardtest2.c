/*
 * cardtest2.c
 * This test is for the function "adventurer" card, controlled by "playAdventurer()" function
 * This test ensures that the playAdventurer() function returns two treasure cards (if available) to the users hand, 
 * and appropriately handles the deck and discard piles.
 * Requirement 1: Ensure other players hands and decks have not been modified by adventurer operation
 * Solution: Assert all remaining players have the same number of cards as they did before the operation.
 * Requirement 2: Current player should receive up to 2 treasure cards (can be less)
 * Solution: Create an Oracle that adds up to 2 cards to users hands. Compare hand count of both functions
 * Requirement 3: Ensure current player total cards (hand, discard, deck) match between game and Oracle
 * Solution: Add up the three counts and compare. Can't compare individually because of random shuffling.
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
    int failCount4 = 0;
    int failCount5 = 0;
    printf("Testing playAdventurer().\n");
    
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
        for (y = 0; y < 5000; y++) {
            // Create gamestate, and then copy to pre state
            memset(&g, 0, sizeof(struct gameState));
            r = initializeGame(players, k, ((rand() % 1000) + 1), &g);
            g.whoseTurn = p;
            
            // Ensure the game state was created properly
            if (r == -1) {
                printf("Game state failed to initialize\n");
            } else {
                /* Calculate the number of cards we will place in the hand, and place using for loop
                Made high enough that you will often have enough coins, but not always */
                int handLimit = ((rand() % 10) + 1);
                int deckLimit = ((rand() % 15) + 1);
                int discardLimit = ((rand() % 15) + 1);
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
                
                // Ensure player has a adventurer card to play
                g.hand[p][i] = adventurer;
      
                // Copy over game state and run the Oracle
                memcpy(&pre, &g, sizeof(struct gameState));
                // Oracle runs to get the results we would expect
                // Draw three cards
                int treasure = 0; // Counts treasure cards drawn
                int shuffleCount = 0;
                int curCard; // Stores info on card drawn
                
                // Figure out how many treasure cards were originally in hand
                int originalHandTreasureCount = 0;
                int d;
                for (d = 0; d < handLimit; d++) {
                    if(pre.hand[p][d] == copper) {
                        originalHandTreasureCount += 1;
                    } else if (pre.hand[p][d] == silver){
                        originalHandTreasureCount += 1;
                    } else if (pre.hand[p][d] == gold){
                        originalHandTreasureCount += 1;
                    }
                }
                
                while(treasure < 2) {
                    //if the deck is empty we need to shuffle discard and add to deck
                    if (pre.deckCount[p] < 1 && shuffleCount < 1){
                      shuffle(p, &pre);
                      shuffleCount++;
                    } else if (shuffleCount >= 1) {
                        break; // Only shuffle and go through deck once. This avoids never ending loop
                    }
                    drawCard(p, &pre);
                    //top card of hand is most recently drawn card.
                    curCard = pre.hand[p][pre.handCount[p]-1];
                    if (curCard == copper || curCard == silver || curCard == gold) {
                        treasure++;
                    }
                    else {
                        pre.discard[p][pre.discardCount[p]] = curCard;
                        pre.discardCount[p]++;
                        pre.hand[p][pre.handCount[p] - 1] = -1;
                        pre.handCount[p]--;
                    }
                }
                
                // Figure out how many treasure cards were originally in hand
                int oracleHandTreasureCount = 0;
                for (d = 0; d < pre.handCount[p]; d++) {
                    if(pre.hand[p][d] == copper) {
                        oracleHandTreasureCount += 1;
                    } else if (pre.hand[p][d] == silver){
                        oracleHandTreasureCount += 1;
                    } else if (pre.hand[p][d] == gold){
                        oracleHandTreasureCount += 1;
                    }
                }
                
                // Retrieve game status after calling "playAdventurer"
                int temphand[1000];
                playAdventurer(p, &g, 0, temphand, 0);
                
                // Figure out how many treasure cards are in hand after running playAdventurer
                int treasuresFromPlaySmithy = 0;
                for (d = 0; d < g.handCount[p]; d++) {
                    if(g.hand[p][d] == copper) {
                        treasuresFromPlaySmithy += 1;
                    } else if (g.hand[p][d] == silver){
                        treasuresFromPlaySmithy += 1;
                    } else if (g.hand[p][d] == gold){
                        treasuresFromPlaySmithy += 1;
                    }
                }
                
                // TEST1: Ensure other players hands are not corrupt by comparing card counts before and after
                printf("Test 1 - Other player card count - ");
                for (i = 0; i < players; i++) {
                    if (i == p) {
                        // do nothing because this isn't the other players
                    } else {
                        printf("Player %d - Expect: %d, %d, %d, Results: %d, %d, %d", i, pre.handCount[i], pre.deckCount[i], pre.discardCount[i], g.handCount[i], g.deckCount[i], g.discardCount[i]); 
                        if(pre.handCount[i] != g.handCount[i] || pre.deckCount[i] != g.deckCount[i] || pre.discardCount[i] != g.discardCount[i]) {
                            printf(" FAIL \n");
                            failCount1++;
                        } else {
                            printf(" - PASS\n");
                        }
                    }
                }
                
                // TEST2: Ensure current player received up to 2 treasure cards
                printf("Test 2 - Current player gets up to 2 treasure cards - ");
                printf("Player %d - Starting Treasure: %d, Expected Treasure: %d, Function Treasure: %d", p, originalHandTreasureCount, oracleHandTreasureCount, treasuresFromPlaySmithy);
                // Ensure oracle did not provide more than 2 treasures
                if(oracleHandTreasureCount - 2 > originalHandTreasureCount) {
                    printf(" FAIL \n");
                    failCount2++;
                } else {
                    printf(" - PASS\n");
                }
                // Ensure game did not award more than 2 treasures
                if(treasuresFromPlaySmithy - 2 > originalHandTreasureCount) {
                    printf(" FAIL \n");
                    failCount3++;
                } else {
                    printf(" - PASS\n");
                }
                // Ensure game and oracle match
                if(oracleHandTreasureCount != treasuresFromPlaySmithy) {
                    printf(" FAIL \n");
                    failCount4++;
                } else {
                    printf(" - PASS\n");
                }
                
                // TEST3: Ensure current player total cards total between the Oracle and the function
                int tmpOracle = pre.handCount[p] + pre.deckCount[p] + pre.discardCount[p];
                int tmpGame = g.handCount[p] + g.deckCount[p] + g.discardCount[p];
                printf("Test 3 - Testing matching card counts - Expected: %d, Received %d", tmpOracle, tmpGame);
                if(tmpOracle != tmpGame) {
                    printf(" FAIL \n");
                    failCount5++;
                } else {
                    printf(" - PASS\n");
                }
            }
        }
    }
    int totalFails = failCount1 + failCount2 + failCount3 + failCount4 + failCount5;
    if (totalFails == 0) {
        printf("Finished all playAdventurer() card tests succesfully!\n");
    } else {
        printf("Finished all playAdventurer() card tests.\nFAILS 1: %d, FAILS 2: %d, FAILS 3: %d, FAILS 4: %d, FAILS 5: %d\n", failCount1, failCount2, failCount3, failCount4, failCount5);
    }
    return 0;
}
