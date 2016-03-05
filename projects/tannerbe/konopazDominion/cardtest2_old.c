/* 
 * Unit test for councilRoomEffect
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

void testCouncilRoomEffect() {
  int i;

  printf("\nStarting tests for councilRoomEffect\n");
  printf("---------------------------------\n");

  int testsRunCount = 0;
  int testsFailedCount = 0;

  struct gameState gs;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  initializeGame(2, k, 1, &gs);

  //give me a hand with only the council room
  int testHand[1];
  testHand[0] = council_room;
  memcpy(gs.hand[0], testHand, sizeof(int));
  gs.handCount[0] = 1;

  //give me a deck of a smithy, adventurer, village and copper
  int testDeck[4];
  testDeck[0] = smithy;
  testDeck[1] = adventurer;
  testDeck[2] = village;
  testDeck[3] = copper;
  memcpy(gs.deck[0], testDeck, sizeof(int) * 4);
  gs.deckCount[0] = 4;

  //play the council room
  councilRoomEffect(&gs, 0);

  printf("Test that the council room was dicarded...");
  int councilRoomPos = -1;
  for (i = 0; i < gs.handCount[0]; i++) {
    if (gs.hand[0][i] == council_room) {
      councilRoomPos = i;
    }
  }

  if (councilRoomPos == -1) {
    printf("passed.\n");
    testsRunCount++;
  }
  else {
    printf("FAILED\n");
    printf("  found council room at %d\n", councilRoomPos);
    testsRunCount++;
    testsFailedCount++;
  }

  printf("Test the 4 cards were drawn as expected...");
  if (gs.handCount[0] == 4) {
    printf("passed\n");
    testsRunCount++;

    printf("Test that the hand now has a smithy...");
    if (handContainsCard(&gs, 0, smithy) > -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      printf("  didn't find a smithy.");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Test that the hand now has a village...");
    if (handContainsCard(&gs, 0, village) > -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      printf("  didn't find a village.");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Test that the hand now has a copper...");
    if (handContainsCard(&gs, 0, copper) > -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      printf("  didn't find a copper.");
      testsRunCount++;
      testsFailedCount++;
    }

    printf("Test that the hand now has a adventurer...");
    if (handContainsCard(&gs, 0, adventurer) > -1) {
      printf("passed\n");
      testsRunCount++;
    }
    else {
      printf("FAILED\n");
      printf("  didn't find a adventurer.");
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
  testCouncilRoomEffect();
  return 0;
}
