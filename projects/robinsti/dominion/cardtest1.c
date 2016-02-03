// Smithy

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dominion.h"

#define TEST_CARD "Smithy"

int cardtest1() {
	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
	int max_hand = 5;
	int k[10] = {adventurer, great_hall, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));

  printf("---------------- Testing %s Card ----------------\n", TEST_CARD);

  int player;
  int hand_pos;
  int failed = 0;

  // For each player
  for (player = 0; player < num_players; player++)
  {
    // For each hand position
  	for (hand_pos = 0; hand_pos < state.handCount[player]; hand_pos++)
  	{

  		playSmithy(player, &state, hand_pos);

  		// This is where my bug was introduced
      // I purposefully do not use the assert statement so that I can check
      // further game conditions and print the errors that are occurring.
  		if (!(state.handCount[player] == pre.handCount[player] + 3))
  		{
  			printf("Added %d cards to their hand, expected %d\n", state.handCount[player] - pre.handCount[player], 3);
        printf("Removed %d cards from their deck, expected %d\n", pre.deckCount[player] - state.deckCount[player], 3);
        failed = 1;
  		}
      // These assert statements are where this card function fails.
  		// assert(state.handCount[player] == pre.handCount[player] + 3);
      // assert(state.deckCount[player] == pre.deckCount[player] - 3);
  		
      memcpy(&state, &pre, sizeof(struct gameState));
  	}
  }

  if (!failed)
  	printf("\nCARD TEST 1 PASSED.\n\n");
  else
  	printf("\nCARD TEST 1 FAILED.\n\n");

	return 0;
}