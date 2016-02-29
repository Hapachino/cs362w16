#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

void setupTest(struct gameState *G, int cardsInPlay[10]);
void testTribute(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
    int cardsInPlay[10] = {adventurer, tribute, embargo, village, minion, mine, cutpurse,
	   sea_hag, baron, smithy};
   
    setupTest(&G, cardsInPlay); 
    testTribute(&G, cardsInPlay);
    
    return 0;
}

void setupTest(struct gameState *G, int cardsInPlay[10]) {
	int r;
	int numPlayer = 2;
	int seed = time(NULL);
  
	memset(G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, cardsInPlay, seed, G); // initialize a new game
}


void testTribute(struct gameState *G, int cardsInPlay[10]) {
    int result;
    int player = 0;
	int player2 = 1;
    int numberInDiscards = G->discardCount[player];
	int numberInHand = G->handCount[player];
    int numberInDeck = G->deckCount[player];
    int playedCards = G->playedCardCount;
    int numInDeck2 = G->deckCount[player2];
    int numInHand2 = G->handCount[player2];
    int numInDiscard2 = G->discardCount[player2];
    int kc[10];
    int i, j;
    int sc[4];
	
	for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
    
/*     if (numberInHand >= 5) {
        G->hand[player][0] = copper;
        G->hand[player][1] = silver;
        G->hand[player][2] = smithy;
        G->hand[player][3] = adventurer;
        G->hand[player][4] = gold;
    } */
	
	//random deck count/contents
	G->deckCount[player] = 0;
	G->deckCount[player+1] = 0;
	result = 30;
	
	for (j = 0; j < result; j++) {
		  G->deck[player][j] = (rand() % 16) + 1; //random card in range of cards in play
		  G->deckCount[player]++;
		  G->deck[player+1][j] = (rand() % 16) + 1; //random card in range of cards in play
		  G->deckCount[player+1]++;
	}
	
	//ensure that there is something valid in the discards to shuffle if necessary
	for (j = 0; j < 5; j++) {
		G->discard[player][G->discardCount[player]] = (rand() % 16) + 1;
		G->discardCount[player]++;
		G->discard[player+1][G->discardCount[player]] = (rand() % 16) + 1;
		G->discardCount[player+1]++;
	}
	
	//shuffle player deck
	shuffle(player, G);
	shuffle(player+1, G);

	numberInDeck = G->deckCount[player];
	numberInDiscards = G->discardCount[player];
	numberInHand = G->handCount[player];
	numInDeck2 = G->deckCount[1];
    numInDiscard2 = G->discardCount[1];
	numInHand2 = G->handCount[1];
    
    result = playTribute(G);
    
    assert(result == 0);
    printf("testTribute(): PASS didn't produce an error.\n");
    //assert(numInDeck2 == G->deckCount[1]);
    printf("testTribute(): num in deck before: %d, after: %d.\n", numberInDeck, G->deckCount[0]);
    //assert(numInHand2 == G->handCount[1]);
    printf("testTribute(): num in hand before: %d, after: %d.\n", numberInHand, G->handCount[0]);
	printf("testTribute(): num in discards before: %d, after: %d.\n", numberInDiscards, G->discardCount[0]);
    //assert(numInDiscard2 == G->discardCount[1]);
    printf("testTribute(): num in other player's discards before: %d, after: %d.\n", numInDiscard2, G->discardCount[1]);
    printf("testTribute(): number in other player's hand before: %d, after: %d.\n", numInHand2,  G->handCount[1]);
	printf("testTribute(): number in other player's deck before: %d, after: %d.\n", numInDeck2,  G->deckCount[1]);

    //printf("testTribute(): PASS number in hand is +3 cards and -1 discard.\n");
}
