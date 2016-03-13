#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interface.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int adventurerEffect(int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

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

int countTreasuresInHand(struct gameState *state, int player) {

  int treasures = 0;

  for (int i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == copper || state->hand[player][i] == silver || state->hand[player][i] == gold) {
      treasures++;
    }
  }

  return treasures;
}

/**
 * Returns the integer index of the adventurer in the players hand. -1
 * if the adventurer isn't in their hand.
 */
int adventurerInHand(struct gameState *state, int player) {

  for (int i = 0; i < state->handCount[player]; i++) {
    if (state->hand[player][i] == adventurer) {
      return i;
    }
  }
  return -1;
}

int main() {

  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  struct gameState state, referenceState;

  int testRunCount = 0, testFailCount = 0;

  while (testRunCount < 10000) {

    initializeGame(rand() % 3 + 2, k, rand(), &state);
    randomizeGameState(&state, k, 10);

    int adventurerHandPos = adventurerInHand(&state, state.whoseTurn);
    if (adventurerHandPos >= 0) {

      testRunCount++;
      memcpy(&referenceState, &state, sizeof(struct gameState));

      int cardPlayed = playCard(adventurerHandPos, -1, -1, -1, &state);

      printf("Testing playing the card didn't return an error...");
      if (cardPlayed >= 0) {
        printf(" passed.\n");

        printf("Testing we drew 2 treasures...");
        if (countTreasuresInHand(&state, state.whoseTurn) - 
          countTreasuresInHand(&referenceState, state.whoseTurn) == 2) {

            printf(" passed\n");

            printf("Testing it's still the same persons turn...");
            if (state.whoseTurn == referenceState.whoseTurn) {
              printf(" passed\n");
            }
            else {
              printf(" FAILED!\n");
              printf("   Found it to be %ds turn instead of %d\n", state.whoseTurn, referenceState.whoseTurn);
              testFailCount++;
            }
        }
        else {
         printf(" FAILED!\n");
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
