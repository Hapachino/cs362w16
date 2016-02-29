/*
 * testing cards
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define NUM_ITER 10

int testAdventurerCard(int card, struct gameState *g, int currentPlayer, int *idx);
int testSmithyCard(int card, struct gameState *g, int currentPlayer, int *n);
int testVillageCard(int card, struct gameState *g, int currentPlayer, int *idx);
int testGreatHallCard(int card, struct gameState *g, int currentPlayer, int *idx);
void printResults(struct gameState *g, struct gameState *g2, int currentPlayer, int handPos);

int main(int argc, char **argv) {
	enum CARD card;
	if (argc == 2) {
		if (!strcmp(*(argv+1), "adventurer")) card = adventurer;
		else if (!strcmp(*(argv+1), "smithy")) card = smithy;
		else if (!strcmp(*(argv+1), "council_room")) card = council_room;
		else if (!strcmp(*(argv+1), "feast")) card = feast;
		else if (!strcmp(*(argv+1), "gardens")) card = gardens;
		else if (!strcmp(*(argv+1), "mine")) card = mine;
		else if (!strcmp(*(argv+1), "remodel")) card = remodel;
		else if (!strcmp(*(argv+1), "village")) card = village;
		else if (!strcmp(*(argv+1), "baron")) card = baron;
		else if (!strcmp(*(argv+1), "great_hall")) card = great_hall;
		else if (!strcmp(*(argv+1), "minion")) card = minion;
		else if (!strcmp(*(argv+1), "steward")) card = steward;
		else if (!strcmp(*(argv+1), "tribute")) card = tribute;
		else if (!strcmp(*(argv+1), "ambassador")) card = ambassador;
		else if (!strcmp(*(argv+1), "cutpurse")) card = cutpurse;
		else if (!strcmp(*(argv+1), "embargo")) card = embargo;
		else if (!strcmp(*(argv+1), "outpost")) card = outpost;
		else if (!strcmp(*(argv+1), "salvager")) card = salvager;
		else if (!strcmp(*(argv+1), "sea_hag")) card = sea_hag;
		else if (!strcmp(*(argv+1), "treasure_map")) card = treasure_map;
		else {
			printf("Usage: testcard adventurer\n");
			return 0;
		}
	}
	else {
		printf("Usage: testcard adventurer\n");
		return 0;
	}

	// testing only adventurer, smithy, village, and great hall cards at this time
	if (card != adventurer && card != smithy && card != village && card != great_hall) {
		printf("Usage: testcard adventurer\n");
		return 0;
	}

	printf("Testing %s card...\n\n", argv[1]);

	srand(time(NULL));
	// random integer between 0 and 19
	// int r = rand() % 20;

	int i, j, player = 0;
	for (i=0; i<NUM_ITER; ++i) {
		// set a game
		struct gameState G;
		G.numPlayers = 2;

		if (card == adventurer && i < NUM_ITER/3) {
			G.deckCount[player] = 0;
			G.deckCount[player+1] = 0;
		}
		else {
			G.deckCount[player] = rand() % MAX_DECK;
			G.deckCount[player+1] = rand() % MAX_DECK;
		}

		G.discardCount[player] = rand() % MAX_DECK;
		G.discardCount[player+1] = rand() % MAX_DECK;
		G.handCount[player] = rand() % MAX_HAND;
		G.handCount[player+1] = rand() % MAX_HAND;
		G.playedCardCount = 0;

		// set cards on the deck
		for (j=0; j<G.deckCount[player]; ++j)
			G.deck[player][j] = rand() % (treasure_map + 1);
		for (j=0; j<G.deckCount[player+1]; ++j)
			G.deck[player+1][j] = rand() % (treasure_map + 1);

		// set cards discarded
		for (j=0; j<G.discardCount[player]; ++j)
			G.discard[player][j] = rand() % (treasure_map + 1);
		for (j=0; j<G.discardCount[player+1]; ++j)
			G.discard[player+1][j] = rand() % (treasure_map + 1);

		// set cards on hand
		for (j=0; j<G.handCount[player]; ++j)
			G.hand[player][j] = rand() % (treasure_map + 1);
		for (j=0; j<G.handCount[player+1]; ++j)
			G.hand[player+1][j] = rand() % (treasure_map + 1);

		// set played cards count
		int n;
		for (j=0; j<MAX_DECK; ++j) {
			n = rand() % MAX_DECK;
			G.playedCards[j] = n;
			//G.playedCardCount += n;
		}
		
		switch (card) {
			case adventurer:
				testAdventurerCard(card, &G, player, &i);
				break;
			case smithy:
				testSmithyCard(card, &G, player, &i);
				break;
			case village:
				testVillageCard(card, &G, player, &i);
				break;
			case great_hall:
				testGreatHallCard(card, &G, player, &i);
				break;
			default:
				break;
		}
	}

	printf("\nTesting %s card done...\n", *(argv+1));
	printf("/***************************************************************/\n");

	return 0;
}

int testAdventurerCard(int card, struct gameState *g, int currentPlayer, int *idx) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));
	
	// run copied game against case to be supposed to be
	int drawntreasure = 0;
	int cardDrawn;
	int temphand[MAX_HAND];
	int z = 0; // this is the counter for the temp hand
	while (drawntreasure < 2) {
		if (g->deckCount[currentPlayer] < 1) // if the deck is empty we need to shuffle discard and add to deck
			shuffle(currentPlayer, g);

		drawCard(currentPlayer, g);
		cardDrawn = g->hand[currentPlayer][g->handCount[currentPlayer]-1]; // top card of hand is most recently drawn card

		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
			drawntreasure++;
		else {
			temphand[z] = cardDrawn;
			g->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one)
			z++;
		}
	}
	while (z-1 >= 0) {
		g->discard[currentPlayer][g->discardCount[currentPlayer]++] = temphand[z-1]; // discard all cards in play that have been drawn
		z--;
	}
	
	// run game against code to be tested
	cardEffect(card, 0, 0, 0, &g2, 0, 0);
	
	// compare results
	printf("Iteration #%d ......\n", *idx+1);
	printResults(g, &g2, currentPlayer, -1);
	
	return 0;
}

int testSmithyCard(int card, struct gameState *g, int currentPlayer, int *idx) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));
	
	// run copied game against case to be supposed to be
	int handPos = rand() % g->handCount[currentPlayer];

	// +3 cards
	int i;
	for (i = 0; i < 3; ++i)
		drawCard(currentPlayer, g);

	// discard card from hand
	discardCard(handPos, currentPlayer, g, 0);
	
	// run game against code to be tested
	cardEffect(card, 0, 0, 0, &g2, handPos, 0);
	
	// compare results
	printf("Iteration #%d ......\n", *idx+1);
	printResults(g, &g2, currentPlayer, handPos);
	
	return 0;
}

int testVillageCard(int card, struct gameState *g, int currentPlayer, int *idx) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));

	// run copied game against case to be supposed to be
	int handPos;
	if (*idx < 3) // first hand position
		handPos = 0;
	else if (*idx >= 3 && *idx < 6) // last hand position (handCount will decrement after drawCard() gets called)
		handPos = g->handCount[currentPlayer];
	else // random hand position
		handPos = rand() % g->handCount[currentPlayer];

	// +1 card
	drawCard(currentPlayer, g);
	// +2 actions
	g->numActions = g->numActions + 2;
	// discard played card from hand
	discardCard(handPos, currentPlayer, g, 0);

	// run game against code to be tested
	cardEffect(card, 0, 0, 0, &g2, handPos, 0);

	// compare results
	printf("Iteration #%d ......\n", *idx+1);
	printResults(g, &g2, currentPlayer, handPos);

	return 0;
}

int testGreatHallCard(int card, struct gameState *g, int currentPlayer, int *idx) {
	struct gameState g2;
	memcpy(&g2, g, sizeof(struct gameState));

	// run copied game against case to be supposed to be
	int handPos;
	if (*idx < 3) // first hand position
		handPos = 0;
	else if (*idx >= 3 && *idx < 6) // last hand position (handCount will decrement after drawCard() gets called)
		handPos = g->handCount[currentPlayer];
	else // random hand position
		handPos = rand() % g->handCount[currentPlayer];

	// +1 card
	drawCard(currentPlayer, g);
	// +1 actions
	g->numActions++;
	// discard played card from hand
	discardCard(handPos, currentPlayer, g, 0);

	// run game against code to be tested
	cardEffect(card, 0, 0, 0, &g2, handPos, 0);

	// compare results
	printf("Iteration #%d ......\n", *idx+1);
	printResults(g, &g2, currentPlayer, handPos);

	return 0;
}

void printResults(struct gameState *g, struct gameState *g2, int currentPlayer, int handPos) {
	if (g->deckCount[currentPlayer] != g2->deckCount[currentPlayer]) {
		printf("expected    deck cnt: %d\n", g->deckCount[currentPlayer]);
		printf("tested      deck cnt: %d\n", g2->deckCount[currentPlayer]);
	}

	if (g->discardCount[currentPlayer] != g2->discardCount[currentPlayer]) {
		printf("expected discard cnt: %d\n", g->discardCount[currentPlayer]);
		printf("tested   discard cnt: %d\n", g2->discardCount[currentPlayer]);
	}

	if (g->handCount[currentPlayer] != g2->handCount[currentPlayer]) {
		printf("expected    hand cnt: %d\n", g->handCount[currentPlayer]);
		printf("tested      hand cnt: %d\n", g2->handCount[currentPlayer]);
	}

	if (handPos > -1) {
		if (g->hand[currentPlayer][handPos] != g2->hand[currentPlayer][handPos]) {
			printf("expected card at hand pos %d: %d\n", handPos, g->hand[currentPlayer][handPos]);
			printf("tested   card at hand pos %d: %d\n", handPos, g2->hand[currentPlayer][handPos]);
		}
	}
	if (g->numActions != g2->numActions) {
		printf("expected number of actions: %d\n", g->numActions);
		printf("tested   number of actions: %d\n", g2->numActions);
	}

	// next player's card counts should not be affected
	if (g->deckCount[currentPlayer+1] != g2->deckCount[currentPlayer+1]) {
		printf("expected    deck cnt for next player: %d\n", g->deckCount[currentPlayer+1]);
		printf("tested      deck cnt for next player: %d\n", g2->deckCount[currentPlayer+1]);
	}

	if (g->discardCount[currentPlayer+1] != g2->discardCount[currentPlayer+1]) {
		printf("expected discard cnt for next player: %d\n", g->discardCount[currentPlayer+1]);
		printf("tested   discard cnt for next player: %d\n", g2->discardCount[currentPlayer+1]);
	}

	if (g->handCount[currentPlayer+1] != g2->handCount[currentPlayer+1]) {
		printf("expected    hand cnt for next player: %d\n", g->handCount[currentPlayer+1]);
		printf("tested      hand cnt for next player: %d\n", g2->handCount[currentPlayer+1]);
	}
}
