// Great Hall

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dominion.h"

#define SUPPLY_COUNT 25
#define TEST_CARD "Great Hall"


int cardtest3() {
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
  int hand_pos;
  int ret;

  int failed = 0;

  // For each player
  for (player = 0; player < num_players; ++player)
  {
    // For each possible hand position
  	for (hand_pos = 0; hand_pos < state.handCount[player]; hand_pos++)
  	{
  		ret = playGreatHall(player, &state, hand_pos);

  		// This is where I introduced a bug into this function.
  		// This bug causes an opponent's card to go into their discard pile
  		// instead of the current player's Great Hall card being discarded.
  		// The card of theirs that goes into their discard pile is decided by
  		// the hand position of the Great Hall card that was played.
  		if (state.handCount[player] != pre.handCount[player])
  		{
  			printf("Player has %d cards in hand, expected %d\n", 
  									state.handCount[player], pre.handCount[player]);
  			failed = 1;
  		}
      // This assert function is where this card function fails.
  		// assert(state.handCount[player] == pre.handCount[player]);
  		assert(state.numActions == pre.numActions + 1);

  		memcpy(&state, &pre, sizeof(struct gameState));
  	}
  }

  if (!failed)
  	printf("\nCARD TEST 3 PASSED.\n\n");
  else
  	printf("\nCARD TEST 3 FAILED.\n\n");


	return 0;
}