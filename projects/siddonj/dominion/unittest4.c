#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define DRAWCARD_PASS "drawCard() PASS: "
#define DRAWCARD_FAIL "drawCard() FAIL: "


void testDrawCard() {
  // Initilize game variables.
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = 3;
  int player = 0;

  int handBefore = 0;
  int deckBefore = 0;
  int discardBefore = 0;
  int cardVariation = 0;

  // Create game.
  struct gameState *state = newGame();          // Initialize game state.

  printf("\n***** TESTING DRAW CARD *****\n");


  // Start Test
  // Check one card is added to hand when drawCard() is called, with cards available in deck.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);

  player = state->whoseTurn;

  // Capture state before call.
  handBefore = state->handCount[player];
  deckBefore = state->deckCount[player];
  discardBefore = state->discardCount[player];

  drawCard(player, state);

  if (handBefore+1 != state->handCount[player]) {       // Hand count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = state->handCount[player] - handBefore;
  printf("expected 'hand' total to increase by 1 after drawing card, got increase of: %d.\n", cardVariation);


  if (deckBefore-1 != state->deckCount[player]) {       // Deck count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = deckBefore - state->deckCount[player];
  printf("expected 'deck' count to decrease by 1 after drawing card, got decrease of: %d.\n", cardVariation);


  if (discardBefore != state->discardCount[player]) {   // Discard count.
    printf(DRAWCARD_FAIL);
  } else {
    printf(DRAWCARD_PASS);
  }
  cardVariation = state->discardCount[player] - discardBefore;
  printf("expected 'discard' count to stay the same after drawing card, got increase of: %d.\n", cardVariation);

}


int main() {
  testDrawCard();
  return 0;
}
