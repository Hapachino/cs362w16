/* 
 * Unit test for villageEffect
 */
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void testVillageEffect() {

  printf("\nStarting tests for villageEffect\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);
  gs.whoseTurn = 0;
  gs.numActions = 0;

  int testHand[1];
  testHand[0] = village;
  memcpy(gs.hand[0], testHand, sizeof(int));
  gs.handCount[0] = 1;

  int testDeck[1];
  testDeck[0] = copper;
  memcpy(gs.deck[0], testDeck, sizeof(int) * 1);
  gs.deckCount[0] = 1;

  int testDiscard[0];
  memcpy(gs.discard[0], testDiscard, 0);
  gs.discardCount[0] = 0;
  
  // the second param doesn't seem to be used ???
  villageEffect(&gs, 0);

  printf("Test numActions incremented appropriately...");
  if (gs.numActions == 2) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 2\n", gs.numActions);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test the copper at the top of the deck was drawn...");
  if (gs.hand[0][0] == copper) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of %d\n", gs.hand[0][0], copper);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test that the hand only has one card in it...");
  if (gs.handCount[0] == 1) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 1\n", gs.handCount[0]);
    testsRunCount++;
    testsFailedCount++;
  }

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
  testVillageEffect();
  return 0;
}
