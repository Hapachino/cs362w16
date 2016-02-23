#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testDiscardCard(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
	testDiscardCard(&G, cardsInPlay);
    
    return 0;
    
}

void testDiscardCard(struct gameState *G, int cardsInPlay[10]) {
	int player = 0;
	int trashFlag = 0; 
    int position;
    
    int numberInHand = G->handCount[player];
    int numInHand2 = G->handCount[1];
    int numInDiscard2 = G->discardCount[1];
    int playedCard = G->playedCards[G->playedCardCount];
    int playedCount = G->playedCardCount;
    int kc[10];
    int i;
    
    for (i = 0; i < 10; i++) {
        kc[i] = cardsInPlay[i];
    }
    
    if (numberInHand == 5) {
        G->hand[player][0] = copper;
        G->hand[player][1] = silver;
        G->hand[player][2] = gold;
        G->hand[player][3] = adventurer;
        G->hand[player][4] = smithy;
    }

    
    //test with card in middle of player's hand
    discardCard(2, player, G, trashFlag);
    
    assert(numberInHand == G->handCount[player] +1);
    printf("testDiscardCard(): PASS when remove card from middle of hand, handCount is decremented.\n");
    assert(numInHand2 == G->handCount[1]);
    printf("testDiscardCard(): PASS other player's handcount unchanged.\n");
    assert(numInDiscard2 == G->discardCount[1]);
    printf("testDiscardCard(): PASS other player's discardcount unchanged.\n");
    assert(G->hand[player][1] == silver);
    printf("testDiscardCard(): PASS when remove card from middle of hand, previous card in hand is unchanged.\n");
    assert(G->hand[player][2] == smithy);
    printf("testDiscardCard(): PASS when remove card from middle of hand, last card in hand has been swapped with removed card.\n");
    assert(G->hand[player][3] == adventurer);
    printf("testDiscardCard(): PASS when remove card from middle of hand, card after removed card is unchanged.\n");
    assert(playedCount == G->playedCardCount -1);
    printf("testDiscardCard(): PASS when remove card from middle of hand, playedCardCount is incremented.\n");
    if(G->playedCards[G->playedCardCount-1] != gold) {
        printf("testDiscardCard(): FAIL.  G->playedCards[G->playedCardCount] == %d\n", G->playedCards[G->playedCardCount]);
        printf("G->playedCardCount == %d\n", G->playedCardCount);
    } else {
        printf("testDiscardCard(): PASS when remove card from middle of hand, top played is the removed card.\n");
    }
    
    //test with card at beginning of player's hand
    numberInHand = G->handCount[player];
    playedCard = G->playedCards[G->playedCardCount];
    playedCount = G->playedCardCount;
    
    discardCard(0, player, G, trashFlag);
    assert(numberInHand == G->handCount[player] +1);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, handCount is decremented.\n");
    assert(G->hand[player][0] == adventurer);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, last card of hand is moved to index 0.\n");
    assert(G->hand[player][2] == smithy);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, new last card is unchanged.\n");
    assert(G->hand[player][1] == silver);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, card after swapped card is unchanged.\n");
    if(G->playedCards[G->playedCardCount-1] != copper) {
        printf("testDiscardCard(): FAIL.  G->playedCards[G->playedCardCount] == %d\n", G->playedCards[G->playedCardCount]);
        printf("G->playedCardCount == %d\n", G->playedCardCount);
    } else {
        printf("testDiscardCard(): PASS when remove card from beginning of hand, if trashFlag set to 0 playedCards holds the removed card.\n");
    }
    assert(playedCount == G->playedCardCount -1);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, if trashFlag set to 0 playedCardCount is incremented.\n");
    assert(numInHand2 == G->handCount[1]);
    printf("testDiscardCard(): PASS other player's handcount unchanged.\n");
    assert(numInDiscard2 == G->discardCount[1]);
    printf("testDiscardCard(): PASS other player's discardcount unchanged.\n");
    
    //test with last card of player's hand
    numberInHand = G->handCount[player];
    playedCard = G->playedCards[G->playedCardCount];
    playedCount = G->playedCardCount;
    
    position = G->handCount[player] -1;
    discardCard(position, player, G, trashFlag);
    assert(numberInHand == G->handCount[player] +1);
    printf("testDiscardCard(): PASS when remove card from end of hand, handCount is decremented.\n");
    assert(G->hand[player][0] == adventurer);
    assert(G->hand[player][1] == silver);
    printf("testDiscardCard(): PASS when remove card from end of hand, other cards remain unchanged.\n");
    //assert(G->playedCards[G->playedCardCount] == smithy);
    if(G->playedCards[G->playedCardCount-1] != smithy) {
        printf("testDiscardCard(): FAIL.  G->playedCards[G->playedCardCount] == %d\n", G->playedCards[G->playedCardCount]);
        printf("G->playedCardCount == %d\n", G->playedCardCount);
    } else {
        printf("testDiscardCard(): PASS when remove card from end of hand, top playedCard is removed card.\n");
    }
    assert(playedCount == G->playedCardCount -1);
    printf("testDiscardCard(): PASS when remove card from end of hand, playedCardCount is incremented.\n");
    
    // if 0, test if card added to playedCardCount and playedCards pile
    player = 1;
    trashFlag = 1;
    numberInHand = G->handCount[player];
    playedCard = G->playedCards[G->playedCardCount];
    playedCount = G->playedCardCount;
    if (numberInHand == 5) {
        G->hand[player][0] = copper;
        G->hand[player][1] = silver;
        G->hand[player][2] = gold;
        G->hand[player][3] = adventurer;
        G->hand[player][4] = smithy;
    }
    discardCard(0, player, G, trashFlag);
    
    //assert(numberInHand == G->handCount[player] +1);
    if(numberInHand != G->handCount[player] +1) {
        printf("testDiscardCard(): FAIL.  numberInHand == %d, G->handCount[player] +1 == %d\n", numberInHand, G->handCount[player] +1);
    } else {
        printf("testDiscardCard(): PASS when remove card from beginning of hand, and trashFlag set to 0, handCount is decremented.\n");
    }
    //assert(G->hand[player][0] == smithy);
    if(G->hand[player][0] != smithy) {
        printf("testDiscardCard(): FAIL.  G->hand[player][0] == %d\n", G->hand[player][0]);
    } else {
        printf("testDiscardCard(): PASS when remove card from beginning of hand, and trashFlag set to 0, last card in hand is swapped into index 0.\n");
    }
    assert(G->hand[player][1] == silver);
    printf("testDiscardCard(): PASS when remove card from end of hand, other cards remain unchanged.\n");
    //test to make sure card was not added to playedCards or playedCardCount
    if(G->playedCards[G->playedCardCount-1] == copper) {
        printf("testDiscardCard(): FAIL.  G->playedCards[G->playedCardCount] == %d\n", G->playedCards[G->playedCardCount]);
        printf("G->playedCardCount == %d\n", G->playedCardCount);
    } else {
        printf("testDiscardCard(): PASS when remove card from beginning of hand, and trashFlag set to 0, top playedCard is unchanged.\n");
    }
    assert(playedCount == G->playedCardCount);
    printf("testDiscardCard(): PASS when remove card from beginning of hand, and trashFlag set to 0, playedCardCount is unchanged.\n");

    setupTest(G, 1, cardsInPlay);
    numberInHand = G->handCount[player];
    playedCard = G->playedCards[G->playedCardCount];
    playedCount = G->playedCardCount;
    discardCard(0, player, G, trashFlag);
    
    //testing hand with just one card
    assert(G->handCount[player] == 0);
    printf("testDiscardCard(): PASS when removing only card in hand, and trashFlag set to 0, handCount is decremented to 0.\n");
    //test to make sure card was not added to playedCards or playedCardCount
    if(G->playedCards[G->playedCardCount-1] == copper) {
        printf("testDiscardCard(): FAIL.  G->playedCards[G->playedCardCount] == %d\n", G->playedCards[G->playedCardCount]);
        printf("G->playedCardCount == %d\n", G->playedCardCount);
    } else {
        printf("testDiscardCard(): PASS when removing only card in hand, and trashFlag set to 0, top playedCard is unchanged.\n");
    }
    assert(playedCount == G->playedCardCount);
    printf("testDiscardCard(): PASS when removing only card in hand, and trashFlag set to 0, playedCardCount is unchanged.\n");
    
    int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != cardsInPlay[i]){
            printf("testDiscardCard(): FAIL kingdomCards[] has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testDiscardCard(): PASS kingdomCards[] has not been altered.\n");
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