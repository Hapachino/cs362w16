#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int c;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	//put tested card into hand
	G.hand[thisPlayer][handpos] = smithy;

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 3;
	printf("handCount = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	printf("deckCount = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
	printf("playedCardCount = %d, expected = %d\n",testG.playedCardCount, G.playedCardCount + 1);
	assert(testG.playedCardCount == G.playedCardCount + 1);
	printf("playedCard = %d, expected = %d\n", testG.playedCards[0], 13);
	assert(testG.playedCards[0] == smithy);

	//make sure no cards went missing. Since nothing has been added to the deck, there should only be coppers and estates in it.
	printf("fullDeckCount(copper) = %d, expected = %d\n", fullDeckCount(thisPlayer, copper, &testG), fullDeckCount(thisPlayer, copper, &G));
	assert(fullDeckCount(thisPlayer, copper, &testG) == fullDeckCount(thisPlayer, copper, &G));
	printf("fullDeckCount(estate) = %d, expected = %d\n", fullDeckCount(thisPlayer, estate, &testG), fullDeckCount(thisPlayer, estate, &G));
	assert(fullDeckCount(thisPlayer, estate, &testG) == fullDeckCount(thisPlayer, estate, &G));

	//restore changed values and compare with original game
	testG.handCount[thisPlayer] = G.handCount[thisPlayer];
	testG.deckCount[thisPlayer] = G.deckCount[thisPlayer];
	testG.playedCardCount = G.playedCardCount;
	memcpy(&testG.playedCards, &G.playedCards, sizeof(G.playedCards));
	memcpy(&testG.deck[thisPlayer], &G.deck[thisPlayer], sizeof(G.deck[thisPlayer]));
	memcpy(&testG.hand[thisPlayer], &G.hand[thisPlayer], sizeof(G.hand[thisPlayer]));
	c = memcmp(&testG, &G, sizeof(struct gameState));
	printf("memcmp result = %d, expected = %d\n", c, 0);
	assert(c == 0);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


