/* Randomly test the Adventurer card
   NOTE: Adventurer should:
     * Draw cards from the player's deck until two treasure cards are drawn.
     * Discard all drawn cards that are not treasure cards.
     * Move the played card to the playedCards pile.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "dominion.h"
#include "fordsamTest.h"

#define CARD adventurer
#define TEST_ITERATIONS 10
#define OUTPUT_MAX 200

/* TODO: Tweak probabilities (e.g. tresure card)? */

/* Generates a random game state that's catered to this context (avoiding the
   randomization of parts of the game state which have no impact on this
   particular function's behavior) */
void generateGameState(struct gameState *state) {
  int i = 0, j = 0;

  /* Set the gameState to all zeros to clear any previous state */
  bzero(state, sizeof(struct gameState));

  /* Number of players - between 2 and MAX_PLAYERS */
  state->numPlayers = rand() % (MAX_PLAYERS - 1) + 2;

  /* whoseTurn is randomly chosen from existing players */
  state->whoseTurn = rand() % state->numPlayers;

  /* Initialize the hand, deck, and discard of every player */
  for (i = 0; i < state->numPlayers; i++) {
    /* Populate the hand with 0-10 cards */
    state->handCount[i] = rand() % 11;
    for (j = 0; j < state->handCount[i]; j++) {
      /* Generate a random card, avoiding treasure cards and CARD */
      do {
        state->hand[i][j] = rand() % (treasure_map + 1);
      } while (
        state->hand[i][j] == copper
        || state->hand[i][j] == silver
        || state->hand[i][j] == gold
        || state->hand[i][j] == CARD
      );
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

/* This function calculates the number of treasure cards that could potentially
   be drawn, assuming the discard is shuffled into the deck when all of the
   cards in the deck have been drawn */
int playerTreasureToDraw(struct gameState *state) {
  int count = 0;
  int i = 0;

  /* Go through the player's deck looking for treasure cards */
  for (i = 0; i < state->deckCount[state->whoseTurn]; i++) {
    if (isTreasureCard(state->deck[state->whoseTurn][i])) {
      count += 1;
    }
  }

  /* Go through the player's discard pile looking for treasure cards */
  for (i = 0; i < state->discardCount[state->whoseTurn]; i++) {
    if (isTreasureCard(state->discard[state->whoseTurn][i])) {
      count += 1;
    }
  }

  return count;
}

/* Randomly test the Adventurer card */
int randomlyTestAdventurer() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  int childResult = 0;
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};
  pid_t pid = -1;
  int status = 0;
  int i = 0, j = 0;
  int p = 0;
  int numTreasureToDraw = 0;
  int playerCardCount = 0;
  int addedCards = 0;
  char output[OUTPUT_MAX];

  /* Generate a game state for each iteration and test it */
  for (i = 0; i < TEST_ITERATIONS; i++) {
    /* Generate a random gameState (zeroing out any previous state first) */
    generateGameState(&state);
    memcpy(&preState, &state, sizeof(struct gameState));

    /* Initialize some necessary variables before proceeding */
    passCount = 0;
    testCount = 0;
    bzero(&gsc, sizeof(struct gameStateComparison));
    p = state.whoseTurn;
    numTreasureToDraw = playerTreasureToDraw(&state);

    if (numTreasureToDraw == 0) {
      /* Run the test in a child process since it can get into a bad state */
      pid = fork();
      if (pid < 0) {
        perror("Error forking");
      } else if (pid == 0) {
        /* Execute the test in the child process */
        result = playAdventurer(&state, p);

        exit(result);
      } else if (pid > 0) {
        /* Wait for the child process to finish */
        wait(&status);

        /* Check if the child process exited cleanly or crashed and store the
           result so we can print it later */
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
          childResult = 1;
        } else {
          childResult = 0;
        }
      }
    }

    if (i != 0) {
      printf("\n\n");   /* Print some newlines to separate iteration output */
    }

    /* Print some brief identifying test information */
    printf(
      "----- Test: players: %d, whoseTurn: %d, treasure cards: %d\n",
      state.numPlayers, state.whoseTurn, numTreasureToDraw
    );

    /* Do special tests for game states with no treasure cards */
    if (numTreasureToDraw == 0) {
      /* Should not crash then there are no available treasure cards */
      testCount += 1;
      passCount += fakeAssert(
        "Should not crash when there are no available treasure cards",
        (childResult)
      );

      if (childResult == 0) {
        /* Print a note about skipping tests and move on to the next iteration
           if execution of the function didn't exit cleanly */
        printf("NOTE: Some tests have been skipped because of this failure\n");
        printTestResults(passCount, testCount);
        continue;
      }
    }

    /* Test the function using the generated game state */
    result = playAdventurer(&state, p);
    compareState(&state, &preState, &gsc);

    /* Determine the number of treasure cards that should have been added to
       the player's hand */
    if (numTreasureToDraw < 1) {
      addedCards = 0;
    } else if (numTreasureToDraw == 1) {
      addedCards = 1;
    } else if (numTreasureToDraw > 1) {
      addedCards = 2;
    }

    /* Should draw the correct number of cards to the player's hand
       NOTE: We subtract one for the removal of the played card */
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

    /* Should draw the correct number of *treasure cards* to the player's
       hand */
    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "treasure cards in player's hand = %d, expected = %d",
      treasureCardsInHand(p, &state),
      (treasureCardsInHand(p, &preState) + addedCards)
    );
    passCount += fakeAssert(
      output,
      (treasureCardsInHand(p, &state)
      == (treasureCardsInHand(p, &preState) + addedCards))
    );

    /* Should not affect other players */
    for (j = 0; j < state.numPlayers; j++) {
      if (j == p) {
        continue;     /* Skip over current player */
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

    /* Calculate the player's card count (hand + deck + discard
       + playedCardCount) in preState so we can test against it below */
    playerCardCount = preState.handCount[preState.whoseTurn]
      + preState.deckCount[preState.whoseTurn]
      + preState.discardCount[preState.whoseTurn]
      + preState.playedCardCount;

    /* All of the player's cards should still be accounted for */
    /* NOTE: I think this is the best I can do for now in terms of checking
       whether all of the drawn cards are discarded.  We can't predict the
       order of the cards when they're shuffled(), so we can't make assertions
       about what the deck or discard pile should look like when
       Adventurer finishees. */
    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "hand + deck + discard + playedCards = %d, expected = %d",
      (state.handCount[p] + state.deckCount[p] + state.discardCount[p]
        + state.playedCardCount),
      playerCardCount
    );
    passCount += fakeAssert(
      output,
      (state.handCount[p] + state.deckCount[p] + state.discardCount[p]
        + state.playedCardCount) == playerCardCount
    );

    /* Should move played card to playedCards */
    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "state.hand[%d] contains adventurer = %d, expected = %d",
      p, containsCard(CARD, state.hand[p], state.handCount[p]), 0
    );
    passCount += fakeAssert(
      output,
      (!containsCard(CARD, state.hand[p], state.handCount[p]))
    );

    testCount += 1;
    snprintf(
      output, OUTPUT_MAX,
      "state.playedCards contains adventurer = %d, expected = %d",
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
  randomlyTestAdventurer();
  return 0;
}
