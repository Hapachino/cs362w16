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
    // set seed for random numbers
    srand(3);

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, tribute, embargo};

    // int k[27] = {curse, estate, duchy, province, copper, silver, gold, adventurer, council_room,
    //     feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward,
    //     tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map
    // };

    const char *cards[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer", "council_room",
        "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
        "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"
    };

    struct gameState G;
    int count;
    int result;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("\n========TESTING fullDeckCount():========\n");
    for (p = 0; p < numPlayer; p++)
    {
        // int fullDeckCount(int player, int card, struct gameState *state)

        printf("Testing for Player %d:\n", p);

        // Enable buy phases and coins
        G.numBuys = 1000;
        G.coins = 1000;

        // Estates
        result = fullDeckCount(p, 1, &G);
        printf("estate result: %d\n", result);
        assert(result == 3);

        // Coppers
        result = fullDeckCount(p, 4, &G);
        printf("copper result: %d\n", result);
        assert(result == 7);

        // int buyCard(int supplyPos, struct gameState *state)

        // Test update of coppers
        count = 5;
        for (i = 0; i < count; i++) {
            buyCard(copper, &G);
        }
        result = fullDeckCount(p, 4, &G);
        printf("updated copper result: %d\n", result);
        assert(result == 7 + count);

        // Test update of golds
        count = 10;
        for (i = 0; i < count; i++) {
            buyCard(gold, &G);
        }
        result = fullDeckCount(p, 6, &G);
        printf("gold result: %d\n", result);
        assert(result == count);

        // Test province
        count = 2;
        for (i = 0; i < count; i++) {
            buyCard(province, &G);
        }
        result = fullDeckCount(p, 3, &G);
        printf("province result: %d\n", result);
        assert(result == count);

        // Test smithy
        count = 3;
        for (i = 0; i < count; i++) {
            buyCard(smithy, &G);
        }
        result = fullDeckCount(p, 13, &G);
        printf("smithy result: %d\n", result);
        assert(result == count);

        // Test tribute
        count = 4;
        for (i = 0; i < count; i++) {
            buyCard(tribute, &G);
        }
        result = fullDeckCount(p, 19, &G);
        printf("tribute result: %d\n", result);
        assert(result == count);

        // Test embargo
        count = 5;
        for (i = 0; i < count; i++) {
            buyCard(embargo, &G);
        }
        result = fullDeckCount(p, 22, &G);
        printf("embargo result: %d\n", result);
        assert(result == count);

        // int endTurn(struct gameState *state)
        endTurn(&G);

        // Enable buy phases and coins
        G.numBuys = 1000;
        G.coins = 1000;

        // 27 types of cards
        printf("Totals of cards by type for Player %d:\n", p);
        for (i = 0; i < 27; i++) {
            result = fullDeckCount(p, i, &G);
            printf("Card count for %s: %d\n", cards[i], result);
        }
    }

    printf("\nAll tests passed!");

    return 0;
}
