/* I found that I was writing some of the same code over and over while
   creating tests, so I stripped some of it out into reusable functions */
#include <stdio.h>
#include <string.h>
#include "fordsamTest.h"

/* This function attempts to vaguely simulate assert() behavior without halting
   the test suite.  The function returns 1 if the test result is truthy,
   otherwise it returns 0.  As a result, the return value can be added to the
   count of passing tests. */
int fakeAssert(char condition[], int result) {
  /* Print the condition explanation with a PASS/FAIL prefix, depending on the
     truthiness of the test result */
  if (result) {
    printf("PASS: %s\n", condition);
    return 1;
  } else {
    printf("FAIL: %s\n", condition);
    return 0;
  }
}

/* This function simply prints out the number of passed tests out of the total
   number of tests in a standardized fashion */
void printTestResults(int passCount, int testCount) {
  /* Print the number of passing tests out of the total number of tests */
  printf(
    "\n%d out of %d test%s passed\n",
    passCount,
    testCount,
    (testCount > 1 ? "s" : "")
  );
}

/* This function searches the provided array for the card, returning 1 if found
   or 0 if not found */
int containsCard(int card, int array[], int arrayCount) {
  int i = 0;

  /* Search the target array for the provided card */
  for (i = 0; i < arrayCount; i++) {
    if (array[i] == card) {
      /* Return 1 (found) if the card exists in the location */
      return 1;
    }
  }

  return 0;   /* Return 0 (not found) by default */
}

/* This function compares two game states, stores the results of the
   comparisons in the passed gameStateComparison struct, and also returns
   an int indicating whether all the comparisons were equal (0 for equal, and
   1 for not equal).
   NOTE: If the gameState struct ever changes, this would need to be updated */
int compareState(
  struct gameState *a,
  struct gameState *b,
  struct gameStateComparison *gsc
) {
  int i = 0, j = 0;
  int changed = 0;

  /* Compare all the gameState members and assign the result to the matching
     gameStateComparison member */
  gsc->numPlayers = (a->numPlayers == b->numPlayers) ? 0 : 1;

  for (i = 0; i < treasure_map+1; i++) {
    gsc->supplyCount[i] = (a->supplyCount[i] == b->supplyCount[i]) ? 0 : 1;

    changed = changed || gsc->supplyCount[i];
  }

  for (i = 0; i < treasure_map+1; i++) {
    gsc->embargoTokens[i] =
      (a->embargoTokens[i] == b->embargoTokens[i]) ? 0 : 1;

    changed = changed || gsc->embargoTokens[i];
  }

  gsc->outpostPlayed = (a->outpostPlayed == b->outpostPlayed) ? 0 : 1;
  gsc->outpostTurn = (a->outpostTurn == b->outpostTurn) ? 0 : 1;
  gsc->whoseTurn = (a->whoseTurn == b->whoseTurn) ? 0 : 1;
  gsc->phase = (a->phase == b->phase) ? 0 : 1;
  gsc->numActions = (a->numActions == b->numActions) ? 0 : 1;
  gsc->coins = (a->coins == b->coins) ? 0 : 1;
  gsc->numBuys = (a->numBuys == b->numBuys) ? 0 : 1;

  for (i = 0; i < MAX_PLAYERS; i++) {
    for (j = 0; j < MAX_HAND; j++) {
      if (a->hand[i][j] == b->hand[i][j]) {
        gsc->hand[i][j] = 0;
      } else {
        gsc->hand[i][j] = 1;
        gsc->handChanged[i] = 1;
      }

      changed = changed || gsc->hand[i][j];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    for (j = 0; j < MAX_DECK; j++) {
      if (a->deck[i][j] == b->deck[i][j]) {
        gsc->deck[i][j] = 0;
      } else {
        gsc->deck[i][j] = 1;
        gsc->deckChanged[i] = 1;
      }

      if (a->discard[i][j] == b->discard[i][j]) {
        gsc->discard[i][j] = 0;
      } else {
        gsc->discard[i][j] = 1;
        gsc->discardChanged[i] = 1;
      }

      changed = changed || gsc->deck[i][j] || gsc->deckChanged[i]
        || gsc->discard[i][j] || gsc->discardChanged[i];
    }
  }

  for (i = 0; i < MAX_PLAYERS; i++) {
    gsc->handCount[i] = (a->handCount[i] == b->handCount[i]) ? 0 : 1;
    gsc->deckCount[i] = (a->deckCount[i] == b->deckCount[i]) ? 0 : 1;
    gsc->discardCount[i] = (a->discardCount[i] == b->discardCount[i]) ? 0 : 1;

    changed = changed || gsc->handCount[i] || gsc->deckCount[i]
      || gsc->discardCount[i];
  }

  for (i = 0; i < MAX_DECK; i++) {
    gsc->playedCards[i] = (a->playedCards[i] == b->playedCards[i]) ? 0 : 1;

    changed = changed || gsc->playedCards[i];
  }

  gsc->playedCardCount = (a->playedCardCount == b->playedCardCount) ? 0 : 1;

  /* Do one change calculation for all the non-looping members */
  changed = changed || gsc->numPlayers || gsc->outpostPlayed
    || gsc->outpostTurn || gsc->whoseTurn || gsc->phase || gsc->numActions
    || gsc->coins || gsc->numBuys || gsc->playedCardCount;

  /* Return the overall status of whether anything changed */
  return changed;
}

/* This function is prints the contents of an array of integers, for debugging
   purposes */
int printIntArray(int array[], int arrayCount) {
  int i = 0;

  /* Iterate through the array and print each of the integers */
  for (i = 0; i < arrayCount; i++) {
    if (i + 1 < arrayCount) {
      printf("%d ", array[i]);
    } else {
      printf("%d\n", array[i]);
    }
  }

  return 0;   /* Return 0 (not found) by default */
}
