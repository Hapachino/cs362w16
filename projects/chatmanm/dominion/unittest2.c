/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
int testWhoseTurn(struct gameState *G1) {
    int playerTurn = G1->whoseTurn;
    int turnTest = whoseTurn(G1);
    
    assert(playerTurn == turnTest);
    
    return 0;
}

int main() {
    struct gameState G1;
    int n, i;
    
    printf ("Testing Whose Turn.\n");
    
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G1)[i] = floor(Random() * 256);
        }
        G1.whoseTurn = floor(Random() * MAX_PLAYERS);
        testWhoseTurn(&G1);
    }
    
    printf("Testing Success!\n");
    
    return 0;
}
