#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testBuyCard(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
	testBuyCard(&G, cardsInPlay);
    
    return 0;
    
}


void testBuyCard(struct gameState *G, int cardsInPlay[10]) {
    //set turn to player 0
    int player = 0;
    int result;
    int numberInSupplyPile = supplyCount(gold, G);
    int numberInDiscards = G->discardCount[player];
    int kc[10];
    int i;
    
    for (i = 0; i < 10; i++) {
        kc[i] = cardsInPlay[i];
    }
    G->whoseTurn = player;
    
    //test numBuys with 1
    G->numBuys = 1;
    G->coins = getCost(gold);
    
    result = buyCard(gold, G);
    assert(result == 0);
    printf("testBuyCard(): PASS buyCard didn't produce an error.\n");
    assert(G->coins == 0);
    printf("testBuyCard(): PASS buyCard decremented correct coins.\n");
    assert(G->numBuys == 0);
    printf("testBuyCard(): PASS buyCard decremented numBuys.\n");
    assert(numberInSupplyPile == supplyCount(gold, G) +1);
    printf("testBuyCard(): PASS buyCard removed correct card from supply.\n");
    assert(numberInDiscards == G->discardCount[player] -1);
    printf("testBuyCard(): PASS buyCard added card to discard pile.\n");
    
    //test numBuys with 0
    G->numBuys = 0;
    G->coins = getCost(gold);
    numberInSupplyPile = supplyCount(gold, G);
    numberInDiscards = G->discardCount[player];
    
    result = buyCard(gold, G);
    assert(result == -1);
    printf("testBuyCard(): PASS buyCard correctly produced an error.\n");
    assert(G->coins == getCost(gold));
    printf("testBuyCard(): PASS coins unchanged.\n");
    assert(numberInSupplyPile == supplyCount(gold, G));
    printf("testBuyCard(): PASS supply unchanged.\n");
    assert(numberInDiscards == G->discardCount[player]);
    printf("testBuyCard(): PASS discard pile unchanged.\n");
    
    //test if supplyCount is out
    G->numBuys = 1;
    G->coins = getCost(gold);
    G->supplyCount[gold] = 0;
    numberInSupplyPile = supplyCount(gold, G);
    numberInDiscards = G->discardCount[player];
    
    result = buyCard(gold, G);
    assert(result == -1);
    printf("testBuyCard(): PASS buyCard correctly produced an error.\n");
    assert(G->coins == getCost(gold));
    printf("testBuyCard(): PASS coins unchanged.\n");
    assert(supplyCount(gold, G) == 0);
    printf("testBuyCard(): PASS supply unchanged.\n");
    assert(numberInDiscards == G->discardCount[player]);
    printf("testBuyCard(): PASS discard pile unchanged.\n");
    assert(G->numBuys == 1);
    printf("testBuyCard(): PASS numBuys unchanged.\n");

    //test if coins available
    G->numBuys = 1;
    G->coins = getCost(silver);
    G->supplyCount[gold] = 10;
    numberInSupplyPile = supplyCount(gold, G);
    numberInDiscards = G->discardCount[player];
    
    result = buyCard(gold, G);
    assert(result == -1);
    printf("testBuyCard(): PASS buyCard correctly produced an error.\n");
    assert(G->coins == getCost(silver));
    printf("testBuyCard(): PASS coins unchanged.\n");
    assert(supplyCount(gold, G) == 10);
    printf("testBuyCard(): PASS supply unchanged.\n");
    assert(numberInDiscards == G->discardCount[player]);
    printf("testBuyCard(): PASS discard pile unchanged.\n");
    assert(G->numBuys == 1);
    printf("testBuyCard(): PASS numBuys unchanged.\n");
    
    G->numBuys = 2;
    G->coins = 15;
    numberInSupplyPile = supplyCount(gold, G);
    numberInDiscards = G->discardCount[player];
    
    result = buyCard(gold, G);
    assert(result == 0);
    printf("testBuyCard(): PASS buyCard didn't produce an error.\n");
    assert(G->coins == 15 - getCost(gold));
    printf("testBuyCard(): PASS coins decremented correctly.\n");
    assert(supplyCount(gold, G) == numberInSupplyPile - 1);
    printf("testBuyCard(): PASS supply decremented correctly.\n");
    assert(numberInDiscards + 1 == G->discardCount[player]);
    printf("testBuyCard(): PASS discards incremented correctly.\n");
    assert(G->numBuys == 1);
    printf("testBuyCard(): PASS numBuys decremented correctly.\n");
    
    result = buyCard(gold, G);
    assert(result == 0);
    printf("testBuyCard(): PASS buyCard didn't produce an error.\n");
    assert(G->coins == 15 - 2*(getCost(gold)));
    printf("testBuyCard(): PASS coins decremented correctly.\n");
    assert(supplyCount(gold, G) == numberInSupplyPile - 2);
    printf("testBuyCard(): PASS supply decremented correctly.\n");
    assert(numberInDiscards + 2 == G->discardCount[player]);
    printf("testBuyCard(): PASS discards incremented correctly.\n");
    assert(G->numBuys == 0);
    printf("testBuyCard(): PASS numBuys decremented correctly.\n");
    
    result = buyCard(gold, G);
    assert(result == -1);
    printf("testBuyCard(): PASS buyCard didn't produce an error.\n");
    assert(G->coins == 15 - 2*(getCost(gold)));
    printf("testBuyCard(): PASS coins unchanged.\n");
    assert(supplyCount(gold, G) == numberInSupplyPile - 2);
    printf("testBuyCard(): PASS supply unchanged.\n");
    assert(numberInDiscards + 2 == G->discardCount[player]);
    printf("testBuyCard(): PASS discards unchanged.\n");
    assert(G->numBuys == 0);
    printf("testBuyCard(): PASS numBuys unchanged.\n");
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != cardsInPlay[i]){
            printf("testBuyCard(): FAIL kingdomCards[] has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testBuyCard(): PASS kingdomCards[] has not been altered.\n");

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