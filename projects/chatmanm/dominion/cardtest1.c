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


int testSmithyCard(int p, int card, int handPos, struct gameState *G1)
{
    struct gameState G2;
    int actionCard = 3; // current player draws three cards
    
    memcpy(&G2, G1, sizeof(struct gameState)); // copy of initialized game for testing
    
    printf("Player's Beginning Hand Count = %d\n", G2.handCount[p]); // player's initial hand count, default = 5
    
    p = floor(Random() * MAX_PLAYERS);
    cardEffect(smithy, 0, 0, 0, &G2, handPos, 0); // player receives 3 more cards
    G1->handCount[p] = (G1->handCount[p] + actionCard) - 1; // update expected hand count when smithy card is played
    
    printf("Final Hand Count = %d, Expected Hand Count = %d\n", G2.handCount[p], G1->handCount[p]);
    
    assert(G2.handCount[p] == G1->handCount[p]);

    return 0;
}

int main() {
    struct gameState G1;
    int numPlayers = 2;
    int handPos = 0;
    int p = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    
    printf("Testing Card: Smithy\n");
    
    initializeGame(numPlayers, k, 1000, &G1); // initializes a new game

    testSmithyCard(p, smithy, handPos, &G1);
    printf("Testing Success!\n");

    return 0;
}
