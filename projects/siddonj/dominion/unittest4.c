#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define DRAWCARD_PASS "drawCard() PASS: "
#define DRAWCARD_FAIL "drawCard() FAIL: "


void testDrawCard() {
  int i = 0;
  // Initilize game variables.
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = 3;
  int player = 0;
  int cardVariation = 0;

  // Create game.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();       // Get space for test game.

  printf("\n***** TESTING DRAW CARD *****\n");

  initializeGame(numPlayers, kingdomCards, randomSeed, state);

  // Start Test
  // Check one card is added to hand when drawCard() is called.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  player = testGame->whoseTurn;         // Get current player.

  drawCard(player, testGame);           // Draw a card.

  if (state->handCount[player]+1 != testGame->handCount[player]) {       // Hand count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = testGame->handCount[player] - state->handCount[player];
  printf("expected 'hand' total to increase by 1 after drawing card, got increase of: %d.\n", cardVariation);


  // Check one card is removed from deck when drawCard() is called.
  if (state->deckCount[player]-1 != testGame->deckCount[player]) {       // Deck count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = state->deckCount[player] - testGame->deckCount[player];
  printf("expected 'deck' count to decrease by 1 after drawing card, got decrease of: %d.\n", cardVariation);


  // Check no cards are discarded.
  if (state->discardCount[player] != testGame->discardCount[player]) {   // Discard count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = testGame->discardCount[player] - state->discardCount[player];
  printf("expected 'discard' count to stay the same after drawing card, got increase of: %d.\n", cardVariation);


  // Check and make sure other players card counts didn't change.
  for(i = 1; i < testGame->numPlayers; i++) {         // Don't start at player 1 since we already tested them.
    if (state->discardCount[i] != testGame->discardCount[i]) {   // Discard count.
      printf(DRAWCARD_FAIL);
    } else {
      printf(DRAWCARD_PASS);
    }
    cardVariation = testGame->discardCount[player] - state->discardCount[player];
    printf("expected Player %d's discard count to stay the same after 'Player 1' draws a card, got change of: %d.\n", i+1, cardVariation);


    if (state->deckCount[i] != testGame->deckCount[i]) {   // Deck count.
      printf(DRAWCARD_FAIL);
    } else {
      printf(DRAWCARD_PASS);
    }
    cardVariation = testGame->deckCount[player] - state->deckCount[player];
    printf("expected Player %d's deck count to stay the same after 'Player 1' draws a card, got change of: %d.\n", i+1, cardVariation);

    if (state->handCount[i] != testGame->handCount[i]) {   // Hand count.
      printf(DRAWCARD_FAIL);
    } else {
      printf(DRAWCARD_PASS);
    }
    cardVariation = testGame->handCount[player] - state->handCount[player];
    printf("expected Player %d's hand count to stay the same after 'Player 1' draws a card, got change of: %d.\n", i+1, cardVariation);

  }


  // Test drawing a card with no cards in deck.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  player = testGame->whoseTurn;         // Get current player.

  // Get rid of players deck without drawing cards.
  for(i = 0; i < testGame->deckCount[player]; i++) {                    // For each card in players deck.
    testGame->discard[player][i] = testGame->deck[player][i];           // Move each card in deck to discard pile.
    testGame->deck[player][i] = -1;                                     // Set card to empty.
  }
  testGame->discardCount[player] = testGame->deckCount[player];         // All of the cards in the deck should be in discard.
  testGame->deckCount[player] = 0;                                      // No more cards in deck.


  drawCard(player, testGame);           // Draw a card.

  if (state->handCount[player]+1 != testGame->handCount[player]) {       // Hand count increase 1.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = testGame->handCount[player] - state->handCount[player];
  printf("expected 'hand' total to increase by 1 after drawing card with no cards in deck, got increase of: %d.\n", cardVariation);


  if (state->deckCount[player]-1 != testGame->deckCount[player]) {       // Deck count should equal what it did before minus 1.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  printf("expected 'deck' total to increase by 4 after drawing card with no cards in deck, got increase of: %d.\n", testGame->deckCount[player]);


  if (state->discardCount[player] != testGame->discardCount[player]) {   // Discard count should equal 0.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  printf("expected 'discard' total to equal 0 after drawing a card with no cards in deck, got : %d.\n", testGame->discardCount[player]);

  // Clean memory.
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;

}


int main() {
  testDrawCard();
  return 0;
}
