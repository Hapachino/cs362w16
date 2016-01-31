/*Jonathan Lagrew
 *test scoreFor()
 *Notes: 
 *Testing that the score is calculated correctly for each curse, estate,
 *duchy, province, great hall or gardens. 
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, great_hall, feast, gardens, mine, remodel, smithy, village, tribute, embargo};   
    struct gameState G;
    int estateCount, duchyCount, provinceCount, ghCount, gardensCount, curseCount; // counter for cards
    int result; // test result value
    int score; // score calculation 
    int deck_discard_hand; // to keep track of garden card effect
    bool pass = true; // bool for pass or fail
    int failed = 0;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // ----PLAYER 0-----
    p = 0;

#if (NOISY_TEST == 1)
    printf("TESTING scoreFor():\n");
    printf("\nTest 1 - Player %d:\n", p);
    printf("Putting in the discard pile:\n");
    printf("    1 duchy\n");
    printf("    2 provinces\n");
    printf("    5 great halls\n");
    printf("    4 gardens\n");
    printf("    2 curses\n");
#endif
    estateCount = 3; // 3 from initialization 
    duchyCount = 1; // duchy
    G.discard[p][ G.discardCount[p] ] = duchy;
    G.discardCount[p]++;
	
    provinceCount = 2; // province
    for (i = 0; i < provinceCount; i++) {
        G.discard[p][ G.discardCount[p] ] = province;
        G.discardCount[p]++;
    }

    ghCount = 5; // great hall
    for (i = 0; i < ghCount; i++) {
        G.discard[p][ G.discardCount[p] ] = great_hall;
        G.discardCount[p]++;
    }

    gardensCount = 4; // gardens
    for (i = 0; i < gardensCount; i++) {
        G.discard[p][ G.discardCount[p] ] = gardens;
        G.discardCount[p]++;
    }

    curseCount = 2; // curse
    for (i = 0; i < curseCount; i++) {
        G.discard[p][ G.discardCount[p] ] = curse;
        G.discardCount[p]++;
    }

    result = scoreFor(p, &G); // Storing scoreFor() test in result
    
    score = 0; // Calculate correct score to compare to result 
    score = score + (curseCount * -1);
    score = score + estateCount;
    score = score + (duchyCount * 3);
    score = score + (provinceCount * 6);
    score = score + ghCount;
#if (NOISY_TEST == 1)
    printf("deckCount: %d\n", G.deckCount[p]);
    printf("discardCount: %d\n", G.discardCount[p]);
    printf("handCount: %d\n", G.handCount[p]);
#endif
    deck_discard_hand = G.deckCount[p] + G.discardCount[p] + G.handCount[p];
    score = score + (deck_discard_hand / 10 * gardensCount);

    // Verify
#if (NOISY_TEST == 1)
    printf("Player %d score: %d, expected: %d\n", p, result, score);
#endif
    // Assert here halts program execution
    // assert(result == score);
    if (result != score) {
        pass = false;
        failed++;
    }

	
    // ------PLAYER 1------
    p = 1;

    // Test scoreFor()
    result = scoreFor(p, &G);

    // From initializeGame()
    curseCount = 0;
    estateCount = 3;
    duchyCount = 0;
    provinceCount = 0;
    ghCount = 0;
    gardensCount = 0;

    // Calculate correct score
    score = 0;
    score = score + (curseCount * -1);
    score = score + estateCount;
    score = score + (duchyCount * 3);
    score = score + (provinceCount * 6);
    score = score + ghCount;
#if (NOISY_TEST == 1)
    printf("\n----------------- Test 2 - Player %d:\n", p);
    printf("No changes and all cards in deck:\n");
    printf("deckCount: %d\n", G.deckCount[p]);
    printf("discardCount: %d\n", G.discardCount[p]);
    printf("handCount: %d\n", G.handCount[p]);
#endif
    deck_discard_hand = G.deckCount[p] + G.discardCount[p] + G.handCount[p];
    score = score + (deck_discard_hand / 10 * gardensCount);

    // Verify
#if (NOISY_TEST == 1)
    printf("Player %d score: %d, expected: %d\n", p, result, score);
#endif
    if (result != score) {
        pass = false;
        failed++;
    }
    if (pass) {
        printf("\nAll tests passed!\n");
    }
    else {
        printf("\n%d/2 test(s) failed!\n", failed);
    }

    return 0;
}
