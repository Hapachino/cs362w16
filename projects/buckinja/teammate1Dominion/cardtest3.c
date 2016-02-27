#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void setupTest2(struct gameState *G, int handCount, int cardsInPlay[10]);
void testCutpurse(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest2(&G, 5, cardsInPlay); //game state and handcount
    testCutpurse(&G, cardsInPlay);
    
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

void setupTest2(struct gameState *G, int handCount, int cardsInPlay[10]) {
	int seed = 100;
	int r, i;
	int numPlayer = 4;
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
    for (i = 0; i < 4; i++) {
        G->handCount[i] = handCount;                 // set the number of cards on hand for each player
        memcpy(G->hand[i], coppers, sizeof(int) * handCount); // set all the cards to copper for each player
    }
}

void testCutpurse(struct gameState *G, int cardsInPlay[10]) {
    int result;
    int player = 0;
    int i;
    int handPos = 0;
    int numberInDeck[4];
    int numberInHand[4];
    int numberInDiscards[4];
    int numCoppers[4];
    int kc[10];
    int sc[4];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    //record how many cards are in each player's hand and set hand cards
    for (i = 0; i < 4; i++) {
        numberInHand[i] = G->handCount[i];
        numberInDeck[i] = G->deckCount[i];
        numberInDiscards[i] = G->discardCount[i];

        G->hand[i][0] = copper;
        G->hand[i][1] = silver;
        G->hand[i][2] = copper;
        G->hand[i][3] = adventurer;
        G->hand[i][4] = copper;
       
        numCoppers[i] = 3;
    }
    
    
    result = playCutpurse(player, G, handPos);
    
    assert(result == 0);
    printf("testCutpurse(): PASS didn't produce an error.\n");
    assert(numberInDeck[1] == G->deckCount[1]);
    assert(numberInDeck[2] == G->deckCount[2]);
    assert(numberInDeck[3] == G->deckCount[3]);
    printf("testCutpurse(): PASS all other players' deck counts unchanged.\n");
    if ((numberInHand[1] == G->handCount[1] +1) && (numberInHand[2] == G->handCount[2] +1) && (numberInHand[3] == G->handCount[3] +1)) {
        printf("testCutpurse(): PASS all other players' hand counts decremented correctly.\n");
    } else {
        if (numberInHand[1] != G->handCount[1] +1) 
            printf("testCutpurse(): FAIL player 1's hand count is %d instead of %d.\n", G->handCount[1], numberInHand[1] -1);
        if (numberInHand[2] != G->handCount[2] +1) 
            printf("testCutpurse(): FAIL player 2's hand count is %d instead of %d.\n", G->handCount[2], numberInHand[2] -1);
        if (numberInHand[3] != G->handCount[3] +1) 
            printf("testCutpurse(): FAIL player 3's hand count is %d instead of %d.\n", G->handCount[3], numberInHand[3] -1);
    }
    if ((numberInDiscards[1] == G->discardCount[1] -1) && (numberInDiscards[2] == G->discardCount[2] -1) && (numberInDiscards[3] == G->discardCount[3] -1)) {
        printf("testCutpurse(): PASS all other players' discard counts incremented correctly.\n");
    } else {
        if (numberInDiscards[1] != G->discardCount[1] -1) 
            printf("testCutpurse(): FAIL player 1's discard count did not increment.\n");
        if (numberInDiscards[2] != G->discardCount[2] -1)
            printf("testCutpurse(): FAIL player 2's discard count did not increment.\n");
        if (numberInDiscards[3] != G->discardCount[3] -1)
            printf("testCutpurse(): FAIL player 3's discard count did not increment.\n");
    }
    
    assert(numberInDeck[0] == G->deckCount[0]);
    printf("testCutpurse(): PASS current player's deck count unchanged.\n");
    if (numberInHand[0] == G->handCount[0])
        printf("testCutpurse(): PASS current player's hand count unchanged.\n");
    else
        printf("testCutpurse(): FAIL current player's hand count changed from %d to %d.\n", numberInHand[0], G->handCount[0]);
    assert(numberInDiscards[0] == G->discardCount[0]);
    printf("testCutpurse(): PASS current player's discard count unchanged.\n");
    
    int j;
    for (i = 1; i < 4; i++) {
        numCoppers[i] = 0;
        for (j = 0; j < G->handCount[i]; j++) {
            if (G->hand[i][j] == copper)
                numCoppers[i]++;
        }
    }
    for (i = 1; i < 4; i++) {
        if (numCoppers[i] == 2)
            printf("testCutpurse(): PASS player %d has had one copper removed from their hand.\n", i);
        else
            printf("testCutpurse(): FAIL player %d has %d coppers in their hand instead of expected 2.\n", i, numCoppers[i]);
    }
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testCutpurse(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testCutpurse(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testCutpurse(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testCutpurse(): PASS victory card supply has not been altered.\n");
    
    //testing with 2 players and no coppers in hand
    setupTest(G, 5, cardsInPlay); //creating 2 player game
    
    for (i = 0; i < 2; i++) {
        numberInHand[i] = G->handCount[i];
        numberInDeck[i] = G->deckCount[i];
        numberInDiscards[i] = G->discardCount[i];

        G->hand[i][0] = smithy;
        G->hand[i][1] = silver;
        G->hand[i][2] = smithy;
        G->hand[i][3] = adventurer;
        G->hand[i][4] = gold;
       
        numCoppers[i] = 0;
    }

    result = playCutpurse(player, G, handPos);
    
    assert(result == 0);
    printf("testCutpurse(): PASS didn't produce an error.\n");
    assert(numberInDeck[1] == G->deckCount[1]);
    printf("testCutpurse(): PASS other player's deck count unchanged.\n");
    assert(numberInHand[1] == G->handCount[1]);
    printf("testCutpurse(): PASS other player's hand count unchanged.\n");
    assert(numberInDiscards[1] == G->discardCount[1]);
    printf("testCutpurse(): PASS other player's discard count unchanged.\n");
    assert(numberInDeck[0] == G->deckCount[0]);
    printf("testCutpurse(): PASS current player's deck count unchanged.\n");
    if (numberInHand[0] == G->handCount[0])
        printf("testCutpurse(): PASS current player's hand count unchanged.\n");
    else
        printf("testCutpurse(): FAIL current player's hand count changed from %d to %d.\n", numberInHand[0], G->handCount[0]);
    assert(numberInDiscards[0] == G->discardCount[0]);
    printf("testCutpurse(): PASS current player's discard count unchanged.\n");

    //testing with 2 players and coppers in hand
    setupTest(G, 5, cardsInPlay); //creating 2 player game
    
    for (i = 0; i < 2; i++) {
        numberInHand[i] = G->handCount[i];
        numberInDeck[i] = G->deckCount[i];
        numberInDiscards[i] = G->discardCount[i];

        G->hand[i][0] = copper;
        G->hand[i][1] = smithy;
        G->hand[i][2] = smithy;
        G->hand[i][3] = adventurer;
        G->hand[i][4] = copper;
       
        numCoppers[i] = 2;
    }

    result = playCutpurse(player, G, handPos);
    
    assert(result == 0);
    printf("testCutpurse(): PASS didn't produce an error.\n");
    assert(numberInDeck[1] == G->deckCount[1]);
    printf("testCutpurse(): PASS other player's deck count unchanged.\n");
    if (numberInHand[1] == G->handCount[1] +1)
        printf("testCutpurse(): PASS other player's hand count decremented correctly.\n");
    else
        printf("testCutpurse(): FAIL other player's hand count did not decrement.\n");
    if (numberInDiscards[1] == G->discardCount[1] -1)
        printf("testCutpurse(): PASS other player's discard count incremented correctly.\n");
    else
        printf("testCutpurse(): FAIL other player's discard count did not increment.\n");
    assert(numberInDeck[0] == G->deckCount[0]);
    printf("testCutpurse(): PASS current player's deck count unchanged.\n");
    if (numberInHand[0] == G->handCount[0])
        printf("testCutpurse(): PASS current player's hand count unchanged.\n");
    else
        printf("testCutpurse(): FAIL current player's hand count changed from %d to %d.\n",numberInHand[0], G->handCount[0]);
    assert(numberInDiscards[0] == G->discardCount[0]);
    printf("testCutpurse(): PASS current player's discard count unchanged.\n");
    
    altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testCutpurse(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testCutpurse(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testCutpurse(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testCutpurse(): PASS victory card supply has not been altered.\n");
}


