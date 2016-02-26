#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testRemodel(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
    testRemodel(&G, cardsInPlay);
    
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

void testRemodel(struct gameState *G, int cardsInPlay[10]) {
    int result;
    int choice1; //hand pos to trash
    int choice2; //gaining
    int i;
    int handPos = 0;
    int player = 0;
    int numberInDeck = G->deckCount[player];
    int numberInHand = G->handCount[player];
    int numberInDiscards = G->discardCount[player];
    
    G->hand[player][0] = remodel;
    G->hand[player][1] = silver;
    G->hand[player][2] = smithy;
    G->hand[player][3] = adventurer;
    G->hand[player][4] = smithy;
    
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

    
    //testing with 2 cards of equal value -- DOESN'T WORK.
    printf("testRemodel(): NOTE--Using cards of EQUAL VALUE, should be a legal move.\n");
    choice1 = 2;
    choice2 = baron;
    result = playRemodel(player, G, handPos, choice1, choice2);
    if (result == 0)
        printf("testRemodel(): PASS didn't produce an error.\n");
    else
        printf("testRemodel(): FAIL produced an error.\n");
    if (numInDeck2 == G->deckCount[1])
        printf("testRemodel(): PASS other player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's deck count changed.\n");
    if (numInHand2 == G->handCount[1])
        printf("testRemodel(): PASS other player's hand count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's hand count changed.\n");
    if (numInDiscard2 == G->discardCount[1])
        printf("testRemodel(): PASS other player's discard count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's discard count changed.\n");
    if (numberInDeck == G->deckCount[player])
        printf("testRemodel(): PASS current player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL current player's deck count changed.\n");
    if (numberInHand == G->handCount[player] +1)
        printf("testRemodel(): PASS current player's hand count decremented correctly.\n");
    else
        printf("testRemodel(): FAIL current player's hand count didn't decrement correctly. Was %d, is now %d.\n", numberInHand, G->handCount[player]);
    if (numberInDiscards == G->discardCount[1] -2)
        printf("testRemodel(): PASS current player's discard count increased by 2.\n");
    else 
        printf("testRemodel(): FAIL current player's discard count was %d, is now %d, but should have incremented by 2.\n", numberInDiscards, G->discardCount[1]);
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            if(cardsInPlay[i] == choice2 && (kc[i] -1 == supplyCount(cardsInPlay[i], G)))
                printf("testRemodel(): PASS enum CARD %d's supply has been decremented correctly.\n", cardsInPlay[i]);
            else
                printf("testRemodel(): FAIL kingdom cards supply has been altered incorrectly. Was %d, is now %d.\n", kc[i], supplyCount(cardsInPlay[i], G));
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): FAIL kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testRemodel(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS victory card supply has not been altered.\n");
    
    setupTest(G, 5, cardsInPlay);
    player = 0;
    numberInDeck = G->deckCount[player];
    numberInHand = G->handCount[player];
    numberInDiscards = G->discardCount[player];
    
    G->hand[player][0] = remodel;
    G->hand[player][1] = silver;
    G->hand[player][2] = smithy;
    G->hand[player][3] = adventurer;
    G->hand[player][4] = smithy;
    
    //ensuring other player's state doesn't change
    numInDeck2 = G->deckCount[1];
    numInHand2 = G->handCount[1];
    numInDiscard2 = G->discardCount[1];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    printf("testRemodel(): NOTE--Exchanging for max value choice2.\n");
    choice1 = 2;
    choice2 = adventurer;
    result = playRemodel(player, G, handPos, choice1, choice2);
    
    if (result == 0)
        printf("testRemodel(): PASS didn't produce an error.\n");
    else
        printf("testRemodel(): FAIL produced an error.\n");
    if (numInDeck2 == G->deckCount[1])
        printf("testRemodel(): PASS other player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's deck count changed.\n");
    if (numInHand2 == G->handCount[1])
        printf("testRemodel(): PASS other player's hand count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's hand count changed.\n");
    if (numInDiscard2 == G->discardCount[1])
        printf("testRemodel(): PASS other player's discard count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's discard count changed.\n");
    if (numberInDeck == G->deckCount[player])
        printf("testRemodel(): PASS current player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL current player's deck count changed.\n");
    if (numberInHand == G->handCount[player] +1)
        printf("testRemodel(): PASS current player's hand count decremented correctly.\n");
    else
        printf("testRemodel(): FAIL current player's hand count didn't decrement correctly. Was %d, is now %d.\n", numberInHand, G->handCount[player]);
    if (numberInDiscards == G->discardCount[1] -2)
        printf("testRemodel(): PASS current player's discard count increased by 2.\n");
    else 
        printf("testRemodel(): FAIL current player's discard count was %d, is now %d, but should have incremented by 2.\n", numberInDiscards, G->discardCount[1]);
    
    altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            if(cardsInPlay[i] == choice2 && (kc[i] -1 == supplyCount(cardsInPlay[i], G)))
                printf("testRemodel(): PASS enum CARD %d's supply has been decremented.\n", cardsInPlay[i]);
            else
                printf("testRemodel(): FAIL kingdom cards supply has been altered incorrectly.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testRemodel(): FAIL victory card supply has been altered incorrectly.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS victory card supply has not been altered.\n");
    
    
    setupTest(G, 5, cardsInPlay);
    player = 0;
    numberInDeck = G->deckCount[player];
    numberInHand = G->handCount[player];
    numberInDiscards = G->discardCount[player];
    
    G->hand[player][0] = remodel;
    G->hand[player][1] = silver;
    G->hand[player][2] = smithy;
    G->hand[player][3] = adventurer;
    G->hand[player][4] = smithy;
    
    //ensuring other player's state doesn't change
    numInDeck2 = G->deckCount[1];
    numInHand2 = G->handCount[1];
    numInDiscard2 = G->discardCount[1];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    printf("testRemodel(): NOTE--Exchanging for more than max value choice2 -- shouldn't be a legal move.\n");
    choice1 = 2;
    choice2 = province;
    result = playRemodel(player, G, handPos, choice1, choice2);
    
    if (result == 0)
        printf("testRemodel(): FAIL didn't produce an error.\n");
    else
        printf("testRemodel(): PASS produced an error.\n");
    if (numInDeck2 == G->deckCount[1])
        printf("testRemodel(): PASS other player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's deck count changed.\n");
    if (numInHand2 == G->handCount[1])
        printf("testRemodel(): PASS other player's hand count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's hand count changed.\n");
    if (numInDiscard2 == G->discardCount[1])
        printf("testRemodel(): PASS other player's discard count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's discard count changed.\n");
    if (numberInDeck == G->deckCount[player])
        printf("testRemodel(): PASS current player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL current player's deck count changed.\n");
    if (numberInHand == G->handCount[player])
        printf("testRemodel(): PASS current player's hand count unchanged.\n");
    else
        printf("testRemodel(): FAIL current player's hand count changed.\n");
    if (numberInDiscards == G->discardCount[1])
        printf("testRemodel(): PASS current player's discard count unchanged.\n");
    else 
        printf("testRemodel(): FAIL current player's discard count changed.\n");
    
    altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testRemodel(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            printf("testRemodel(): FAIL victory card supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS victory card supply has not been altered.\n");
    
    
    setupTest(G, 5, cardsInPlay);
    player = 0;
    numberInDeck = G->deckCount[player];
    numberInHand = G->handCount[player];
    numberInDiscards = G->discardCount[player];
    
    G->hand[player][0] = remodel;
    G->hand[player][1] = silver;
    G->hand[player][2] = smithy;
    G->hand[player][3] = adventurer;
    G->hand[player][4] = smithy;
    
    //ensuring other player's state doesn't change
    numInDeck2 = G->deckCount[1];
    numInHand2 = G->handCount[1];
    numInDiscard2 = G->discardCount[1];
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
    printf("testRemodel(): NOTE--Exchanging for value +1 for choice2, should alter victory deck.\n");
    
    choice1 = 2;
    choice2 = duchy;
    result = playRemodel(player, G, handPos, choice1, choice2); 
    
    if (result == 0)
        printf("testRemodel(): PASS didn't produce an error.\n");
    else
        printf("testRemodel(): FAIL produced an error.\n");
    if (numInDeck2 == G->deckCount[1])
        printf("testRemodel(): PASS other player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's deck count changed.\n");
    if (numInHand2 == G->handCount[1])
        printf("testRemodel(): PASS other player's hand count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's hand count changed.\n");
    if (numInDiscard2 == G->discardCount[1])
        printf("testRemodel(): PASS other player's discard count unchanged.\n");
    else
        printf("testRemodel(): FAIL other player's discard count changed.\n");
    if (numberInDeck == G->deckCount[player])
        printf("testRemodel(): PASS current player's deck count unchanged.\n");
    else
        printf("testRemodel(): FAIL current player's deck count changed.\n");
    if (numberInHand == G->handCount[player] +1)
        printf("testRemodel(): PASS current player's hand count decremented correctly.\n");
    else
        printf("testRemodel(): FAIL current player's hand count didn't decrement correctly. Was %d, is now %d.\n", numberInHand, G->handCount[player]);
    if (numberInDiscards == G->discardCount[1] -2)
        printf("testRemodel(): PASS current player's discard count increased by 2.\n");
    else 
        printf("testRemodel(): FAIL current player's discard count was %d, is now %d, but should have incremented by 2.\n", numberInDiscards, G->discardCount[1]);
    
    altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != supplyCount(cardsInPlay[i], G)){
            printf("testRemodel(): FAIL kingdom cards supply has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): PASS kingdom cards supply has not been altered.\n");
    
    altered = 1;
    for (i = 1; i < 4; i++) {
        if (sc[i] != G->supplyCount[i]){
            if(i == choice2 && (sc[i] -1 == G->supplyCount[i]))
                printf("testRemodel(): PASS enum CARD %d's supply has been decremented.\n", cardsInPlay[i]);
            else
                printf("testRemodel(): FAIL victory card supply has been altered incorrectly.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testRemodel(): FAIL victory card supply has not been altered.\n");
}
