#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TEST "shuffle"

int main() {
    int i, j;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState GTest;
    int maxHandCount = 5;
    
    printf ("Testing %s()\n", TEST);
    
    initializeGame(numPlayer, k, seed, &G);
    
    memcpy(&GTest, &G, sizeof(struct gameState));
    
    shuffle(0, &G);
    
    for (j = 0; j < numPlayer; j++) {
        printf("Player %d", j + 1);
        printf("Before the shuffle\n");
        for (i = 0; i < GTest.deckCount[0]; i++) {
            printf("%d\n", GTest.deck[0][i]);
        }
    
        printf("After the shuffle\n");
        for (i = 0; i < G.deckCount[0]; i++) {
            printf("%d\n", G.deck[0][i]);
        }
    }
    
    
    return 0;
}