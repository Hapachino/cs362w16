/*Jonathan Lagrew
 *test fullDeckCount()
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
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, embargo};

    // const char *cards[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
    //     "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
    //     "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
    // };

    struct gameState G;
    int copperCount, estateCount;
    int count;
    int result;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
    printf("----------------- TESTING fullDeckCount():\n");
#endif

    for (p = 0; p < numPlayer; p++)
    {
#if (NOISY_TEST == 1)
        printf("\n----------------- Testing for Player %d:\n", p);
        printf("Adding the following to\n");
        printf("    deck:         5 coppers\n");
        printf("    hand:         10 golds\n");
        printf("    discard pile: 2 provinces\n");
        printf("    hand:         3 smithys\n");
        printf("    discard pile: 4 tributes\n");
        printf("    deck:         5 embargos\n");
#endif

        // Estates
        estateCount = 3;
        result = fullDeckCount(p, 1, &G);
#if (NOISY_TEST == 1)
        printf("estate result: %d, expected: %d\n", result, estateCount);
#endif
        assert(result == estateCount);

        // Coppers
        copperCount = 7;
        result = fullDeckCount(p, 4, &G);
#if (NOISY_TEST == 1)
        printf("copper result: %d, expected: %d\n", result, copperCount);
#endif
        assert(result == copperCount);

        // Test update of coppers (deck)
        count = 5;
        for (i = 0; i < count; i++) {
            G.deck[p][ G.deckCount[p] ] = copper;
            G.deckCount[p]++;
        }
        copperCount = copperCount + count;
        result = fullDeckCount(p, 4, &G);
#if (NOISY_TEST == 1)
        printf("updated copper result: %d, expected: %d\n", result, copperCount);
#endif
        assert(result == copperCount);

        // Test update of golds (hand)
        count = 10;
        for (i = 0; i < count; i++) {
            G.hand[p][ G.handCount[p] ] = gold;
            G.handCount[p]++;
        }
        result = fullDeckCount(p, 6, &G);
#if (NOISY_TEST == 1)
        printf("gold result: %d, expected: %d\n", result, count);
#endif
        assert(result == count);

        // Test province (discard)
        count = 2;
        for (i = 0; i < count; i++) {
            G.discard[p][ G.discardCount[p] ] = province;
            G.discardCount[p]++;
        }
        result = fullDeckCount(p, 3, &G);
#if (NOISY_TEST == 1)
        printf("province result: %d, expected: %d\n", result, count);
#endif
        assert(result == count);

        // Test smithy (hand)
        count = 3;
        for (i = 0; i < count; i++) {
            G.hand[p][ G.handCount[p] ] = smithy;
            G.handCount[p]++;
        }
        result = fullDeckCount(p, 13, &G);
#if (NOISY_TEST == 1)
        printf("smithy result: %d, expected: %d\n", result, count);
#endif
        assert(result == count);

        // Test tribute (discard)
        count = 4;
        for (i = 0; i < count; i++) {
            G.discard[p][ G.discardCount[p] ] = tribute;
            G.discardCount[p]++;
        }
        result = fullDeckCount(p, 19, &G);
#if (NOISY_TEST == 1)
        printf("tribute result: %d, expected: %d\n", result, count);
#endif
        assert(result == count);

        // Test embargo (deck)
        count = 5;
        for (i = 0; i < count; i++) {
            G.deck[p][ G.deckCount[p] ] = embargo;
            G.deckCount[p]++;
        }
        result = fullDeckCount(p, 22, &G);
#if (NOISY_TEST == 1)
        printf("embargo result: %d, expected: %d\n", result, count);
#endif
        assert(result == count);

        // 27 types of cards
#if (NOISY_TEST == 1)
        // printf("Totals of cards by type for Player %d:\n", p);
        // for (i = 0; i < 27; i++) {
        //     result = fullDeckCount(p, i, &G);
        //     printf("Card count for %s: %d\n", cards[i], result);
        // }
#endif
    }

    printf("\nAll tests passed!\n");

    return 0;
}
