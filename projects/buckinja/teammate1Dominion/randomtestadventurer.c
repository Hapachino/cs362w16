#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>


void setupTest(struct gameState *G, int cardsInPlay[10], int seed);
void testAdventurer(struct gameState *G, int cardsInPlay[10]);

int main (int argc, char** argv) {
    struct gameState G;
	int seed = 20;
    int cardsInPlay[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   
    setupTest(&G, cardsInPlay, seed); //game state and handcount
	
	while(1)
		testAdventurer(&G, cardsInPlay);
    
    return 0;
}

void setupTest(struct gameState *G, int cardsInPlay[10], int seed) {
	int r;
	int numPlayer = 2;
  
	memset(G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, cardsInPlay, seed, G); // initialize a new game
}

void testAdventurer(struct gameState *G, int cardsInPlay[10]) {
    
    int result;
    int player = 0;
    int i, j, random;
    int numberInDeck = G->deckCount[player];
    int numTreasure = 0;
	int numInDiscards = G->discardCount[player];
    int numTreasureAfter = 0;
    int numberInHand = G->handCount[player];
    int kc[10];
    int sc[4];
	int where = rand() % 2;
	int handcount;
	int numInDeck2;
    int numInHand2;
    int numInDiscard2;
	
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
		G->discard[player+1][G->discardCount[player+1]] = copper;
		G->discardCount[player+1]++;
	}

	//shuffle player deck
	shuffle(player, G);
	shuffle(player+1, G);

	numberInDeck = G->deckCount[player];
	numInDiscards = G->discardCount[player];
		
	if (where == 0) //half of the time, pull from the top 50 hand count possibilities
		handcount = MAX_HAND - 50 + (rand() % 50);
	else { //half of the time, pull from either bottom 50 or in the middle somewhere.
		handcount = rand() % 60;
		if (handcount > 50) {
			handcount = MAX_HAND/(handcount - 49);
		}
	}
	
	G->handCount[player] = 0;
	G->handCount[player+1] = 0;
	
	//populate the hand with random cards and keep track of how many treasures are being inserted.
	for (i = 0; i < handcount; i++) {
		random = (rand() % 16) + 1;
		G->hand[player][i] = random; //randomly assign hand cards from cards in play
		G->hand[player+1][i] = random;
		G->handCount[player]++;
		G->handCount[player+1]++;
		if (G->hand[player][i] == copper || G->hand[player][i] == silver || G->hand[player][i] == gold) {
			numTreasure++;
		}
	}
    
	numberInHand = G->handCount[player];
	
	//save the state of the cardsInPlay array and the estate cards
    for (i = 0; i < 10; i++) {
        kc[i] = supplyCount(cardsInPlay[i], G);
    }
    for (i = 0; i < 4; i++) {
        sc[i] = G->supplyCount[i];
    }
	
	//ensuring other player's state doesn't change
    numInDeck2 = G->deckCount[player+1];
    numInHand2 = G->handCount[player+1];
    numInDiscard2 = G->discardCount[player+1];
	
	//call the function
	result = adventurerCard(G, player);
    
    assert(result == 0);
    printf("testAdventurer(): PASS didn't produce an error.\n");
    assert(numInDeck2 == G->deckCount[1]);
    printf("testAdventurer(): PASS other player's deck count unchanged.\n");
    assert(numInHand2 == G->handCount[1]);
    printf("testAdventurer(): PASS other player's hand count unchanged.\n");
    if(numInDiscard2 == G->discardCount[1])
		printf("testAdventurer(): PASS other player's discard count unchanged.\n");
	else {
		printf("testAdventurer(): FAIL other player's discard count has changed from %d to %d.\n", numInDiscard2, G->discardCount[1]);
		exit(0);
	}
    if(numberInDeck > G->deckCount[player])
		printf("testAdventurer(): PASS some cards were taken from correct player's deck.\n");
	else
		printf("testAdventurer(): FAIL cards were not taken from player's deck.\n");
	int dis = G->discardCount[player] - numInDiscards;
	if(numberInDeck - dis == G->deckCount[player])
		printf("testAdventurer(): PASS correct total number of cards were moved from deck to discards.\n");
	else
		printf("testAdventurer(): FAIL incorrect number of cards were moved from deck to discards.\n");
    
    numTreasureAfter = 0;
    for (i = 0; i < G->handCount[player]; i++) {
        if (G->hand[player][i] == copper ||  G->hand[player][i] == silver || G->hand[player][i] == gold) {
            numTreasureAfter++;
        }
    }
    if(numTreasureAfter == 2)
		printf("testAdventurer(): PASS correct number of treasures found in hand.\n");
	else
		printf("testAdventurer(): FAIL incorrect number of treasures found in hand. Found %d.\n", numTreasureAfter);
    if (numberInHand == G->handCount[player] - 2) {
        printf("testAdventurer(): PASS hand size incremented correctly.\n");
    }
    else {
        printf("testAdventurer(): NEW FAIL hand size incremented incorrectly. Expected %d, found %d.\n", numberInHand +2, G->handCount[player]);
    }
    for (i = 0; i < 10; i++) {
        assert(kc[i] == supplyCount(cardsInPlay[i], G)); 
    }
    printf("testAdventurer(): PASS kingdom cards supply has not been altered.\n");

    for (i = 1; i < 4; i++) {
        assert(sc[i] == G->supplyCount[i]); 
    }
	printf("testAdventurer(): PASS victory card supply has not been altered.\n");
}