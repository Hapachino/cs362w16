/**
 ** Author: Tim Robinson
 ** Tested Function: isGameOver
 ** Description: The "test3" function in this file tests if the isGameOver
 ** function behaves as expected and changes a gameState object as expected.
 ** 
 ** This function is intended to be compiled with the unittest1.c file, where
 ** a main function is defined that calls the test3 function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

#define SUPPLY_COUNT 25
#define TEST_FUNC "isGameOver"

int test3() {
	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
	int max_hand = 5;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};



  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));
  
  printf("---------------- Testing %s Function ----------------\n", TEST_FUNC);

  int i;
  int j;
  int m;
 
  // Return 1 if the game is over
  // Try every combination of game ending conditions

  // Test if the game ends from province supply count == 0
  printf("Out of provinces: game end\n");
 	state.supplyCount[province] = 0;
 	int ret = isGameOver(&state);
 	assert(ret == 1);
 	memcpy(&state, &pre, sizeof(struct gameState));
  printf("Passed\n");

  // Test that the game does not end if supply count for each card is nonzero.
  printf("Each card has a nonzero supply\n");
  for (i = 0; i < SUPPLY_COUNT; i++)
  {
  	state.supplyCount[i] = 1;
  	ret = isGameOver(&state);
  	assert(ret == 0);
  	memcpy(&state, &pre, sizeof(struct gameState));
  }
  printf("Passed\n");

  // Test that the game does not end if supply count for exactly 1 card is 0
  // for every possible card.
  printf("Exactly 1 card has zero supply\n");
  for (i = 0; i < SUPPLY_COUNT; i++) 
  {
    // Ignore the case of supply count of provinces equal to zero (tested 
    // above)
  	if (i == 3)
  	{
  		memcpy(&state, &pre, sizeof(struct gameState));
  		continue;
  	}

  	state.supplyCount[i] = 0;

  	ret = isGameOver(&state);
  	assert(ret == 0);
  	memcpy(&state, &pre, sizeof(struct gameState));
  }
  printf("Passed\n");

  // Test that the game does not end if supply count for exactly 2 cards is 0,
  // for every combination of 2 cards.
  printf("Exactly 2 cards has zero supply\n");
  for (i = 0; i < SUPPLY_COUNT; i++) 
  {
  	for (j = i + 1; j < SUPPLY_COUNT; j++)
  	{
      
      // Ignore the case of supply count of provinces equal to zero (tested 
      // above)
  		if ((i != 3) && (j != 3))
  		{
	  		state.supplyCount[i] = 0;
	  		state.supplyCount[j] = 0;
	  		ret = isGameOver(&state);
	  		assert(ret == 0);
	  		memcpy(&state, &pre, sizeof(struct gameState));
  		}
  	}
  }
  printf("Passed\n");

  // Test that the game ends if supply count for exactly 3 cards is 0 for every
  // combination of 3 cards.
  printf("Exactly 3 cards has zero supply\n");
  for (i = 0; i < SUPPLY_COUNT; i++)
  {
  	for (j = i + 1; j < SUPPLY_COUNT; j++)
  	{
  		for (m = j + 1; m < SUPPLY_COUNT; m++)
  		{
  			if ((i != 3) && (j != 3) && (m != 3))
  			{
	  			state.supplyCount[i] = 0;
		  		state.supplyCount[j] = 0;
		  		state.supplyCount[m] = 0;

		  		ret = isGameOver(&state);
		  		assert(ret == 1);
		  		memcpy(&state, &pre, sizeof(struct gameState));
				}
  		}
  	}
  }
  printf("Passed\n");

  printf("\nUNIT TEST 3 PASSED.\n\n");


	return 0;
}