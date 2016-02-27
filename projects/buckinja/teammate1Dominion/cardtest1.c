#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testSmithy(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
    testSmithy(&G, cardsInPlay);
    
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

void testSmithy(struct gameState *G, int cardsInPlay[10]) {
    int result;
    int handPos = 2;
    int player = 0;
    int numberInDiscards = G->discardCount[player];
    int numberInHand = G->handCount[player];
    int numberInDeck = G->deckCount[player];
    int playedCards = G->playedCardCount;
    int numInDeck2 = G->deckCount[1];
    int numInHand2 = G->handCount[1];
    int numInDiscard2 = G->discardCount[1];
    int kc[10];
    int i;
    int sc[4];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    if (numberInHand >= 5) {
        G->hand[player][0] = copper;
        G->hand[player][1] = silver;
        G->hand[player][2] = smithy;
        G->hand[player][3] = adventurer;
        G->hand[player][4] = gold;
    }
    
    //test with smithy in mid hand
    result = smithyCard(G, player, handPos);
    
    assert(result == 0);
    printf("testSmithy(): PASS didn't produce an error.\n");
    assert(numInDeck2 == G->deckCount[1]);
    printf("testSmithy(): PASS other player's deck count unchanged.\n");
    assert(numInHand2 == G->handCount[1]);
    printf("testSmithy(): PASS other player's hand count unchanged.\n");
    assert(numInDiscard2 == G->discardCount[1]);
    printf("testSmithy(): PASS other player's discard count unchanged.\n");
    if (numberInHand != G->handCount[player] -2) {
        printf("testSmithy(): FAIL number in hand is %d instead of %d.\n", G->handCount[player], numberInHand +2  );
    } else {
        printf("testSmithy(): PASS number in hand is +3 cards and -1 discard.\n");
    }
    //assert(numberInDiscards == G->discardCount[player] +1);
    if (numberInDiscards != G->discardCount[player] +1) {
        printf("testSmithy(): FAIL number in discards is %d, was previously %d. Should have incremented.\n", G->discardCount[player], numberInDiscards);
    } else {
        printf("testSmithy(): PASS discard is incremented correctly.\n");
    }
    if (numberInDeck != G->deckCount[player] +2) { 
        printf("testSmithy(): FAIL number in deckCount is %d, was previously %d. Should have decremented by 2.\n", G->deckCount[player], numberInDeck);
    } else {
        printf("testSmithy(): PASS deckCount decremented correctly.\n");
    }
    if (G->playedCardCount -1 != playedCards) {
        printf("testSmithy(): FAIL playedCardCount is %d, was previously %d. Should have incremented by 1.\n", G->playedCardCount, playedCards);
    } else {
        printf("testSmithy(): PASS smithy added to playedCards.\n");
    }
    
    //test with smithy as only card in hand
    while (G->handCount[player] > 1) {
        discardCard(0, player, G, 0);
    }
    
    G->hand[player][0] = smithy;
    numberInDiscards = G->discardCount[player];
    numberInHand = G->handCount[player];
    numberInDeck = G->deckCount[player];
    playedCards = G->playedCardCount;
    
    result = smithyCard(G, player, 0);
    
    assert(result == 0);
    printf("testSmithy(): PASS didn't produce an error.\n");
    if (numberInHand != G->handCount[player] -2) {
        printf("testSmithy(): FAIL number in hand is %d instead of %d.\n", G->handCount[player], numberInHand +2  );
    } else {
        printf("testSmithy(): PASS number in hand is +3 cards and -1 discard.\n");
    }
    if (numberInDiscards != G->discardCount[player] +1) {
        printf("testSmithy(): FAIL number in discards is %d, was previously %d. Should have incremented.\n", G->discardCount[player], numberInDiscards);
    } else {
        printf("testSmithy(): PASS discard is incremented correctly.\n");
    }
    if (numberInDeck != G->deckCount[player] +1) {
        printf("testSmithy(): FAIL number in deckCount is %d, was previously %d. Should have decremented by 2.\n", G->deckCount[player], numberInDeck);
    } else {
        printf("testSmithy(): PASS deckCount decremented correctly.\n");
    }
    if (G->playedCardCount -1 != playedCards) {
        printf("testSmithy(): FAIL playedCardCount is %d, was previously %d. Should have incremented by 1.\n", G->playedCardCount, playedCards);
    } else {
        printf("testSmithy(): PASS smithy added to playedCards.\n");
    }
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testSmithy(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testSmithy(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testSmithy(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testSmithy(): PASS victory card supply has not been altered.\n");
}
