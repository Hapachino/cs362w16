/*
 * cardtest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int testVillage(int p, int card, struct gameState *G1){
    struct gameState G2;
    int handPos = floor(Random() * G1->handCount[p]);
    
    memcpy (&G2, G1, sizeof(struct gameState));
    
    cardEffect(card, 0, 0, 0, G1, handPos, 0);
    
    PutSeed(3);

    drawCard(p, &G2); // draws a single card
    G2.numActions += 2; // gains two actions
    discardCard(handPos, p, &G2, 0); // discard the card
    
    assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);
    
    return 0;
}

int main () {
    struct gameState G1;
    int p;
    
    printf ("Testing Card: Village.\n");
    
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
        
        testVillage(p, village, &G1);
    }
    
    printf("Testing Success!\n");
    
    return 0;
}
