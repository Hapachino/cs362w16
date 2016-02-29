#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RSEED 5 // change random seed here
#define CARD silver //change test card here

int main() {
	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	initializeGame(2, cards, RSEED, &state);


	printf("TEST: BUYCARD\n\n");
	printf("Test card = ");
	int testcard = CARD;
	switch( testcard ) 
    {
    case curse:
      printf("curse\n");
    	break;
    case estate:
      printf("estate\n");
    	break;
    case duchy:
      printf("duchy\n");
    	break;
    case province:
      printf("province\n");
    	break;
    case copper:
      printf("copper\n");
    	break;
    case silver:
      printf("silver\n");
    	break;
    case gold:
      printf("gold\n");
    	break;
    case adventurer:
      printf("adventurer\n");
    	break;
    case council_room:
      printf("council_room\n");
    	break;
    case feast:
      printf("feast\n");
    	break;
    case gardens:
      printf("gardens\n");
    	break;
    case mine:
      printf("mine\n");
    	break;
    case remodel:
      printf("remodel\n");
    	break;
    case smithy:
      printf("smithy\n");
    	break;
    case village:
      printf("village\n");
    	break;
    case baron:
      printf("baron\n");
    	break;
    case great_hall:
      printf("great_hall\n");
    	break;
    case minion:
      printf("minion\n");
    	break;
    case steward:
      printf("steward\n");
    	break;
    case tribute:
      printf("tribute\n");
    	break;
    case ambassador:
      printf("ambassador\n");
    	break;
    case cutpurse:
      printf("cutpurse\n");
    	break;
    case embargo: 
      printf("embargo\n");
    	break;
    case outpost:
      printf("outpost\n");
    	break;
    case salvager:
      printf("salvager\n");
    	break;
    case sea_hag:
      printf("sea_hag\n");
    	break;
    case treasure_map:
      printf("treasure_map\n");
      break;
    }




	printf("TEST: buy with enough coins and buy\n");
	state.coins = 10;
	int curCoins = state.coins;
	state.numBuys = 1;
	int curBuys = state.numBuys;
	state.whoseTurn = 0;
	int cardCount = supplyCount(CARD, &state);
	int deckCount = fullDeckCount(0, CARD, &state);

	assert(buyCard(CARD, &state) > -1);
	printf("Coins: %d; Expected: %d\n", state.coins, 10 - getCost(CARD));
	if (state.coins == 10 - getCost(CARD))
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Buys: %d; Expected: %d\n", state.numBuys, 0);
	if (state.numBuys == 0)
		printf ("PASSED\n");
	else
		printf("FAILED\n");

	printf("Card supply: %d; Expected: %d\n", supplyCount(CARD, &state), cardCount - 1);
	if (supplyCount(CARD, &state) == cardCount - 1)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Cards in deck: %d; Expected: %d\n", fullDeckCount(0, CARD, &state), deckCount + 1);
	if (fullDeckCount(0, CARD, &state) == deckCount + 1)
		printf ("PASSED\n");
	else
		printf("FAILED\n");


	printf("TEST: buy with not enough buys\n");
	curCoins = state.coins;
	state.numBuys = 0;
	curBuys = state.numBuys;
	cardCount = supplyCount(CARD, &state);
	deckCount = fullDeckCount(0, CARD, &state);
	assert(buyCard(CARD, &state) == -1);
	printf("Coins: %d; Expected: %d\n", state.coins, curCoins);
	if (state.coins == curCoins)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Buys: %d; Expected: %d\n", state.numBuys, curBuys);
	if (state.numBuys == curBuys)
		printf ("PASSED\n");
	else
		printf("FAILED\n");

	printf("Card supply: %d; Expected: %d\n", supplyCount(CARD, &state), cardCount);
	if (supplyCount(CARD, &state) == cardCount)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Cards in deck: %d; Expected: %d\n", fullDeckCount(0, CARD, &state), deckCount);
	if (fullDeckCount(0, CARD, &state) == deckCount)
		printf ("PASSED\n");
	else
		printf("FAILED\n");


	printf("TEST: buy with not enough supply\n");
	state.coins = 5;
	curCoins = state.coins;
	state.numBuys = 1;
	curBuys = state.numBuys;
	state.supplyCount[CARD] = 0;
	cardCount = supplyCount(CARD, &state);
	deckCount = fullDeckCount(0, CARD, &state);
	assert(buyCard(CARD, &state) == -1);
	printf("Coins: %d; Expected: %d\n", state.coins, curCoins);
	if (state.coins == curCoins)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Buys: %d; Expected: %d\n", state.numBuys, curBuys);
	if (state.numBuys == curBuys)
		printf ("PASSED\n");
	else
		printf("FAILED\n");

	printf("Card supply: %d; Expected: %d\n", supplyCount(CARD, &state), cardCount);
	if (supplyCount(CARD, &state) == cardCount)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	printf("Cards in deck: %d; Expected: %d\n", fullDeckCount(0, CARD, &state), deckCount);
	if (fullDeckCount(0, CARD, &state) == deckCount)
		printf ("PASSED\n");
	else
		printf("FAILED\n");


	printf("TEST: buy with not enough coins\n");
	state.coins = 1;
	curCoins = state.coins;
	state.numBuys = 1;
	curBuys = state.numBuys;
	cardCount = supplyCount(CARD, &state);
	deckCount = fullDeckCount(0, CARD, &state);
	if (CARD == copper || CARD == curse)
		assert(buyCard(CARD, &state) == 0);
	else
		assert(buyCard(CARD, &state) == -1);
	printf("Coins: %d; Expected: %d\n", state.coins, curCoins);
	if (state.coins == curCoins)
		printf ("PASSED\n");
	else
		printf ("FAILED\n");
	
	if (CARD == copper || CARD == curse) {
		printf("Buys: %d; Expected: %d\n", state.numBuys, curBuys - 1);
		if (state.numBuys == curBuys - 1)
			printf ("PASSED\n");
		else
			printf("FAILED\n");
	}
	else {
		printf("Buys: %d; Expected: %d\n", state.numBuys, curBuys);
		if (state.numBuys == curBuys)
			printf ("PASSED\n");
		else
			printf("FAILED\n");
	}

	if (CARD == copper || CARD == curse) {
		printf("Card supply: %d; Expected: %d\n", supplyCount(CARD, &state), cardCount - 1);
		if (supplyCount(CARD, &state) == cardCount - 1)
			printf ("PASSED\n");
		else
			printf ("FAILED\n");
	}
	else {
		printf("Card supply: %d; Expected: %d\n", supplyCount(CARD, &state), cardCount);
		if (supplyCount(CARD, &state) == cardCount)
			printf ("PASSED\n");
		else
			printf ("FAILED\n");
	}
	
	if (CARD == copper || CARD == curse) {
		printf("Cards in deck: %d; Expected: %d\n", fullDeckCount(0, CARD, &state), deckCount + 1);
		if (fullDeckCount(0, CARD, &state) == deckCount + 1)
			printf ("PASSED\n");
		else
			printf("FAILED\n");
	}
	else {
		printf("Cards in deck: %d; Expected: %d\n", fullDeckCount(0, CARD, &state), deckCount);
		if (fullDeckCount(0, CARD, &state) == deckCount)
			printf ("PASSED\n");
		else
			printf("FAILED\n");
	}

	return 0;
}