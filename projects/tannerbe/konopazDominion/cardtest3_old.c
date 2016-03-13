/* 
 * Unit test for smithyEffect
 */
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int handContainsCard(struct gameState *gs, int player, int card) {

  int i;

  /*
  printf("checking hand [");
  for (i = 0; i < gs->handCount[player]; i++) {
    if (i > 0) printf (", ");
    printf("%d", gs->hand[player][i]);
  }
  printf("] for %d\n", card);
  */

  int position = -1;

  for (i = 0; i < gs->handCount[player]; i++) {
    if (gs->hand[player][i] == card) {
      position = i;
    }
  }

  return position;
}

void testSmithyEffect() {

  printf("\nStarting tests for smithyEffect\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);

  //give me a hand with a smithy in it
  int testHand[1];
  testHand[0] = smithy;
  memcpy(gs.hand[0], testHand, sizeof(int));
  gs.handCount[0] = 1;

  //give me a deck of a smithy, adventurer, village and copper
  int testDeck[4];
  testDeck[0] = adventurer;
  testDeck[1] = village;
  testDeck[2] = copper;
  memcpy(gs.deck[0], testDeck, sizeof(int) * 4);
  gs.deckCount[0] = 4;

  //play the smithy
  smithyEffect(&gs, 0);

  printf("Test that the smithy was dicarded...");
  int smithyPos = handContainsCard(&gs, 0, smithy);
  if (smithyPos == -1) {
    printf("passed.\n");
    testsRunCount++;
  }
  else {
    printf("FAILED\n");
    printf("  found smithy at %d\n", smithyPos);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test the 3 cards were drawn as expected...");
  if (gs.handCount[0] == 3) {
    printf("passed\n");
    testsRunCount++;

    printf("Test the hand contains an adventurer...");
    if (handContainsCard(&gs, 0, adventurer) != -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Test the hand contains an village...");
    if (handContainsCard(&gs, 0, village) != -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Test the hand contains an copper...");
    if (handContainsCard(&gs, 0, copper) != -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      testsRunCount++;
      testsFailedCount++;
    }
  }
  else {
    printf("FAILED\n");
    printf("  found %d cards in stead of 4\n", gs.handCount[0]);
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
  testSmithyEffect();
  return 0;
}
