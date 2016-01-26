/* -----------------------------------------------------------------------
 * test fullDeckCount()
 * 
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
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

    const char *cards[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
        "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
        "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
    };

    struct gameState G;
    int count;
    int result;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
    printf("========TESTING fullDeckCount():========\n");
#endif

    for (p = 0; p < numPlayer; p++)
    {
#if (NOISY_TEST == 1)
        printf("\nTesting for Player %d:\n", p);
#endif

        // Estates
        result = fullDeckCount(p, 1, &G);
#if (NOISY_TEST == 1)
        printf("estate result: %d\n", result);
#endif
        assert(result == 3);

        // Coppers
        result = fullDeckCount(p, 4, &G);
#if (NOISY_TEST == 1)
        printf("copper result: %d\n", result);
#endif
        assert(result == 7);

        // Test update of coppers (discard)
        count = 5;
        for (i = 0; i < count; i++) {
            G.discard[p][ G.discardCount[p] ] = copper;
            G.discardCount[p]++;
        }
        result = fullDeckCount(p, 4, &G);
#if (NOISY_TEST == 1)
        printf("updated copper result: %d\n", result);
#endif
        assert(result == 7 + count);

        // Test update of golds (hand)
        count = 10;
        for (i = 0; i < count; i++) {
            G.hand[p][ G.handCount[p] ] = gold;
            G.handCount[p]++;
        }
        result = fullDeckCount(p, 6, &G);
#if (NOISY_TEST == 1)
        printf("gold result: %d\n", result);
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
        printf("province result: %d\n", result);
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
        printf("smithy result: %d\n", result);
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
        printf("tribute result: %d\n", result);
#endif
        assert(result == count);

        // Test embargo (hand)
        count = 5;
        for (i = 0; i < count; i++) {
            G.hand[p][ G.handCount[p] ] = embargo;
            G.handCount[p]++;
        }
        result = fullDeckCount(p, 22, &G);
#if (NOISY_TEST == 1)
        printf("embargo result: %d\n", result);
#endif
        assert(result == count);

        // 27 types of cards
#if (NOISY_TEST == 1)
        printf("Totals of cards by type for Player %d:\n", p);
        for (i = 0; i < 27; i++) {
            result = fullDeckCount(p, i, &G);
            printf("Card count for %s: %d\n", cards[i], result);
        }
#endif
    }

    printf("\nAll tests passed!");

    return 0;
}
