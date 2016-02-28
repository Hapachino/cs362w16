// Embargo

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dominion.h"

#define SUPPLY_COUNT 25
#define TEST_CARD "Embargo"


int cardtest4() {
	int num_players = 2;
	int random_seed = 1000;
	struct gameState state;
  struct gameState pre;
  struct gameState tmp;
	int max_hand = 5;
	int k[10] = {adventurer, great_hall, embargo, village, minion, mine, cutpurse,
         sea_hag, tribute, smithy};

  int g = initializeGame(num_players, k, random_seed, &state);
  memcpy(&pre, &state, sizeof(struct gameState));
  memcpy(&tmp, &state, sizeof(struct gameState));

  printf("---------------- Testing %s Card ----------------\n", TEST_CARD);

  int player;
  int choice1;
  int hand_pos;
  int ret;

  int failed = 0;

  // For each player
  for (player = 0; player < num_players; ++player)
  {
    // For each possible choice
  	for (choice1 = 0; choice1 < SUPPLY_COUNT; ++choice1)
  	{
      // For each hand position
  		for (hand_pos = 0; hand_pos < state.handCount[player]; ++hand_pos)
  		{
  		//	ret = playEmbargo(player, &state, choice1, hand_pos);

  			if (ret == -1)
  			{
  				assert(state.embargoTokens[choice1] == pre.embargoTokens[choice1]);
  			} else 
  			{
  				assert(state.embargoTokens[choice1] == pre.embargoTokens[choice1] + 1);
  			
  				// This tests the bug that I introduced
          // I purposefully do not use the assert statement so that I can check
          // further game conditions and print the errors that are occurring.
  				if (state.coins != pre.coins + 2)
  				{
  					printf("Player has %d coins, expected %d\n", state.coins, pre.coins + 2);
						failed = 1;
					}
          // This assert is where the card function fails.
  				// assert(state.coins == pre.coins + 2);
  			}

  			memcpy(&state, &pre, sizeof(struct gameState));
  		}
  	}
  }

  if (!failed)
  	printf("\nCARD TEST 4 PASSED.\n\n");
  else
  	printf("\nCARD TEST 4 FAILED.\n\n");

  return 0;

}