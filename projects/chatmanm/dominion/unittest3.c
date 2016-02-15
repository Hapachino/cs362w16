/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


int testGetCost(randCard) {
    int cardCostValues[] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    int cardCost = 0;
    
    cardCost = getCost(randCard);

    assert(cardCost == cardCostValues[randCard]);
    return 0;
}

int main() {
    int randCard;
    int n, i;
    struct gameState G;
    srand(time(NULL));
    
    printf("Testing Function: GetCost\n");
    for (n = 0; n < 2000; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        randCard = rand() % (treasure_map + 1); // generates random number 1 - 27
        testGetCost(randCard);
    }
    
    printf("Testing Success!\n");
    
    return 0;
}
