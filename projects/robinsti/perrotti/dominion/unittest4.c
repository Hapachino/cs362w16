/**
 ** Author: Tim Robinson
 ** Tested Function: buyCard
 ** Description: The "test4" function in this file tests if the buyCard 
 ** function behaves as expected and changes a gameState object as expected.
 ** 
 ** This function is intended to be compiled with the unittest1.c file, where
 ** a main function is defined that calls the test4 function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

#define TEST_FUNC "buyCard"

#define SUPPLY_COUNT 25

int test4() {
	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
  struct gameState tmp;
	int max_hand = 5;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));
  memcpy(&tmp, &state, sizeof(struct gameState));


  printf("---------------- Testing %s Function ----------------\n", TEST_FUNC);

  int i;
  int num_buys;
  int supply;
  int coins;
  int ret;

  // Test for each card that may be purchased
  for (supply = 0; supply < SUPPLY_COUNT; supply++)
  {
  	printf("---- Testing card %d ----\n", supply);
  	// Test the following scenarios for the card being purchased:
  	//	- The current player does not have enough buys
  	//	- The current player has 1 buy
  	//	- The current player has more than 1 buy
  	for (num_buys = 0; num_buys < 3; num_buys++) 
	 	{
	 		printf("Player has %d buys\n", num_buys);
	 		state.numBuys = num_buys;
	 		pre.numBuys = num_buys;

	 		ret = buyCard(supply, &state);

	 		if (num_buys == 0) 
	 		{
		 		// Card purchase should be prevented.
		 		// The game state experiencing the purchase should be no different than
		 		// it was before the purchase was made.
	 			assert(ret == -1);
	 			assert(memcmp(&state, &pre, sizeof(struct gameState)) == 0);
	 		}
	 		
	 		printf("Passed\n");

	 		memcpy(&state, &tmp, sizeof(struct gameState));
	 		memcpy(&pre, &tmp, sizeof(struct gameState));
	 	}
	 	
	 	// Test the following scenarios for the card being purchased:
	 	//	- There are no cards remaining to be purchased of the selected type
	 	//	- There is 1 card remaining to be purchased of the selected type
	 	//	- There are more than 1 cards remaining to be purchased of the 
	 	//		selected type
	 	for (i = 0; i < 3; i++) 
	 	{
	 		printf("%d cards available to buy\n", i);
	 		state.supplyCount[supply] = i;
	 		pre.supplyCount[supply] = i;

	 		ret = buyCard(supply, &state);

	 		if (i == 0)
	 		{
		 		// Card purchase should be prevented.
		 		// The game state experiencing the purchase should be no different than
		 		// it was before the purchase was made.
	 			assert(ret == -1);
	 			assert(memcmp(&state, &pre, sizeof(struct gameState)) == 0);
	 		}

	 		printf("Passed\n");

			memcpy(&state, &tmp, sizeof(struct gameState));
	 		memcpy(&pre, &tmp, sizeof(struct gameState));
	 	}

	 	// Test the following scenarios for the card being purchased:
	 	//	- The player does not have enough coins to purchase the current card
	 	//	- The player has the exact amount to purchase the current card
	 	//	- The player has more than enough coins to purchase the current card
	 	printf("Card costs %d coins\n", getCost(supply));
	 	for (coins = 0; coins < 9; coins++)
	 	{
	 		printf("Player has %d coins\n", coins);
	 		state.coins = coins;
	 		pre.coins = coins;

	 		ret = buyCard(supply, &state);

	 		if (coins < getCost(supply))
	 		{
		 		// Card purchase should be prevented.
		 		// The game state experiencing the purchase should be no different than
		 		// it was before the purchase was made.
	 			assert(ret == -1);
	 			assert(memcmp(&state, &pre, sizeof(struct gameState)) == 0);
	 		} else
	 		{
	 			if (ret != -1) 
	 			{
		 			// Phase should advance.
		 			// Card should be added to the current player's deck.
		 			// Coins should be deducted correctly from game state.
		 			// The number of buys should be decremented.
		 			assert(state.phase == 1);
		 			assert(state.discardCount[state.whoseTurn] == pre.discardCount[pre.whoseTurn] + 1);
		 			assert(state.coins == pre.coins - getCost(supply));
		 			assert(state.numBuys == pre.numBuys - 1);
	 			}
	 		}

	 		printf("Passed\n");

	 		memcpy(&state, &tmp, sizeof(struct gameState));
	 		memcpy(&pre, &tmp, sizeof(struct gameState));

	 	}
  }

  printf("\nUNIT TEST 4 PASSED.\n\n");
 	

	return 0;
}