/* -----------------------------------------------------------------------
 * test Adventurer Card
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 cardtest2.c dominion.o rngs.o
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int checkDrawCard(int p, struct gameState *G) {
	struct gameState G2;
	memcpy (&G2, G, sizeof(struct gameState));

	int r = drawCard(p, G);

	if (G2.deckCount[p] > 0) {
		G2.handCount[p]++;
		G2.hand[p][G2.handCount[p]-1] = G2.deck[p][G2.deckCount[p]-1]; // add card to the hand
		G2.deckCount[p]--;
	}
	else {
		memcpy(G2.deck[p], G->deck[p], sizeof(int)*G2.discardCount[p]);
		memcpy(G2.discard[p], G->discard[p], sizeof(int)*G2.discardCount[p]);

		G2.hand[p][G->handCount[p]-1] = G->hand[p][G->handCount[p]-1];
		G2.handCount[p]++;
		G2.deckCount[p] = G2.discardCount[p]-1;
		G2.discardCount[p] = 0;
	}

	assert(r == 0);

	int result = memcmp(&G2, G, sizeof(struct gameState));
	assert(result == 0);
	if (result == 0)
		printf("Draw card test passed!\n");
	else
		printf("Draw card test failed!\n");

	return 0;
}

int main() {
	srand(time(NULL));

	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G, G2;

	memset(&G, 23, sizeof(struct gameState));
	initializeGame(2, k, 1000, &G);
	memcpy (&G2, &G, sizeof(struct gameState));

	int drawntreasure = 0, currentPlayer = 0, cardDrawn;
	int temphand[MAX_HAND]; // moved above the if statement
	int z = 0;// this is the counter for the temp hand

	int discardcnt = rand() % 100;
	//printf("discardcnt: %d\n", discardcnt);
	G.discardCount[currentPlayer] = discardcnt;

	int handcnt = rand() % 10 + 1;
	//printf("handcnt: %d\n", handcnt);
	G.handCount[currentPlayer] = handcnt;

	while (drawntreasure < 2) {
		if (G.deckCount[currentPlayer] < 1) { //if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &G);
		}

		drawCard(currentPlayer, &G);

		cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			G.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}

	while (z >= 1) {
		G.discard[currentPlayer][G.discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
		z--;
	}


	G2.discardCount[currentPlayer] = discardcnt;
	G2.handCount[currentPlayer] = handcnt;
	drawntreasure = 0;

	while (drawntreasure < 2) {
		if (G2.deckCount[currentPlayer] < 1) { //if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, &G2);
		}

		int deckCounter = G2.deckCount[currentPlayer];//Create holder for the deck count
		int count = G2.handCount[currentPlayer];
		G2.hand[currentPlayer][count] = G2.deck[currentPlayer][deckCounter - 1];//Add card to the hand
		G2.deckCount[currentPlayer]--;
		G2.handCount[currentPlayer]++;//Increment hand count

		cardDrawn = G2.hand[currentPlayer][G2.handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			G2.handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
			z++;
		}
	}
	while (z >= 1) {
		G2.discard[currentPlayer][G2.discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
		z--;
	}

	int result = memcmp(&G2, &G, sizeof(struct gameState));
	assert(result == 0);
	if (result == 0)
		printf("Adventurer card test passed!\n");
	else
		printf("Adventurer card test failed!\n");

	return 0;
}
