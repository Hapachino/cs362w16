#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

  printf("\nStarting tests for buyCard\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);

  printf("Testing buying when numbuys < 1...");
  gs.numBuys = 0;
  int success = buyCard(0, &gs);
  if (success == -1) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failed!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing when supply is out of card type...");
  gs.numBuys = 1;
  gs.supplyCount[smithy] = 0;
  success = buyCard(smithy, &gs);
  if (success == -1) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failed!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing when not enough money...");
  gs.numBuys = 1;
  gs.supplyCount[smithy] = 1;
  gs.coins = 0;
  success = buyCard(smithy, &gs);
  if (success == -1) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failed!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing successful purchase...");
  gs.numBuys = 1;
  gs.supplyCount[smithy] = 1;
  gs.coins = 4;
  gs.whoseTurn = 0;
  int testDiscard1[0];
  memcpy(gs.discard[0], testDiscard1, 0);
  gs.discardCount[0] = 0;

  success = buyCard(smithy, &gs);
  if (success == 0) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failed!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing card is in discard after buyCard...");
  if (gs.discard[0][0] == smithy) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failed!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  if (testsFailedCount == 0) {
    printf("SUCCESS %d of %d tests passed.\n", testsRunCount, testsRunCount);
    return 0;
  }
  else {
    printf("FAILURE! %d of %d tests passed.\n", 
      testsRunCount - testsFailedCount, 
      testsRunCount);

    return 1;
  }
}
