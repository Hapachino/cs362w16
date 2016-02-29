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

  printf("\nStarting tests for gainCard\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);

  printf("Test you can't gain a card that isn't in supply...");
  gs.supplyCount[adventurer] = 0;
  int success = gainCard(adventurer, &gs, 0, 0); //supply pos, gs, toFlag, player
  if (success == -1) {
    printf("passed\n");
    testsRunCount++;
  }
  else {
    printf("failure!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test gain a card to discard...");
  gs.supplyCount[adventurer] = 1;
  int testDiscard1[0];
  memcpy(gs.discard[0], testDiscard1, 0);
  gs.discardCount[0] = 0;

  success = gainCard(adventurer, &gs, 0, 0); //supply pos, gs, toFlag, player
  if (success == 0) {
    printf("passed\n");
    testsRunCount++;

    printf("Did the discard count increase...");
    if (gs.discardCount[0] == 1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Is the card in the discard...");
    if (gs.discard[0][0] == adventurer) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }
  }
  else {
    printf("failure!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test gain a card to deck...");
  gs.supplyCount[adventurer] = 1;
  int testDeck1[0];
  memcpy(gs.deck[0], testDeck1, 0);
  gs.deckCount[0] = 0;

  success = gainCard(adventurer, &gs, 1, 0); //supply pos, gs, toFlag, player
  if (success == 0) {
    printf("passed\n");
    testsRunCount++;

    printf("Did the deck count increase...");
    if (gs.deckCount[0] == 1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Is the card in the deck...");
    if (gs.deck[0][0] == adventurer) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }
  }
  else {
    printf("failure!\n");
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test gain a card to hand...");
  gs.supplyCount[adventurer] = 1;
  int testHand1[0];
  memcpy(gs.hand[0], testHand1, 0);
  gs.handCount[0] = 0;

  success = gainCard(adventurer, &gs, 2, 0); //supply pos, gs, toFlag, player
  if (success == 0) {
    printf("passed\n");
    testsRunCount++;

    printf("Did the hand count increase...");
    if (gs.handCount[0] == 1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Is the card in the hand...");
    if (gs.hand[0][0] == adventurer) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("failure!\n");
      testsRunCount++;
      testsFailedCount++;
    }
  }
  else {
    printf("failure!\n");
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
