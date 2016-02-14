// Adventurer

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dominion.h"

#define SUPPLY_COUNT 25
#define TEST_CARD "Adventurer"

int cardtest2() {
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

  int player = 0;
  int drawntreasure = 0;
  int temphand[MAX_HAND];
  int cardDrawn;
  int i;
  int j;
  int ret;

  int state_total;
  int pre_total;
  int failed = 0;

  // For each player
  for (player = 0; player < num_players; player++)
  {
    // We must do brute force iteration and add more cards to the player's deck
    // in order to achieve a more thorough test.
  	for (i = 0; i < 10; i++)
  	{ 
  		playAdventurer(player, &state, drawntreasure, temphand, cardDrawn); 
  		assert(state.handCount[player] == pre.handCount[player] + 2);

  		state_total = state.deckCount[player];
  		state_total += state.handCount[player];
  		state_total += state.discardCount[player];
  		
  		pre_total = pre.deckCount[player];
  		pre_total += pre.handCount[player];
  		pre_total += pre.discardCount[player];

  		// This is where I introduced a bug into this program.
  		// We must count all of the cards in the deck, hand, and discard
  		// pile in order to find it.
      // I purposefully do not use the assert statement so that I can check
      // further game conditions and print the errors that are occurring.
  		if (state_total < pre_total)
  		{
  			printf("Player has %d cards in total, expected %d\n", state_total, pre_total);
  			failed = 1;
  		}
      // This assert function is where this card function fails.
  		// assert(state_total == pre_total);

  		// Try to buy gold and then try to buy silver in order to diversify the
      // test deck for the cards drawn by the adventurer.
  		ret = gainCard(7, &tmp, 1, player);
  		ret = gainCard(6, &tmp, 1, player);
  		memcpy(&state, &tmp, sizeof(struct gameState));
  		memcpy(&pre, &tmp, sizeof(struct gameState)); 

  	}
  }

  if (failed == 0) 
  {
  	printf("\nCARD TEST 2 PASSED.\n\n");
  } else
  {
  	printf("\nCARD TEST 2 FAILED.\n\n");
  }

  return 0;

}