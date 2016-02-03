/*
 * Unit test for isGameOver function
 *
 * Business Rules:
 *  1.	if the stack of province cards is empty, game is over
 *	2.	if three supply piles are empty, the game is over
 *	3.	if neither of these are true, the game continues
 *
 * unitTest2: unitTest2.c dominion.o rngs.o
 *      gcc -o unitTest2 -g unitTest2.c dominion.o rngs.o $(FLAGS)
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
    int i, p, new_game, isOver;
    int seed = 1000;
    int numPlayer = 1;
    int copper_coins, silver_coins, gold_coins;
    int province_count;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING isGameOver()\n");
    for(p = 0; p < numPlayer; ++p) {
        //tests if three supply piles are empty
        for(copper_coins = 0; copper_coins < 5; ++copper_coins) {
            for(silver_coins = 0; silver_coins < 5; ++silver_coins) {
                for(gold_coins = 0; gold_coins < 5; ++gold_coins) {
                    for(province_count = 0; province_count < 5; ++province_count) {
                        //clear the game state
                        memset(&G, 23, sizeof(struct gameState));
                        //initialize a new game
                        new_game = initializeGame(numPlayer, k, seed, &G);
                        //set game state
                        G.supplyCount[province] = province_count;
                        G.supplyCount[copper] = copper_coins;
                        G.supplyCount[silver] = silver_coins;
                        G.supplyCount[gold] = gold_coins;

                        //test if game is over
                        isOver = isGameOver(&G);
#if (NOISY_TEST == 1)
                        printf("----------------------\nProvince = %d, Copper coins = %d, Silver coins = %d, Gold coins = %d\n",
                               province_count, copper_coins, silver_coins, gold_coins);
                        if(isOver)
                            printf("Game over = YES\n");
                        else
                            printf("Game over = NO\n");
#endif
                    }
                }
            }
        }
    }

    printf("\nAll tests passed: isGameOver()\n");

    return 0;
}
