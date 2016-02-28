/* 
 * Unit test for fullDeckCount
 */
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void testFullDeckCount() {

  printf("\nStarting tests for fullDeckCount\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, 
    great_hall};

  initializeGame(2, k, 1, &gs);

  int testHand1[0];
  int testDeck1[0];
  int testDiscard1[0];
  memcpy(gs.hand[0], testHand1, 0);
  memcpy(gs.deck[0], testDeck1, 0);
  memcpy(gs.discard[0], testDiscard1, 0);
  gs.handCount[0] = 0;
  gs.deckCount[0] = 0;
  gs.discardCount[0] = 0;

  printf("Testing fullDeckCount for empty deck...");
  int result = fullDeckCount(0, copper, &gs);
  if (result == 0) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 0\n", result);
    testsRunCount++;
    testsFailedCount++;
  }

  int testHand2[5];
  testHand2[0] = copper;
  testHand2[1] = copper;
  testHand2[2] = copper;
  testHand2[3] = copper;
  testHand2[4] = copper;
  memcpy(gs.hand[0], testHand2, 5 * sizeof(int));
  gs.handCount[0] = 5;

  int testDeck2[7];
  testDeck2[0] = copper;
  testDeck2[1] = copper;
  testDeck2[2] = copper;
  testDeck2[3] = copper;
  testDeck2[4] = copper;
  testDeck2[5] = copper;
  testDeck2[6] = copper;
  memcpy(gs.deck[0], testDeck2, 7 * sizeof(int));
  gs.deckCount[0] = 7;

  int testDiscard2[3];
  testDiscard2[0] = copper;
  testDiscard2[1] = copper;
  testDiscard2[2] = copper;
  memcpy(gs.discard[0], testDiscard2, 3 * sizeof(int));
  gs.discardCount[0] = 3;

  printf("Testing fullDeckCount for silvers in coppers only deck...");
  result = fullDeckCount(0, silver, &gs);
  if (result == 0) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 0\n", result);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing fullDeckCount for coppers in coppers only deck...");
  result = fullDeckCount(0, copper, &gs);
  if (result == 15) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 15\n", result);
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
  testFullDeckCount();
  return 0;
}
