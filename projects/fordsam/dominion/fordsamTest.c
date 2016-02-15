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

/* This function searches the provided array for the card, returning the index
   of the card if it's found */
int handIndex(int card, int *array, int arrayCount) {
  int i = 0;

  /* Search the target array for the provided card */
  for (i = 0; i < arrayCount; i++) {
    if (array[i] == card) {
      /* Return index if the card was found */
      return i;
    }
  }

  return -1;   /* Return -1 (not found) by default */
}

/* This function simply determines whether the passed card is a treasure card
   (copper, silver, or gold) */
int isTreasureCard(int card) {
  if (card == copper || card == silver || card == gold) {
    /* Return 1 (is a treasure card) if the card is a treasure card */
    return 1;
  }

  return 0;   /* Return 0 (not a treasure card) by default */
}

/* Goes through the player's hand to determine the number of treasure cards */
int treasureCardsInHand(int player, struct gameState *state) {
  int i = 0;
  int count = 0;

  for (i = 0; i < state->handCount[player]; i++) {
    if (isTreasureCard(state->hand[player][i])) {
      /* Increment the count when we find a treasure card */
      count += 1;
    }
  }

  return count;
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

/* This function prints the contents of an array of integers, for debugging
   purposes */
void printIntArray(int array[], int arrayCount) {
  int i = 0;

  /* Iterate through the array and print each of the integers */
  for (i = 0; i < arrayCount; i++) {
    if (i + 1 < arrayCount) {
      printf("%d ", array[i]);
    } else {
      printf("%d\n", array[i]);
    }
  }
}

void enumToCardName(int card, char *name, int nameLength) {
  /* Clear out any existing contents of the provided name string */
  bzero(name, nameLength);

  /* Copy the name of the provided card into the name string */
  switch (card) {
    case curse:
      sprintf(name, "curse");
      break;
    case estate:
      sprintf(name, "estate");
      break;
    case duchy:
      sprintf(name, "duchy");
      break;
    case province:
      sprintf(name, "province");
      break;
    case copper:
      sprintf(name, "copper");
      break;
    case silver:
      sprintf(name, "silver");
      break;
    case gold:
      sprintf(name, "gold");
      break;
    case adventurer:
      sprintf(name, "adventurer");
      break;
    case council_room:
      sprintf(name, "council_room");
      break;
    case feast:
      sprintf(name, "feast");
      break;
    case gardens:
      sprintf(name, "gardens");
      break;
    case mine:
      sprintf(name, "mine");
      break;
    case remodel:
      sprintf(name, "remodel");
      break;
    case smithy:
      sprintf(name, "smithy");
      break;
    case village:
      sprintf(name, "village");
      break;
    case baron:
      sprintf(name, "baron");
      break;
    case great_hall:
      sprintf(name, "great_hall");
      break;
    case minion:
      sprintf(name, "minion");
      break;
    case steward:
      sprintf(name, "steward");
      break;
    case tribute:
      sprintf(name, "tribute");
      break;
    case ambassador:
      sprintf(name, "ambassador");
      break;
    case cutpurse:
      sprintf(name, "cutpurse");
      break;
    case embargo:
      sprintf(name, "embargo");
      break;
    case outpost:
      sprintf(name, "outpost");
      break;
    case salvager:
      sprintf(name, "salvager");
      break;
    case sea_hag:
      sprintf(name, "sea_hag");
      break;
    case treasure_map:
      sprintf(name, "treasure_map");
      break;
    default:
      sprintf(name, "UNKNOWN_CARD (%d)", card);
  }
}

/* Print the members of a gameState struct in a readable manner, for
   debugging */
void printGameState(struct gameState *state) {
  int i = 0, j = 0;
  char cardName[CARD_NAME_LENGTH];

  printf("numPlayers: %d\n", state->numPlayers);

  for (i = 0; i < treasure_map+1; i++) {
    enumToCardName(i, cardName, CARD_NAME_LENGTH);
    printf("supplyCount[%s]: %d\n", cardName, state->supplyCount[i]);
  }

  for (i = 0; i < treasure_map+1; i++) {
    enumToCardName(i, cardName, CARD_NAME_LENGTH);
    printf("embargoTokens[%s]: %d\n", cardName, state->embargoTokens[i]);
  }

  printf("outpostPlayed: %d\n", state->outpostPlayed);
  printf("outpostTurn: %d\n", state->outpostTurn);
  printf("whoseTurn: %d\n", state->whoseTurn);
  printf("phase: %d\n", state->phase);
  printf("numActions: %d\n", state->numActions);
  printf("coins: %d\n", state->coins);
  printf("numBuys: %d\n", state->numBuys);

  for (i = 0; i < state->numPlayers; i++) {
    for (j = 0; j < state->handCount[i]; j++) {
      enumToCardName(state->hand[i][j], cardName, CARD_NAME_LENGTH);
      printf("hand[%d][%d]: %s\n", i, j, cardName);
    }

    printf("handCount[%d]: %d\n", i, state->handCount[i]);
  }

  for (i = 0; i < state->numPlayers; i++) {
    for (j = 0; j < state->deckCount[i]; j++) {
      enumToCardName(state->deck[i][j], cardName, CARD_NAME_LENGTH);
      printf("deck[%d][%d]: %s\n", i, j, cardName);
    }

    printf("deckCount[%d]: %d\n", i, state->deckCount[i]);
  }

  for (i = 0; i < state->numPlayers; i++) {
    for (j = 0; j < state->discardCount[i]; j++) {
      enumToCardName(state->discard[i][j], cardName, CARD_NAME_LENGTH);
      printf("discard[%d][%d]: %s\n", i, j, cardName);
    }

    printf("discardCount[%d]: %d\n", i, state->discardCount[i]);
  }

  for (i = 0; i < state->playedCardCount; i++) {
    enumToCardName(state->playedCards[i], cardName, CARD_NAME_LENGTH);
    printf("playedCards[%d]: %s\n", i, cardName);
  }

  printf("playedCardCount: %d\n", state->playedCardCount);
}
