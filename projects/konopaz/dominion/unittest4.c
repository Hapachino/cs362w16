#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

int main() {

  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  printf("\nStarting tests for updateCoins\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);

  int testHand1[0];
  memcpy(gs.hand[0], testHand1, 0);
  gs.handCount[0] = 0;

  printf("Testing an empty hand, no bonus...");
  updateCoins(0, &gs, 0);
  if (gs.coins == 0) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 0\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Testing an empty hand, 2 bonus...");
  updateCoins(0, &gs, 2);
  if (gs.coins == 2) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 2\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  // 3 coppers
  int testHand2[3];
  testHand2[0] = copper;
  testHand2[1] = copper;
  testHand2[2] = copper;
  memcpy(gs.hand[0], testHand2, 3 * sizeof(int));
  gs.handCount[0] = 3;

  printf("Test hand 3 coppers, no bonus...");
  updateCoins(0, &gs, 0);
  if (gs.coins == 3) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 3\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test hand 3 coppers, 2 bonus...");
  updateCoins(0, &gs, 2);
  if (gs.coins == 5) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 5\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  // 3 silvers
  testHand2[0] = silver;
  testHand2[1] = silver;
  testHand2[2] = silver;
  memcpy(gs.hand[0], testHand2, 3 * sizeof(int));
  gs.handCount[0] = 3;

  printf("Test hand 3 silver, no bonus...");
  updateCoins(0, &gs, 0);
  if (gs.coins == 6) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 6\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test hand 3 silver, 2 bonus...");
  updateCoins(0, &gs, 2);
  if (gs.coins == 8) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 8\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  // 3 gold
  testHand2[0] = gold;
  testHand2[1] = gold;
  testHand2[2] = gold;
  memcpy(gs.hand[0], testHand2, 3 * sizeof(int));
  gs.handCount[0] = 3;

  printf("Test hand 3 gold, no bonus...");
  updateCoins(0, &gs, 0);
  if (gs.coins == 9) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 9\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test hand 3 gold, 2 bonus...");
  updateCoins(0, &gs, 2);
  if (gs.coins == 11) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 8\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  // 1 copper, 1 silver, 1 gold
  testHand2[0] = copper;
  testHand2[1] = silver;
  testHand2[2] = gold;
  memcpy(gs.hand[0], testHand2, 3 * sizeof(int));
  gs.handCount[0] = 3;

  printf("Test hand 1 copper, 1 silver, 1 gold, no bonus...");
  updateCoins(0, &gs, 0);
  if (gs.coins == 6) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 6\n", gs.coins);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test hand 1 copper, 1 silver, 1 gold, 2 bonus...");
  updateCoins(0, &gs, 2);
  if (gs.coins == 8) {
    printf(" passed\n");
    testsRunCount++;
  }
  else {
    printf(" FAILED!\n");
    printf("   found %d instead of 8\n", gs.coins);
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
