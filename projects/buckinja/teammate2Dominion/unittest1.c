#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int handCount, int cardsInPlay[10]);
void testGainCard(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, 5, cardsInPlay); //game state and handcount
	testGainCard(&G, cardsInPlay);
    
    return 0;
}

void testGainCard(struct gameState *G, int cardsInPlay[10]) {

    enum CARD c = adventurer;
	int player = 0;
      // toFlag = 0 : add to discard
      // toFlag = 1 : add to deck
      // toFlag = 2 : add to hand
	int flag = 0; 
    int kc[10];
    int i;
    
    for (i = 0; i < 10; i++) {
        kc[i] = cardsInPlay[i];
    }    
    
    for (flag = 0; flag < 3; flag++) {
        int numberInDiscards = G->discardCount[player];
        int topOfDiscards = G->discard[player][ G->discardCount[player] ];
        int numberInSupplyPile = G->supplyCount[c];
        int numberInHand = G->handCount[player];
        int numberInDeck = G->deckCount[player];
        int numInHand2 = G->handCount[1];
        int numInDeck2 = G->deckCount[1];
        int numInDiscard2 = G->discardCount[1];
        
        gainCard(c, G, flag, player);
        
        if (flag == 0) {
            assert(numberInDiscards == G->discardCount[player] -1);
            printf("testGainCard(): PASS when add to discard, discardCount is incremented.\n");
            assert(numInDiscard2 == G->discardCount[1]);
            printf("testGainCard(): PASS other player's discard count unchanged.\n");
            assert(G->discard[player][ G->discardCount[player] -1] == adventurer);
            printf("testGainCard(): PASS when add adventurer to discard, last item in discard is adventurer.\n");
        } else {
            assert(numberInDiscards == G->discardCount[player]);
            printf("testGainCard(): PASS when NOT add to discard, discardCount is unchanged.\n");
            assert(G->discard[player][ G->discardCount[player] ] == topOfDiscards);
            printf("testGainCard(): PASS when NOT add to discard, last item added to discard is unchanged.\n");
            assert(numInDiscard2 == G->discardCount[1]);
            printf("testGainCard(): PASS other player's discard count unchanged.\n");
        }
        
        if (flag == 1) {
            assert(numberInDeck == G->deckCount[player] -1);
            printf("testGainCard(): PASS when add to deck, deckCount is incremented.\n");
            assert(G->deck[player][ G->deckCount[player] -1] == adventurer);
            printf("testGainCard(): PASS when add adventurer to deck, last item in deck is adventurer.\n");
            assert(numInDeck2 == G->deckCount[1]);
            printf("testGainCard(): PASS other player's deck count unchanged.\n");
        } else {
            assert(numberInDeck == G->deckCount[player]);
            printf("testGainCard(): PASS when NOT add to deck, deckCount is unchanged.\n");
            assert(numInDeck2 == G->deckCount[1]);
            printf("testGainCard(): PASS other player's deck count unchanged.\n");
        }
        
        if (flag == 2) {
            assert(numberInHand == G->handCount[player] -1);
            printf("testGainCard(): PASS when add to hand, handCount is incremented.\n");
            assert(G->hand[player][ G->handCount[player] -1] == adventurer);
            printf("testGainCard(): PASS when add adventurer to hand, last item in hand is adventurer.\n");
            assert(numInHand2 == G->handCount[1]);
            printf("testGainCard(): PASS other player's hand count unchanged.\n");
        } else {
            assert(numberInHand == G->handCount[player]);
            printf("testGainCard(): PASS when NOT add to hand, handCount is unchanged.\n");
            assert(numInHand2 == G->handCount[1]);
            printf("testGainCard(): PASS other player's hand count unchanged.\n");
        }
        
        assert(numberInSupplyPile == G->supplyCount[c] +1);
        printf("testGainCard(): PASS when gain adventurer card, supplyCount of adventurer is decremented.\n");
        
    }
    
    //setting the amount of this card type to zero (none left)
    G->supplyCount[c] = 0;
    assert(gainCard(c, G, flag, player) == -1);
    printf("testGainCard(): PASS when adventurer supplyCount set to empty, gainCard returns -1.\n");
    
    //there is no card type with enum that equals 50
    assert(gainCard(50, G, flag, player) == -1);
    printf("testGainCard(): PASS when attempting to gainCard with invalid card type number, gainCard returns -1.\n");

	int altered = 1;
    for (i = 0; i < 10; i++) {
        if (kc[i] != cardsInPlay[i]){
            printf("testGainCard(): FAIL kingdomCards[] has been altered.\n");
            altered = 0;
        }  
    }
    if (altered == 1)
        printf("testGainCard(): PASS kingdomCards[] has not been altered.\n");
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
