#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "embargo"

int main() {
    int newCards = 0;
    int newCoins = 0;
    int discarded = 1;

    int i, c, result;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1090;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	//put tested card into hand
	G.hand[thisPlayer][handpos] = embargo;
	printf("\n----------------- Testing Card: %s ----------------\n\n", TESTCARD);
	
	for (i = 0; i < 10; i++)
	{
		printf("Test %d: pile #%d --------------------------------\n", i+1, i);
		choice1 = k[i];

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		result = cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
		assert(result == 0);

		newCoins = 2;
		printf("handCount = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
		printf("deckCount = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);
		printf("coins = %d, expected = %d\n",testG.coins, G.coins + newCoins);
		assert(testG.coins == G.coins + newCoins);
		//card is trashed, so playedCardCount should not increment
		printf("playedCardCount = %d, expected = %d\n",testG.playedCardCount, G.playedCardCount);
		assert(testG.playedCardCount == G.playedCardCount);
		printf("embargo tokens on k[i] = %d, expected = %d\n",testG.embargoTokens[k[i]], G.embargoTokens[k[i]] + 1);
		assert(testG.embargoTokens[k[i]] == G.embargoTokens[k[i]] + 1);

		//make sure no cards went missing. Since nothing has been added to the deck, there should only be coppers and estates in it.
		printf("fullDeckCount(copper) = %d, expected = %d\n", fullDeckCount(thisPlayer, copper, &testG), fullDeckCount(thisPlayer, copper, &G));
		assert(fullDeckCount(thisPlayer, copper, &testG) == fullDeckCount(thisPlayer, copper, &G));
		printf("fullDeckCount(estate) = %d, expected = %d\n", fullDeckCount(thisPlayer, estate, &testG), fullDeckCount(thisPlayer, estate, &G));
		assert(fullDeckCount(thisPlayer, estate, &testG) == fullDeckCount(thisPlayer, estate, &G));
		
		//restore changed values and compare with original game
		testG.handCount[thisPlayer] = G.handCount[thisPlayer];
		testG.deckCount[thisPlayer] = G.deckCount[thisPlayer];
		testG.embargoTokens[k[i]] = G.embargoTokens[k[i]];
		testG.coins = G.coins;
		memcpy(&testG.playedCards, &G.playedCards, sizeof(G.playedCards));
		memcpy(&testG.deck[thisPlayer], &G.deck[thisPlayer], sizeof(G.deck[thisPlayer]));
		memcpy(&testG.hand[thisPlayer], &G.hand[thisPlayer], sizeof(G.hand[thisPlayer]));
		c = memcmp(&testG, &G, sizeof(struct gameState));
		printf("memcmp result = %d, expected = %d\n", c, 0);
		assert(c == 0);
		printf("\n");
	}
	printf("Test %d: invalid pile --------------------------------\n", i+1);
	choice1 = baron;

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	result = cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
	//this should fail since it's not a valid pile
	//assert(result != 0);
	printf("return value from cardEffect = %d, expected = %d\n", result, -1);

	//game should be unchanged
	c = memcmp(&testG, &G, sizeof(struct gameState));
	printf("memcmp result = %d, expected = %d\n", c, 0);
	//assert(c == 0);
	printf("\n");	



	//the below code is accomplished instead by the memcmp above.
/*
	//check other players deck, hand, and discard
	printf("other player's deckCount = %d, expected = %d\n",testG.deckCount[1], G.deckCount[1]);
	assert(testG.deckCount[1] == G.deckCount[1]);
	printf("other player's handCount = %d, expected = %d\n",testG.handCount[1], G.handCount[1]);
	assert(testG.handCount[1] == G.handCount[1]);
	printf("other player's discardCount = %d, expected = %d\n", testG.discardCount[1], G.discardCount[1]);
	assert(testG.discardCount[1] == G.discardCount[1]);

	//check supply
	for (i=0; i < 10; i++)
	{
		printf("kingdom card supply count %d = %d, expected = %d\n", i, testG.supplyCount[k[i]], G.supplyCount[k[i]]);
		assert(testG.supplyCount[k[i]] == G.supplyCount[k[i]]);
	}
	printf("estate supply = %d, expected = %d\n",testG.supplyCount[estate], G.supplyCount[estate]);
	assert(testG.supplyCount[estate] == G.supplyCount[estate]);
	printf("duchy supply = %d, expected = %d\n",testG.supplyCount[duchy], G.supplyCount[duchy]);
	assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
	printf("province supply = %d, expected = %d\n",testG.supplyCount[province], G.supplyCount[province]);
	assert(testG.supplyCount[province] == G.supplyCount[province]);

*/
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


