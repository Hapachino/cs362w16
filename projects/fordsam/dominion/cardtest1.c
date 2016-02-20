/* Test the playAdventurer() function
   NOTE: playAdventurer() should:
     * Draw cards from the player's deck until two treasure cards are drawn.
     * Discard all drawn cards that are not treasure cards.
     * Move the played card to the playedCards pile.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "dominion.h"
#include "fordsamTest.h"

#define P1 0
#define P2 1

int testPlayAdventurer() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  int stored_results[10] = {0};
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};
  pid_t pid = -1;
  int status = 0;

  /* Test with no available treasure cards */
  state.hand[P1][0] = adventurer;
  state.handCount[P1] = 1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = baron;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = smithy;
  state.deckCount[P1] = 5;
  state.discard[P1][0] = estate;
  state.discard[P1][1] = baron;
  state.discard[P1][2] = mine;
  state.discard[P1][3] = gardens;
  state.discard[P1][4] = smithy;
  state.discardCount[P1] = 5;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));

  /* Run the test in a child process since it can get into a bad state */
  pid = fork();
  if (pid < 0) {
    perror("Error forking");
  } else if (pid == 0) {
    /* Execute the test in the child process */
    result = playAdventurer(&state);

    exit(result);
  } else if (pid > 0) {
    /* Wait for the child process to finish */
    wait(&status);

    /* Check if the child process exited cleanly or crashed and store the
       result so we can print it later */
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
      stored_results[0] = 1;
    } else {
      stored_results[0] = 0;
    }
  }

  /* NOTE: Tests after this point don't need to be forked into child processes
     since they won't lead to the same sort of bad states.

     Output should start here because the forking can lead to weird
     repeated output when we redirect the output to file. */
  printf("----- Testing Adventurer card -----\n");

  /* Print the results for the first test */
  printf("----- Test: deckCount = 5, discardCount = 5, no treasure cards\n");
  testCount += 1;
  passCount += fakeAssert(
    "Should not crash when there are no available treasure cards",
    (stored_results[0])
  );

  if (stored_results[0] == 1) {
    /* Properly test the lack of treasure cards if it didn't cause a crash
       NOTE: This current setup relies on the pre-existing setup above */
    memcpy(&state, &preState, sizeof(struct gameState));
    result = playAdventurer(&state);
    compareState(&state, &preState, &gsc);

    /* Should not change the player's hand */
    testCount += 1;
    passCount += fakeAssert(
      "With no treasure cards, player's hand should not be changed",
      ((gsc.handChanged[P1] == 0) && (gsc.handCount[P1] == 0))
    );

    /* Should not affect other players */
    testCount += 1;
    passCount += fakeAssert(
      "Should not affect other players",
      (gsc.handChanged[P2] == 0
      && gsc.deckChanged[P2] == 0
      && gsc.discardChanged[P2] == 0
      && state.handCount[P2] == preState.handCount[P2]
      && state.deckCount[P2] == preState.deckCount[P2]
      && state.discardCount[P2] == preState.discardCount[P2])
    );

    /* Should move played card to playedCards */
    testCount += 1;
    passCount += fakeAssert(
      "Should move played card to playedCards",
      (!containsCard(adventurer, state.hand[P1], state.handCount[P1])
      && containsCard(adventurer, state.playedCards, state.playedCardCount))
    );
  } else {
    printf(
      "NOTE: Some tests have been skipped because of this failure\n"
    );
  }

  /* Test with only one treasure card */
  printf("\n----- Test: deckCount = 5, deck has copper, discardCount = 5\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.hand[P1][0] = adventurer;
  state.handCount[P1] = 1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = copper;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = smithy;
  state.deckCount[P1] = 5;
  state.discard[P1][0] = estate;
  state.discard[P1][1] = baron;
  state.discard[P1][2] = mine;
  state.discard[P1][3] = gardens;
  state.discard[P1][4] = smithy;
  state.discardCount[P1] = 5;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playAdventurer(&state);
  compareState(&state, &preState, &gsc);

  /* For 1 treasure card, hand should only get 1 additional card
     NOTE: We subtract one because the played card should be discarded */
  testCount += 1;
  passCount += fakeAssert(
    "For 1 treasure card, player's hand should only get the 1 treasure card",
    (state.handCount[P1] == preState.handCount[P1] + 1 - 1
    && containsCard(copper, state.hand[P1], state.handCount[P1]))
  );

  /* Should discard all other drawn cards */
  testCount += 1;
  passCount += fakeAssert(
    "Should discard all other drawn cards",
    (state.discardCount[P1] == preState.discardCount[P1] + 4)
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(adventurer, state.hand[P1], state.handCount[P1])
    && containsCard(adventurer, state.playedCards, state.playedCardCount))
  );

  /* Test with an empty deck and a populated discard pile */
  printf("\n----- Test: deckCount = 0, discardCount = 5, discard has copper");
  printf(" + silver\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.hand[P1][0] = adventurer;
  state.handCount[P1] = 1;
  state.discard[P1][0] = estate;
  state.discard[P1][1] = copper;
  state.discard[P1][2] = mine;
  state.discard[P1][3] = gardens;
  state.discard[P1][4] = silver;
  state.discardCount[P1] = 5;
  state.deckCount[P1] = 0;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playAdventurer(&state);
  compareState(&state, &preState, &gsc);

  /* Should draw treasure cards from deck into hand
     NOTE: We subtract one because the played card should be discarded */
  testCount += 1;
  passCount += fakeAssert(
    "Should add discard to deck and shuffle, so 2 treasure cards are drawn",
    (state.handCount[P1] == preState.handCount[P1] + 2 - 1
    && containsCard(copper, state.hand[P1], state.handCount[P1])
    && containsCard(silver, state.hand[P1], state.handCount[P1]))
  );

  /* Print note about deck and discard testing */
  printf(
    "NOTE: We can't reliably test deck or discard because shuffle is random\n"
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(adventurer, state.hand[P1], state.handCount[P1])
    && containsCard(adventurer, state.playedCards, state.playedCardCount))
  );

  /* Test with two treasure cards */
  printf(
    "\n----- Test: deckCount = 5, deck has copper + silver\n"
  );
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.hand[P1][0] = adventurer;
  state.handCount[P1] = 1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = copper;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = silver;
  state.deckCount[P1] = 5;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playAdventurer(&state);
  compareState(&state, &preState, &gsc);

  /* Should draw treasure cards from deck into hand
     NOTE: We subtract one because the played card should be discarded */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw 2 treasure cards (of 2) from player's deck into hand",
    (state.handCount[P1] == preState.handCount[P1] + 2 - 1
    && containsCard(copper, state.hand[P1], state.handCount[P1])
    && containsCard(silver, state.hand[P1], state.handCount[P1]))
  );

  /* Should stop drawing cards when two treasure cards have been drawn */
  testCount += 1;
  passCount += fakeAssert(
    "Should stop drawing cards when 2 treasure cards have been drawn",
    (state.deckCount[P1] == preState.deckCount[P1] - 4)
  );

  /* Should discard all other drawn cards */
  testCount += 1;
  passCount += fakeAssert(
    "Should discard all other drawn cards",
    (state.discardCount[P1] == preState.discardCount[P1] + 2)
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(adventurer, state.hand[P1], state.handCount[P1])
    && containsCard(adventurer, state.playedCards, state.playedCardCount))
  );

  /* Test with three treasure cards */
  printf("\n----- Test: deckCount = 8, deck has copper, silver, and");
  printf(" gold, discardCount = 5\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.hand[P1][0] = adventurer;
  state.handCount[P1] = 1;
  state.deck[P1][0] = estate;
  state.deck[P1][1] = copper;
  state.deck[P1][2] = mine;
  state.deck[P1][3] = gardens;
  state.deck[P1][4] = silver;
  state.deck[P1][5] = baron;
  state.deck[P1][6] = gold;
  state.deck[P1][7] = cutpurse;
  state.deckCount[P1] = 8;
  state.deck[P2][0] = silver;
  state.deck[P2][1] = smithy;
  state.deckCount[P2] = 2;
  state.hand[P2][2] = gardens;
  state.hand[P2][3] = council_room;
  state.handCount[P2] = 2;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = playAdventurer(&state);
  compareState(&state, &preState, &gsc);

  /* Should draw treasure cards from deck into hand
     NOTE: We subtract one because the played card should be discarded */
  testCount += 1;
  passCount += fakeAssert(
    "Should draw 2 treasure cards (of 3) from player's deck into hand",
    (state.handCount[P1] == preState.handCount[P1] + 2 - 1
    && containsCard(silver, state.hand[P1], state.handCount[P1])
    && containsCard(gold, state.hand[P1], state.handCount[P1]))
  );

  /* Should stop drawing cards when two treasure cards have been drawn */
  testCount += 1;
  passCount += fakeAssert(
    "Should stop drawing cards when 2 treasure cards have been drawn",
    (state.deckCount[P1] == preState.deckCount[P1] - 4)
  );

  /* Should discard all other drawn cards */
  testCount += 1;
  passCount += fakeAssert(
    "Should discard all other drawn cards",
    (state.discardCount[P1] == preState.discardCount[P1] + 2)
  );

  /* Should not affect other players */
  testCount += 1;
  passCount += fakeAssert(
    "Should not affect other players",
    (gsc.handChanged[P2] == 0
    && gsc.deckChanged[P2] == 0
    && gsc.discardChanged[P2] == 0
    && state.handCount[P2] == preState.handCount[P2]
    && state.deckCount[P2] == preState.deckCount[P2]
    && state.discardCount[P2] == preState.discardCount[P2])
  );

  /* Should move played card to playedCards */
  testCount += 1;
  passCount += fakeAssert(
    "Should move played card to playedCards",
    (!containsCard(adventurer, state.hand[P1], state.handCount[P1])
    && containsCard(adventurer, state.playedCards, state.playedCardCount))
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);

  return 0;
}

int main() {
  testPlayAdventurer();
  return 0;
}
