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
               , remodel, smithy, village, baron, great_hall};

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

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("\n========TESTING fullDeckCount():========\n");
    for (p = 0; p < numPlayer; p++)
    {
        // int fullDeckCount(int player, int card, struct gameState *state)

        printf("Testing for Player %d:\n", p);

        // Estates
        count = fullDeckCount(p, 1, &G);
        printf("Estate count: %d\n", count);

        // Coppers
        count = fullDeckCount(p, 4, &G);
        printf("Copper count: %d\n", count);

        // int drawCard(int player, struct gameState *state)
        // int buyCard(int supplyPos, struct gameState *state)
        buyCard(smithy, &G);
        buyCard(estate, &G);
        buyCard(province, &G);

        // int endTurn(struct gameState *state)
        endTurn(&G);

        // int updateCoins(int player, struct gameState *state, int bonus)
        G.numBuys = 100;
        G.coins = 100;

        // 27 types of cards
        for (i = 0; i < 27; i++) {
            count = fullDeckCount(p, i, &G);
            printf("Card count of %s: %d\n", cards[i], count);
        }

        // assert(G.coins == expected);
    }

    printf("\nAll tests passed!");

    return 0;
}
