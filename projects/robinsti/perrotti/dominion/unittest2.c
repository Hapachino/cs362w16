/**
 ** Author: Tim Robinson
 ** Tested Function: isGameOver
 ** Description: The "test2" function in this file tests if the gainCard
 ** function behaves as expected and changes a gameState object as expected.
 ** 
 ** This function is intended to be compiled with the unittest1.c file, where
 ** a main function is defined that calls the test2 function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"

#define MAX_HAND_TEST 5
#define SUPPLY_COUNT 25
#define TEST_FUNC "gainCard"

int test2() {
	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
	int max_hand = 5;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};
  int pre_hand[MAX_HAND_TEST];

  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));

  printf("---------------- Testing %s Function ----------------\n", TEST_FUNC);

  // For each of the possible supply cards.
  int supply;
  for (supply = 0; supply < SUPPLY_COUNT; supply++)
  {
  	printf("---- Testing card %d ----\n", supply);
  	// If the supply card is in the game
  	if (state.supplyCount[supply] != -1)
  	{
  		// For adding a card to a deck, a hand, or a discard pile
  		int to_flag;
	  	for (to_flag = 0; to_flag < 3; to_flag++)
	  	{
	  		if (to_flag == 0)
	  		{
	  			printf("Gain to discard, ");
	  		} else if (to_flag == 1)
	  		{
	  			printf("Gain to deck, ");
	  		} else
	  		{
	  			printf("Gain to hand, ");
	  		}

	  		// For each player
	  		int player;
	  		for (player = 0; player < num_players; player++)
	  		{
					printf("for player %d\n", player);	  			
					gainCard(supply, &state, to_flag, player);

					// If adding card to the discard pile
	  			if (to_flag == 0)
	  			{
	  				assert(state.discardCount[player] == pre.discardCount[player] + 1);
	  				assert(state.discard[player][pre.discardCount[player]] == supply);
	  			
	  			// If adding card to the deck
	  			} else if (to_flag == 1)
	  			{
	  				assert(state.deckCount[player] == pre.deckCount[player] + 1);
	  				assert(state.deck[player][pre.deckCount[player]] == supply);

	  			// If adding card to the hand
	  			} else
	  			{
	  				assert(state.handCount[player] == pre.handCount[player] + 1);
	  				assert(state.hand[player][pre.handCount[player]] == supply);
	  			}

					assert(state.supplyCount[supply] == pre.supplyCount[supply] - 1); 
	  			
	  			memcpy(&state, &pre, sizeof(struct gameState));
	  			printf("Passed\n");
	  		}
	  	}

	  // Else we must be sure that gainCard returns -1, and the game state is
	  // not changed
	  } else
	  {
	  	printf("Card not in play\n");
	  	int to_flag;
	  	for (to_flag = 0; to_flag < 3; to_flag++)
	  	{
	  		int player;
	  		for (player = 0; player < num_players; player++)
	  		{
					int ret = gainCard(supply, &state, to_flag, player);
	  			assert(ret == -1);
	  			// Ensure game state has not changed
	  			assert(memcmp(&state, &pre, sizeof(struct gameState)) == 0);
	  			memcpy(&state, &pre, sizeof(struct gameState));
	  		}
	  	}
	  	printf("Passed\n");
	  }
  }

  printf("\nUNIT TEST 2 PASSED.\n\n");

  return 0;
}