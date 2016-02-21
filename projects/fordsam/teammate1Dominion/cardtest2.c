/* Test the Council Room card
   NOTE: Council Room should:
     * Draw four cards from the player's deck and add them to their hand.
     * Add 1 buy.
     * For each other player, draw a card from their deck and add it to their
       hand.
     * Move the played card to the playedCard pile.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1
#define P3 2
#define HANDPOS 1

int testCouncilRoom() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState state = {0};
  struct gameState preState = {0};

  printf("----- Testing Council Room card -----\n");

  /* Set up state for three players */
  printf(
    "\n----- Test: 3 players, P1 deckCount = 5, P2 & P3 deckCount = 2\n"
  );
  state.whoseTurn = P1;
  state.numPlayers = 3;
  state.numBuys = 1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = silver;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = copper;
  state.deckCount[P1] = 5;
  state.discardCount[P1] = 0;
  state.hand[P1][0] = baron;
  state.hand[P1][1] = council_room;
  state.handCount[P1] = 2;
  state.deck[P2][0] = treasure_map;
  state.deck[P2][1] = salvager;
  state.deckCount[P2] = 2;
  state.deck[P3][0] = sea_hag;
  state.deck[P3][1] = cutpurse;
  state.deckCount[P3] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = councilRoomEffect(HANDPOS, P1, &state);

  /* Should draw 4 cards to player's hand
     NOTE: We subtract one because the Council Room card is discarded */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw 4 cards to player's hand",
    (state.handCount[P1] == preState.handCount[P1] + 4 - 1)
  );

  /* Should draw the 4 cards from the player's deck */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw the 4 cards from the player's deck",
    (containsCard(copper, state.hand[P1], state.handCount[P1])
    && containsCard(gardens, state.hand[P1], state.handCount[P1])
    && containsCard(mine, state.hand[P1], state.handCount[P1])
    && containsCard(silver, state.hand[P1], state.handCount[P1]))
  );

  /* Should provide +1 buy to player */
  testCount += 1;
  passCount += fakeAssert(
    "Should provide +1 buy",
    (state.numBuys == preState.numBuys + 1)
  );

  /* Should cause other players to draw 1 card */
  testCount += 1;
  passCount += fakeAssert(
    "Should cause all other players to draw 1 card",
    (state.handCount[P2] == preState.handCount[P2] + 1
    && state.handCount[P3] == preState.handCount[P3] + 1)
  );

  /* Should draw other players' cards from their decks */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw other players' cards from their own decks",
    (containsCard(salvager, state.hand[P2], state.handCount[P2])
    && containsCard(cutpurse, state.hand[P3], state.handCount[P3]))
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(council_room, state.hand[P1], state.handCount[P1])
    && containsCard(council_room, state.playedCards, state.playedCardCount))
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);

  return 0;
}

int main() {
  testCouncilRoom();
  return 0;
}
