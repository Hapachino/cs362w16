#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>

void setupTest(struct gameState *G, int cardsInPlay[10], int seed);
void testSmithy(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
	int seed = 200;
	int count = 10000;
    int cardsInPlay[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   
    setupTest(&G, cardsInPlay, seed); //game state and handcount
	
	while(count > 1) {
		testSmithy(&G, cardsInPlay);
		count--;
	}
    
    return 0;
}

void setupTest(struct gameState *G, int cardsInPlay[10], int seed) {
	int r;
	int numPlayer = 2;
  
	memset(G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, cardsInPlay, seed, G); // initialize a new game
}

void testSmithy(struct gameState *G, int cardsInPlay[10]) {
    int result;
    int handPos = 2;
    int player = 0;
    int numberInDiscards = G->discardCount[player];
    int numberInHand = G->handCount[player];
    int numberInDeck = G->deckCount[player];
    int playedCards = G->playedCardCount;
    int numInDeck2;
    int numInHand2;
    int numInDiscard2;
    int kc[10];
    int i, j;
    int sc[4];
	int where = rand() % 2;
	int random;
    
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
	
	//random deck count/contents
	G->deckCount[player] = 0;
	G->deckCount[player+1] = 0;
	result = rand() % MAX_DECK;
	
	for (j = 0; j < result; j++) {
		  G->deck[player][j] = (rand() % 16) + 1; //random card in range of cards in play
		  G->deckCount[player]++;
		  G->deck[player+1][j] = (rand() % 16) + 1; //random card in range of cards in play
		  G->deckCount[player+1]++;
	}
	
	//ensure that there is something valid in the discards to shuffle if necessary
	for (j = 0; j < 3; j++) {
		G->discard[player][G->discardCount[player]] = copper;
		G->discardCount[player]++;
		G->discard[player+1][G->discardCount[player]] = copper;
		G->discardCount[player+1]++;
	}

	//shuffle player deck
	shuffle(player, G);
	shuffle(player+1, G);

	numberInDeck = G->deckCount[player];
	numberInDiscards = G->discardCount[player];
	int handcount;
	
	if (where == 0) //half of the time, pull from the top 50 hand count possibilities
		handcount = MAX_HAND - 50 + (rand() % 50);
	else { //half of the time, pull from either bottom 50 or in the middle somewhere.
		handcount = rand() % 60;
		if (handcount > 50) {
			handcount = MAX_HAND/(handcount - 49);
		}
	}
	
	//to avoid empty hand (causes floating point error because a card needs to be discarded when playing smithy)
	// pick a random number within range of MAX_HAND
	if (handcount == 0)
		handcount = (rand() % (MAX_HAND - 10)) + 1;
	
	G->handCount[player] = 0;
	G->handCount[player+1] = 0;
	
	//populate the hand with random cards
	for (i = 0; i < handcount; i++) {
		random = (rand() % 16) + 1;
		G->hand[player][i] = random; //randomly assign hand cards from cards in play
		G->handCount[player]++;
		G->hand[player+1][i] = random; //randomly assign hand cards from cards in play
		G->handCount[player+1]++;
	}
	
	numInDeck2 = G->deckCount[1];
	numInHand2 = G->handCount[1];
    numInDiscard2 = G->discardCount[1];
	
	handPos = rand() % handcount; //pulling card out of random spot in hand
    result = playSmithy(handPos, G);
	
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