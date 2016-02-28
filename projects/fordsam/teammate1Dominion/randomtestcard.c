/* Random tester for Steward (as part of cardEffect())
   NOTE: Steward should allow player to choose one of:
     * +2 cards
     * +2 gold
     * Trash 2 cards from hand (or fewer if 2 cards aren't available)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "fordsamTest.h"

#define CARD steward
#define TEST_ITERATIONS 10
#define OUTPUT_MAX 200

/* TODO: Tweak probabilities so that we make sure to test problematic cases? */

/* Generates a random game state that's catered to this context (avoiding the
   randomization of parts of the game state which have no impact on this
   particular function's behavior) */
void generateGameState(struct gameState *state) {
  int i = 0, j = 0;
  int generatedCard = 0;

  /* Set the gameState to all zeros to clear any previous state */
  bzero(state, sizeof(struct gameState));

  /* Number of players - between 2 and MAX_PLAYERS */
  state->numPlayers = rand() % (MAX_PLAYERS - 1) + 2;

  /* whoseTurn is randomly chosen from existing players */
  state->whoseTurn = rand() % state->numPlayers;

  /* Initialize the hand, deck, and discard of every player */
  for (i = 0; i < state->numPlayers; i++) {
    /* Populate the hand with 0-12 cards */
    state->handCount[i] = rand() % 13;
    for (j = 0; j < state->handCount[i]; j++) {
      /* Use a more complex hand-generation scheme for the current player */
      if (i == state->whoseTurn) {
        /* Generate a unique, random card (always avoiding CARD) */
        do {
          generatedCard = rand() % (treasure_map + 1);
        } while (
          generatedCard == CARD
          || containsCard(generatedCard, state->hand[i], state->handCount[i])
        );
        state->hand[i][j] = generatedCard;
      } else {
        /* Simply generate a random hand for other players */
        state->hand[i][j] = rand() % (treasure_map + 1);
      }
    }

    /* Replace one of the cards in the current player's hand with CARD to make
    sure they have it */
    if (i == state->whoseTurn) {
      if (state->handCount[i] == 0) {
        /* Set the handCount to 1 if they had 0 cards */
        state->handCount[i] = 1;
      }
      state->hand[i][(rand() % state->handCount[i])] = CARD;
    }

    /* Populate the deck with 0-17 cards */
    state->deckCount[i] = rand() % 18;
    for (j = 0; j < state->deckCount[i]; j++) {
      state->deck[i][j] = rand() % (treasure_map + 1);
    }

    /* Populate the discard pile with 0-17 cards */
    state->discardCount[i] = rand() % 18;
    for (j = 0; j < state->discardCount[i]; j++) {
      state->discard[i][j] = rand() % (treasure_map + 1);
    }
  }

  /* Randomly populate the playedCards array, but avoid the current card so we
     can easily test for its inclusion */
  state->playedCardCount = rand() % 5;
  for (i = 0; i < state->playedCardCount; i++) {
    do {
      state->playedCards[i] = rand() % (treasure_map + 1);
    } while (state->playedCards[i] == CARD);
  }
}

int randomlyTest() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};
  int i = 0, j = 0;
  int p = 0;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int handPos = 0;
  int addedCards = 0;
  int expectedDeckCount = 0;
  int trashedCards = 0;
  int allOtherCardsPresent = 0;
  char output[OUTPUT_MAX];

  /* Generate a game state for each iteration and test it */
  for (i = 0; i < TEST_ITERATIONS; i++) {
    /* Generate a random gameState (zeroing out any previous state first) */
    generateGameState(&state);
    memcpy(&preState, &state, sizeof(struct gameState));

    /* Initialize some necessary variables before proceeding */
    passCount = 0;
    testCount = 0;
    addedCards = 0;
    expectedDeckCount = 0;
    trashedCards = 0;
    allOtherCardsPresent = 0;
    bzero(&gsc, sizeof(struct gameStateComparison));
    p = state.whoseTurn;
    choice1 = rand() % 3;   /* 0-2 */
    // choice1 = 0;
    choice2 = rand() % state.handCount[p];
    choice3 = rand() % state.handCount[p];
    handPos = handIndex(CARD, state.hand[p], state.handCount[p]);

    if (i != 0) {
      printf("\n\n");   /* Print some newlines to separate iteration output */
    }

    /* Print some brief identifying test information */
    printf(
      "----- Test: players: %d, whoseTurn: %d, handCount: %d, discardCount:",
      state.numPlayers, state.whoseTurn, state.handCount[p]
    );
    printf(
      " %d\n      handPos: %d, choice1: %d, choice2: %d, choice3: %d\n",
      state.discardCount[p], handPos, choice1, choice2, choice3
    );

    /* Test the card using the generated game state */
    result = cardEffect(CARD, choice1, choice2, choice3, &state, handPos, 0);
    compareState(&state, &preState, &gsc);

    if (choice1 == 1) {
      /* Determine the number of cards that were added from deck */
      if ((preState.deckCount[p] + preState.discardCount[p]) < 1) {
        addedCards = 0;
      } else if ((preState.deckCount[p] + preState.discardCount[p]) == 1) {
        addedCards = 1;
      } else if ((preState.deckCount[p] + preState.discardCount[p]) > 1) {
        addedCards = 2;
      }

      /* Determine the expected deck count */
      if (preState.deckCount[p] <= 1) {
        expectedDeckCount = preState.deckCount[p] + preState.discardCount[p];
      } else {
        expectedDeckCount = preState.deckCount[p];
      }
      expectedDeckCount -= addedCards;

      /* Hand should have additional cards, depending on deck availability */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.handCount[%d] = %d, expected = %d",
        p, state.handCount[p], (preState.handCount[p] + addedCards - 1)
      );
      passCount += fakeAssert(
        output,
        (state.handCount[p] == (preState.handCount[p] + addedCards - 1))
      );

      /* deckCount should be reduced according to the number of drawn cards */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.deckCount[%d] = %d, expected = %d",
        p, state.deckCount[p], expectedDeckCount
      );
      passCount += fakeAssert(
        output,
        (state.deckCount[p] == expectedDeckCount)
      );

      /* Shouldn't affect coins */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.coins = %d, expected = %d",
        state.coins, preState.coins
      );
      passCount += fakeAssert(
        output,
        (state.coins == preState.coins)
      );
    } else if (choice1 == 2) {
      /* Should add two additional coins */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.coins = %d, expected = %d",
        state.coins, (preState.coins + 2)
      );
      passCount += fakeAssert(
        output,
        (state.coins == (preState.coins + 2))
      );

      /* Shouldn't affect hand (other than the played card being removed) */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.handCount[%d] = %d, expected = %d",
        p, state.handCount[p], (preState.handCount[p] - 1)
      );
      passCount += fakeAssert(
        output,
        (state.handCount[p] == (preState.handCount[p] - 1))
      );

      /* Player's deck shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "gsc.deckChanged[%d] = %d, expected = %d",
        p, gsc.deckChanged[p], 0
      );
      passCount += fakeAssert(output, (gsc.deckChanged[p] == 0));

      /* Player's deckCount shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.deckCount[%d] = %d, expected = %d",
        p, state.deckCount[p], preState.deckCount[p]
      );
      passCount += fakeAssert(
        output,
        (state.deckCount[p] == preState.deckCount[p])
      );

      /* Player's discard pile shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "gsc.discardChanged[%d] = %d, expected = %d",
        p, gsc.discardChanged[p], 0
      );
      passCount += fakeAssert(output, (gsc.discardChanged[p] == 0));

      /* Player's discardCount shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.discardCount[%d] = %d, expected = %d",
        p, state.discardCount[p], preState.discardCount[p]
      );
      passCount += fakeAssert(
        output,
        (state.discardCount[p] == preState.discardCount[p])
      );
    } else {
      /* Should prevent players from trashing the played card or selecting
         the same card twice */
      if ((choice2 == handPos || choice3 == handPos) || (choice2 == choice3)) {
        /* Shouldn't allow CARD for choice2 or choice3 */
        testCount += 1;
        snprintf(
          output, OUTPUT_MAX,
          "result = %d, expected = %d",
          result, -1
        );
        passCount += fakeAssert(
          output,
          (result == -1)
        );
      }

      /* Determine how many cards should be trashed based on how many cards
         were *really* available in the hand (i.e. cards other than the card
         being played) */
      if ((preState.handCount[p] - 1) >= 2) {
        trashedCards = 2;
      } else if ((preState.handCount[p] - 1) >= 0) {
        trashedCards = preState.handCount[p] - 1;
      } else {
        trashedCards = 0;
      }

      /* Should trash the correct number of cards based on availability */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "handCount[%d] = %d, expected = %d",
        p, state.handCount[p], (preState.handCount[p] - trashedCards - 1)
      );
      passCount += fakeAssert(
        output,
        (state.handCount[p] == (preState.handCount[p] - trashedCards - 1))
      );

      /* Should trash the correct card for choice2 (with regard to preState) */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "card for choice2 is in hand = %d, expected = %d",
        containsCard(
          preState.hand[p][choice2], state.hand[p], state.handCount[p]
        ), 0
      );
      passCount += fakeAssert(
        output,
        (containsCard(
          preState.hand[p][choice2], state.hand[p], state.handCount[p]
        ) == 0)
      );

      /* Should trash the correct card for choice3 (with regard to preState) */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "card for choice3 is in hand = %d, expected = %d",
        containsCard(
          preState.hand[p][choice3], state.hand[p], state.handCount[p]
        ), 0
      );
      passCount += fakeAssert(
        output,
        (containsCard(
          preState.hand[p][choice3], state.hand[p], state.handCount[p]
        ) == 0)
      );

      /* Make sure all the other cards are still present in the hand */
      for (j = 0; j < preState.handCount[p]; j++) {
        if (
          preState.hand[p][j] == preState.hand[p][handPos]
          || preState.hand[p][j] == preState.hand[p][choice2]
          || preState.hand[p][j] == preState.hand[p][choice3]
        ) {
          continue;     /* Skip the cards that should have been removed */
        }

        /* Check if the card still exists in the player's hand */
        allOtherCardsPresent = containsCard(
          preState.hand[p][j], state.hand[p], state.handCount[p]
        );

        /* Prematurely break if any card doesn't exist in the player's hand */
        if (!allOtherCardsPresent) {
          break;
        }
      }

      /* Should only affect the chosen cards and the played card */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "all non-chosen cards present = %d, expected = %d",
        allOtherCardsPresent, 1
      );
      passCount += fakeAssert(
        output,
        (allOtherCardsPresent == 1)
      );
    }

    /* Should not affect other players */
    for (j = 0; j < state.numPlayers; j++) {
      if (j == p) {
        continue;     /* Skip over the current player */
      }

      /* Other player's hand shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "gsc.handChanged[%d] = %d, expected = %d",
        j, gsc.handChanged[j], 0
      );
      passCount += fakeAssert(output, (gsc.handChanged[j] == 0));

      /* Other player's handCount shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.handCount[%d] = %d, expected = %d",
        j, state.handCount[j], preState.handCount[j]
      );
      passCount += fakeAssert(
        output,
        (state.handCount[j] == preState.handCount[j])
      );

      /* Other player's deck shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "gsc.deckChanged[%d] = %d, expected = %d",
        j, gsc.deckChanged[j], 0
      );
      passCount += fakeAssert(output, (gsc.deckChanged[j] == 0));

      /* Other player's deckCount shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.deckCount[%d] = %d, expected = %d",
        j, state.deckCount[j], preState.deckCount[j]
      );
      passCount += fakeAssert(
        output,
        (state.deckCount[j] == preState.deckCount[j])
      );

      /* Other player's discard pile shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "gsc.discardChanged[%d] = %d, expected = %d",
        j, gsc.discardChanged[j], 0
      );
      passCount += fakeAssert(output, (gsc.discardChanged[j] == 0));

      /* Other player's discardCount shouldn't change */
      testCount += 1;
      snprintf(
        output, OUTPUT_MAX,
        "state.discardCount[%d] = %d, expected = %d",
        j, state.discardCount[j], preState.discardCount[j]
      );
      passCount += fakeAssert(
        output,
        (state.discardCount[j] == preState.discardCount[j])
      );
    }

    /* Should move played card to playedCards */
    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "state.hand[%d] contains steward = %d, expected = %d",
      p, containsCard(CARD, state.hand[p], state.handCount[p]), 0
    );
    passCount += fakeAssert(
      output,
      (!containsCard(CARD, state.hand[p], state.handCount[p]))
    );

    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "state.playedCards contains steward = %d, expected = %d",
      containsCard(CARD, state.playedCards, state.playedCardCount), 1
    );
    passCount += fakeAssert(
      output,
      (containsCard(CARD, state.playedCards, state.playedCardCount))
    );

    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "state.playedCardCount = %d, expected = %d",
      state.playedCardCount, (preState.playedCardCount + 1)
    );
    passCount += fakeAssert(
      output,
      (state.playedCardCount == (preState.playedCardCount + 1))
    );

    /* Print the final number of passing tests and the total number of tests */
    printTestResults(passCount, testCount);
  }

  return 0;
}

int main() {
  srand(time(NULL));
  randomlyTest();
  return 0;
}
