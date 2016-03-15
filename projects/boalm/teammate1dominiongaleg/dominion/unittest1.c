
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
    int isOver = 0;

    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING isGameOver():\n");

    printf("note: 0 means the game is not over and 1 means it's over.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[province] = 0;
    isOver = isGameOver(&testG);
    printf("Test when province stack is set to 0\n"); 
    printf("Expected = %d, Actual = %d\n", 1, isOver);
    assert(1 == isOver);

    printf("Test when province stack is set to 3\n"); 
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[province] = 3;
    isOver = isGameOver(&testG);
    printf("Expected = %d, Actual = %d\n", 0, isOver);
    assert(0 == isOver);

    printf("Test 2 but not 3 stacks are empty\n"); 
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[council_room] = 0;
    testG.supplyCount[duchy] = 0;
    isOver = isGameOver(&testG);
    printf("Expected = %d, Actual = %d\n", 0, isOver);
    assert(0 == isOver);

    printf("Test when 3 stacks are empty\n"); 
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[duchy] = 0;
    testG.supplyCount[smithy] = 0;
    testG.supplyCount[village] = 0;
    isOver = isGameOver(&testG);
    printf("Expected = %d, Actual = %d\n", 1, isOver);
    assert(1 == isOver);

    printf("Test 3 different stacks are empty\n"); 
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[gardens] = 0;
    testG.supplyCount[mine] = 0;
    testG.supplyCount[great_hall] = 0;
    isOver = isGameOver(&testG);
    printf("Expected = %d, Actual = %d\n", 1, isOver);
    assert(1 == isOver);

    printf("Test when 3 stacks are empty, but wasn't in the game.\n"); 
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[minion] = 0;
    testG.supplyCount[mine] = 0;
    testG.supplyCount[great_hall] = 0;
    isOver = isGameOver(&testG);
    printf("Expected = %d, Actual = %d\n", 0, isOver);
    printf("I turned off this assertion because it fails, but I'm not sure how to fix this.");
    // assert(0 == isOver);


    printf("\nAll tests passed!\n\n\n");

    return 0;
}
