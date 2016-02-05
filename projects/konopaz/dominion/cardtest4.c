/* 
 * Unit test for adventurerEffect
 */
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void testingAdventurerEffect() {

  printf("\nStarting tests for adventurerEffect\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);
  gs.whoseTurn = 0;
  gs.numActions = 0;

  int testHand[0];
  memcpy(gs.hand[0], testHand, 0);
  gs.handCount[0] = 0;

  int testDeck[1];
  testDeck[0] = copper;
  memcpy(gs.deck[0], testDeck, sizeof(int) * 1);
  gs.deckCount[0] = 1;

  int testDiscard[0];
  memcpy(gs.discard[0], testDiscard, 0);
  gs.discardCount[0] = 0;
  
  int bonus;
  // the first three and last params aren't used?
  adventurerEffect(0, 0, 0, &gs, 0, &bonus);

  if (testsFailedCount == 0) {
    printf("SUCCESS %d of %d tests passed.\n", testsRunCount, testsRunCount);
  }
  else {
    printf("FAILURE! %d of %d tests passed.\n", 
      testsRunCount - testsFailedCount, 
      testsRunCount);
  }
}

int main() {
  testingAdventurerEffect();
  return 0;
}
