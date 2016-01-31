/*
 * Unit test for updateCoins function
 *
 * unitTest1: unitTest1.c dominion.o rngs.o
 *      gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o $(FLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove prinftf's from output
#define NOISY_TEST 1

int main() {
    int i, p, new_game;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 5;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int handCount;
    int maxHandCount = 5;
    int copper_coins[MAX_HAND];
    int silver_coins[MAX_HAND];
    int gold_coins[MAX_HAND];

    for(i = 0; i < MAX_HAND; ++i) {
        copper_coins[i] = copper;
        silver_coins[i] = silver;
        gold_coins[i] = gold;
    }

    printf("TESTING updateCoins()\n");
    for(p = 0; p < numPlayer; ++p) {
        for(handCount = 1; handCount < maxHandCount; ++handCount) {
            for(bonus = 0; bonus < maxBonus; ++bonus) {
                //clear the game state
                memset(&G, 23, sizeof(struct gameState));
                //initialize a new game
                new_game = initializeGame(numPlayer, k, seed, &G);
                //set number of cards on hand
                //will loop through for every 5 hands
                G.handCount[p] = handCount;

                //set all cards to copper
                memcpy(G.hand[p], copper_coins, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("----------------------\nCOPPER\n");
                printf("Coins before bonus + bonus coins = Total (%d + %d = %d) - Expected coins = %d\n",
                       G.coins - bonus, bonus, G.coins, handCount * 1 + bonus);
#endif

                //set all cards to silver
                memcpy(G.hand[p], silver_coins, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("SILVER\n");
                printf("Coins before bonus + bonus coins = Total (%d + %d = %d) - Expected coins = %d\n",
                       G.coins - bonus, bonus, G.coins, handCount * 2 + bonus);
#endif

                //set all cards to gold
                memcpy(G.hand[p], gold_coins, sizeof(int) * handCount);
                updateCoins(p, &G, bonus);
#if (NOISY_TEST == 1)
                printf("GOLD\n");
                printf("Coins before bonus + bonus coins = Total (%d + %d = %d) - Expected coins = %d\n",
                       G.coins - bonus, bonus, G.coins, handCount * 3 + bonus);
#endif

            }
        }
    }

    printf("\nAll tests passed: updateCoins()\n");

    return 0;
}
