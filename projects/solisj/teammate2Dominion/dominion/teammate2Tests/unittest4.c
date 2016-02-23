#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int testUpdateCoins(int p, struct gameState *G1, int coins) {
    struct gameState G2;
    int i;
 
    memcpy(&G2, G1, sizeof(struct gameState));
    
    for (i = 0; i < G2.handCount[p]; i++) {
        switch (G2.hand[p][i])
        {
            case copper:
                G2.coins += 1;
                break;
            case silver:
                G2.coins += 2;
            case gold:
                G2.coins += 3;
        }
    }
    
    assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);
    return 0;
}

int main () {
    struct gameState G1;
    int n, i, p;
    int coins;
   
    printf("Testing Function: GetCost\n");
    
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G1)[i] = floor(Random() * 256);
        }
        coins = 0;
        p = floor(Random() * MAX_PLAYERS);
        G1.deckCount[p] = floor(Random() * MAX_DECK);
        G1.discardCount[p] = floor(Random() * MAX_DECK);
        G1.handCount[p] = floor(Random() * MAX_HAND);
        
        testUpdateCoins(p, &G1, coins);
    }
    
    printf("Testing Success!\n");
    
    return 0;
}
