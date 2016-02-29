#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testIsGameOver(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
	testIsGameOver(&G, cardsInPlay);
    
    return 0;
    
}


void testIsGameOver(struct gameState *G, int cardsInPlay[10]) {
    //NOTE: in this case, checking the return value of 0 or 1 is appropriate since 0 is game not over and 1 is game over.
    //no other values are changed in this function.
    
    int i = 0;
    int kc[10];
    
    for (i = 0; i < 10; i++) {
        kc[i] = cardsInPlay[i];
    }
    
    //test at game set up
    assert(isGameOver(G) == 0);
    printf("testIsGameOver(): PASS game not over after game setup.\n");

    //test with all values above 0
    for (i = 0; i < 25; i++) {
        G->supplyCount[i] = 1;
    }
    assert(isGameOver(G) == 0);
    printf("testIsGameOver(): PASS game not over after all supplyCount values set to 1.\n");
    
    //test with non-province values - one is 0, two are 0, three are 0, 5 are 0
    G->supplyCount[5] = 0;
    assert(isGameOver(G) == 0);
    printf("testIsGameOver(): PASS game not over after one supplyCount value set to 0, rest to 1.\n");
    G->supplyCount[14] = 0;
    assert(isGameOver(G) == 0);
    printf("testIsGameOver(): PASS game not over after two supplyCount values set to 0, rest to 1.\n");
    G->supplyCount[0] = 0;
    assert(isGameOver(G) == 1);
    printf("testIsGameOver(): PASS game is over after three supplyCount values set to 0, rest to 1.\n");
    G->supplyCount[11] = 0;
    G->supplyCount[19] = 0;
    assert(isGameOver(G) == 1);
    printf("testIsGameOver(): PASS game is over after more than 3 supplyCount values set to 0, rest to 1.\n");
    
    //test with all values at MAX_DECK except for province ==0
    for (i = 0; i < 25; i++) {
        G->supplyCount[i] = MAX_DECK;
    }
    G->supplyCount[province] = 0;
    assert(isGameOver(G) == 1);
    printf("testIsGameOver(): PASS game is over after only province supplyCount value set to 0.\n");
    
    //test with all values ==0
    for (i = 0; i < 25; i++) {
        G->supplyCount[i] = 0;
    }
    assert(isGameOver(G) == 1);
    printf("testIsGameOver(): PASS game is over after all supplyCount values set to 0.\n");
    
    //test with 3 values < 0
    for (i = 0; i < 25; i++) {
        G->supplyCount[i] = 10;
    }
    G->supplyCount[8] = -1;
    G->supplyCount[9] = -1;
    G->supplyCount[10] = -1;
    assert(isGameOver(G) == 0);
    printf("testIsGameOver(): PASS game not over after three values set to -1.\n");
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != cardsInPlay[i]){
            printf("testIsGameOver(): FAIL kingdomCards[] has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testIsGameOver(): PASS kingdomCards[] has not been altered.\n");
}

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]) {
	int seed = 100;
	int p = 0;
	int r, i;
	int numPlayer = 2;
	int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
  
	memset(G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, cardsInPlay, seed, G); // initialize a new game
	G->handCount[p] = handCount;                 // set the number of cards on hand
    G->handCount[p+1] = handCount; 

	memcpy(G->hand[p], coppers, sizeof(int) * handCount); // set all the cards to copper
    memcpy(G->hand[p+1], coppers, sizeof(int) * handCount);
}