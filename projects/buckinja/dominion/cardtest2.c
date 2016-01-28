#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testAdventurer(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
    testAdventurer(&G, cardsInPlay);
    
    return 0;
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

void testAdventurer(struct gameState *G, int cardsInPlay[10]) {
    
    int result;
    int player = 0;
    int i;
    int cards = 3; // number of cards that will be in discard
    int numberInDeck = G->deckCount[player];
    int numTreasure = 0;
    int numTreasureAfter = 0;
    int numberInHand = G->handCount[player];
    int kc[10];
    //ensuring other player's state doesn't change
    int numInDeck2 = G->deckCount[1];
    int numInHand2 = G->handCount[1];
    int numInDiscard2 = G->discardCount[1];
    int sc[4];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    G->deck[player][G->deckCount[player] - 1] = copper;
    G->deck[player][G->deckCount[player] - 2] = smithy;
    G->deck[player][G->deckCount[player] - 3] = smithy;
    G->deck[player][G->deckCount[player] - 4] = smithy;
    G->deck[player][G->deckCount[player] - 5] = copper;
    
    
    //count number of coppers in deck before playing adventurer
    for (i = 0; i < G->deckCount[player]; i++) {
        if (G->deck[player][i] == copper) {
            numTreasure++;
        }
    }

    //turn all cards in hand into smithy cards
    for (i = 0; i < G->handCount[player]; i++) {
        G->hand[player][i] = smithy;
    }
    
    result = playAdventurer(player, G);
    
    for (i = 0; i < G->deckCount[player]; i++) {
        if (G->deck[player][i] == copper) {
            numTreasureAfter++;
        }
    }
    
    assert(result == 0);
    printf("testAdventurer(): PASS didn't produce an error.\n");
    assert(numInDeck2 == G->deckCount[1]);
    printf("testAdventurer(): PASS other player's deck count unchanged.\n");
    assert(numInHand2 == G->handCount[1]);
    printf("testAdventurer(): PASS other player's hand count unchanged.\n");
    assert(numInDiscard2 == G->discardCount[1]);
    printf("testAdventurer(): PASS other player's discard count unchanged.\n");
    
    if(cards != G->discardCount[player]){
        printf("testAdventurer(): FAIL expected number of cards were not discarded to correct player's discard.  Expected %d, actual value: %d\n", cards, G->discardCount[player]);
    } else {
        printf("testAdventurer(): PASS correct number of cards were discarded to correct player's discard.\n");
    }
    assert(numTreasure == numTreasureAfter +2);
    printf("testAdventurer(): PASS correct number of treasure cards were taken from deck.\n");
    assert(numberInDeck == G->deckCount[player] + 5);
    printf("testAdventurer(): PASS correct number of total cards were taken from correct player's deck.\n");
    
    numTreasureAfter = 0;
    for (i = 0; i < G->handCount[player]; i++) {
        if (G->hand[player][i] == copper) {
            numTreasureAfter++;
        }
    }
    
    assert(numTreasureAfter == 2);
    printf("testAdventurer(): PASS correct number of coppers found in hand.\n");
    assert(numberInHand == G->handCount[player] - 2);
    printf("testAdventurer(): PASS hand size incremented correctly.\n");
    
    //testing with other treasures (gold/silver) and no discards
    player = 1;
    cards = 0; // number of cards that will be in discard
    numberInDeck = G->deckCount[player];
    numTreasure = 0;
    numTreasureAfter = 0;
    numberInHand = G->handCount[player];
    
    //turn all cards in hand into smithy cards
    for (i = 0; i < G->handCount[player]; i++) {
        G->hand[player][i] = smithy;
    }
    
    G->deck[player][G->deckCount[player] - 1] = silver;
    G->deck[player][G->deckCount[player] - 2] = gold;
    G->deck[player][G->deckCount[player] - 3] = smithy;
    G->deck[player][G->deckCount[player] - 4] = smithy;
    G->deck[player][G->deckCount[player] - 5] = copper;
    
    //count number of treasure in deck before playing adventurer
    for (i = 0; i < G->deckCount[player]; i++) {
        if (G->deck[player][i] == copper || G->deck[player][i] == silver || G->deck[player][i] == gold) {
            numTreasure++;
        }
    }
    
    result = playAdventurer(player, G);
    
    //count number of treasure in deck after playing adventurer
    for (i = 0; i < G->deckCount[player]; i++) {
        if (G->deck[player][i] == copper || G->deck[player][i] == silver || G->deck[player][i] == gold) {
            numTreasureAfter++;
        }
    }
    
    assert(result == 0);
    printf("testAdventurer(): PASS didn't produce error.\n");
    assert(cards == G->discardCount[player]);
    printf("testAdventurer(): PASS correct number of cards were discarded to correct player's discard pile.\n");
    assert(numTreasure == numTreasureAfter +2);
    printf("testAdventurer(): PASS correct number of treasure cards removed from deck.\n");
    assert(numberInDeck == G->deckCount[player] + 2);
    printf("testAdventurer(): PASS correct number of total cards removed from correct player's deck.\n");
    
    numTreasureAfter = 0;
    for (i = 0; i < G->handCount[player]; i++) {
        if (G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i] == gold) {
            numTreasureAfter++;
        }
    }
    
    if (numTreasureAfter == 2){
        printf("testAdventurer(): PASS correct number of treasure cards in hand.\n");
    } else {
        printf("testAdventurer(): FAIL correct number of treasure cards in hand should be 2, but is %d.\n", numTreasureAfter);
    }
    assert(numberInHand == G->handCount[player] - 2);
    printf("testAdventurer(): PASS correct number of total cards in hand.\n");
    
    
    //test need for shuffling and empty hand
    setupTest(G, 0, cardsInPlay);
    player = 0;
    cards = 0; // number of cards that will be in discard
    
    //turn all cards in hand into smithy cards
    for (i = 0; i < G->handCount[player]; i++) {
        G->hand[player][i] = smithy;
    }
    
    //put all but one card from deck into discards, forcing a need for shuffling
    int deckc = G->deckCount[player] -1;
    for (i = deckc; i > 0; i--) {
        G->discard[player][G->discardCount[player]] = G->deck[player][i];
        G->discardCount[player]++;
        G->deckCount[player]--;
    }
    
    G->deck[player][0] = smithy;
    numberInDeck = G->deckCount[player];
    if(numberInDeck == 1) {
        printf("testAdventurer(): PASS all but one card in deck moved to discards (precondition for this round of tests).\n");
    } else {
         printf("testAdventurer(): FAIL number in deck should be 1 but is %d.\n", numberInDeck);
    }
    int numberInDiscards = G->discardCount[player];
    numTreasureAfter = 0;
    numberInHand = G->handCount[player];
    assert(numberInHand == 0);
    printf("testAdventurer(): PASS hand starts empty.\n");
    
    result = playAdventurer(player, G);
    
    assert(result == 0);
    printf("testAdventurer(): PASS didn't produce error.\n");
    if (numberInDiscards > G->discardCount[player]){
        printf("testAdventurer(): PASS discards amount less than previous discard amount, so shuffling occurred.\n");
    } else {
        printf("testAdventurer(): FAIL deck did not shuffle.");
    }
    assert(numberInHand == G->handCount[player] -2);
    printf("testAdventurer(): PASS correct number of cards in hand.\n");
    
    for (i = 0; i < G->handCount[player]; i++) {
        if (G->hand[player][i] == copper) {
            numTreasureAfter++;
        }
    }
    
    assert(numTreasureAfter == 2);
    printf("testAdventurer(): PASS correct number of treasure cards in hand.\n");

    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testAdventurer(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testAdventurer(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testAdventurer(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testAdventurer(): PASS victory card supply has not been altered.\n");
}