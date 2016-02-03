
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 5;
    int deckSize = 0;
    int player1 = 0;
    int result = 0;

    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING buyCard():\n");
    printf("notes: successful = 0, failed to buy = -1.\n");

    //This function works by using state->coins, and state->numBuys to do it's work
    //Thus, there is no reason to test more than one player
    
    printf("Try to buy a silver with 3 coins, and 1 buy.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.coins = 3;
    testG.numBuys = 1;
    result = buyCard(silver, &testG);
    printf("buyCard() was successful = %d, expected = %d\n", result, 0);
    assert(result == 0);
    printf("coins remaining = %d, expected = %d\n", testG.coins, 0);
    assert(testG.coins == 0);
    printf("buys remaining = %d, expected = %d\n", testG.numBuys, 0);
    assert(testG.numBuys == 0);
    printf("last card is of type: %d, expected: %d\n", testG.hand[player1][testG.handCount[player1] - 1], silver);
    assert(testG.hand[player1][testG.handCount[player1] - 1] == silver);

    printf("Try to buy a silver with 2 coins, and 1 buy.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.coins = 2;
    testG.numBuys = 1;
    result = buyCard(silver, &testG);
    printf("buyCard() was successful = %d, expected = %d\n", result, -1);
    assert(result == -1);
    printf("coins remaining = %d, expected = %d\n", testG.coins, 2);
    assert(testG.coins == 2);
    printf("buys remaining = %d, expected = %d\n", testG.numBuys, 1);
    assert(testG.numBuys == 1);

    printf("Try to buy a silver with 3 coins, and 0 buys.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.coins = 3;
    testG.numBuys = 0;
    result = buyCard(silver, &testG);
    printf("buyCard() was successful = %d, expected = %d\n", result, -1);
    assert(result == -1);
    printf("coins remaining = %d, expected = %d\n", testG.coins, 3);
    assert(testG.coins == 3);
    printf("buys remaining = %d, expected = %d\n", testG.numBuys, 0);
    assert(testG.numBuys == 0);

    printf("Try to buy a silver with 3 coins, and 1 buy and no silvers left.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.coins = 3;
    testG.numBuys = 1;
    testG.supplyCount[silver] = 0;
    result = buyCard(silver, &testG);
    printf("buyCard() was successful = %d, expected = %d\n", result, -1);
    assert(result == -1);
    printf("coins remaining = %d, expected = %d\n", testG.coins, 3);
    assert(testG.coins == 3);
    printf("buys remaining = %d, expected = %d\n", testG.numBuys, 1);
    assert(testG.numBuys == 1);

    printf("\nAll tests passed!\n\n\n");

    return 0;
}
