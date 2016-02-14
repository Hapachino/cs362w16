#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

/**
 * Change the game to some random but still valid state.
 */
void randomizeGameState(struct gameState *state, int *k, int k_size) {
  state->whoseTurn = rand() % state->numPlayers;
  //populate the deck randomly

  //add a random # of cards to the players deck
  state->deckCount[state->whoseTurn] = 0;
  int addCards = rand() % 20;
  while (addCards > 0 && state->deckCount[state->whoseTurn] < MAX_DECK) {
    //randomly choose between treasure and action cards
    int choice = rand() % 4;
    if (choice == 0) {

      int randCard = rand() % k_size;
      
      if (supplyCount(randCard, state) > 0) {
        state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = k[randCard];
        state->deckCount[state->whoseTurn]++;
        addCards--;
      }
    }
    else {
      if (choice == 1) {
        state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = copper;
      }
      else if (choice == 2) {
        state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = silver;
      }
      else {
        state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = gold;
      }
      state->deckCount[state->whoseTurn]++;
      addCards--;
    }
  }

  //put the players hand back in the deck
  while(state->handCount[state->whoseTurn] > 0) {
    state->deck[state->whoseTurn][state->deckCount[state->whoseTurn]] = 
      state->hand[state->whoseTurn][state->handCount[state->whoseTurn]];
    state->deckCount[state->whoseTurn]++;
    state->handCount[state->whoseTurn]--;
  }

  shuffle(state->whoseTurn, state);

  for (int j = 0; j < 5; j++) {
    drawCard(state->whoseTurn, state);
  }
}

/**
 * Returns the integer index of the smithy in the players hand. -1
 * if the smithy isn't in their hand.
 */
int smithyInHand(struct gameState *state, int player) {

  for (int i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == smithy) {
      return i;
    }
  }
  return -1;
}

int smithyInHandCount(struct gameState *state, int player) {

  int count = 0;
  for (int i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == smithy) {
      count++;
    }
  }
  return count;
}

int main() {

  int k[10] = {smithy, adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute};
  struct gameState state, referenceState;

  int testRunCount = 0, testFailCount = 0;

  while (testRunCount < 10000) {

    initializeGame(rand() % 3 + 2, k, rand(), &state);
    randomizeGameState(&state, k, 10);
      testRunCount++;

    int smithyHandPos = smithyInHand(&state, state.whoseTurn);
    int smithyHandCount = smithyInHandCount(&state, state.whoseTurn);

    if (smithyHandPos >= 0) {
      testRunCount++;
      memcpy(&referenceState, &state, sizeof(struct gameState));

      int cardPlayed = playCard(smithyHandPos, -1, -1, -1, &state);

      printf("Testing playing the card didn't return an error...");
      if (cardPlayed >= 0) {
        printf(" passed.\n");

        /*
        printf("Testing that the smithys in hand reduced by 1...");
        if (smithyHandCount - smithyInHandCount(&state, state.whoseTurn)) {
          printf(" passed.\n");
        }
        else {
          printf("FAILED!\n");
        }
        */

        printf("Testing that the hand count has increased by 2...");
        int handDifference = state.handCount[state.whoseTurn] - referenceState.handCount[referenceState.whoseTurn];
        if (handDifference == 2) {
          printf("passed.\n");
        }
        else {
          printf("FAILED!\n");
          printf("   expected 2 but was %d\n", handDifference);
          
          testFailCount++;
        }
      }
      else {
          printf(" FAILED!\n");
          testFailCount++;
      }
    }
  }

  if (testFailCount == 0) {
    printf("SUCCESS %d of %d tests passed.\n", testRunCount, testRunCount);
    return 0;
  }
  else {
    printf("FAILURE! %d of %d tests passed.\n", 
      testRunCount - testFailCount, 
      testRunCount);
  }

  return 0;
}
