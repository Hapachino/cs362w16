/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"

int testGreatHall(int p, struct gameState *G1) {
    struct gameState G2;
    int handPos = floor(Random() * G1->handCount[p]);
    
    memcpy(&G2, G1, sizeof(struct gameState));
    
    PutSeed(3);
    
    cardEffect(great_hall, 0, 0, 0, G1, handPos, 0);
    
    drawCard(p, &G2); // draws a single card
    G2.numActions++; // gains one action
    discardCard(handPos, p, &G2, 0); // discard the card
    
    assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);
    
    return 0;
}

int main() {
    struct gameState G1;
    int p;
    printf ("Testing Card: Great Hall\n");
    
    for (int n = 0; n < 2000; n++) {
        for (int i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G1)[i] = floor(Random() * 256);
        }
        
        p = floor(Random() * MAX_PLAYERS);
        G1.deckCount[p] = floor(Random() * MAX_DECK);
        G1.discardCount[p] = floor(Random() * MAX_DECK);
        G1.handCount[p] = floor(Random() * MAX_HAND);
        G1.playedCardCount = floor(Random() * MAX_DECK);
        G1.whoseTurn = p;
        
        testGreatHall(p, &G1);
    }
    
    printf("Testing Success!\n");
    
    return 0;
}


