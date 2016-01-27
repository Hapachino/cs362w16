#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "dominion.h"

#define PLAYSMITHY_PASS "playSmithy() PASS: "
#define PLAYSMITHY_FAIL "playSmithy() FAIL: "


void testPlaySmithy() {
  int i = 0;
  int playerHandSize = 0;       // Get hand size.
  int playerActions = 0;
  int handSizeIncrease = 0;
  int actionDecrease = 0;
  int smithyHandCount = 0;
  int smithyDiscardCount = 0;
  int smithyPlayedCount = 0;

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;



  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  struct gameState *state = newGame();          // Initialize game state.


  printf("\n***** TESTING PLAY SMITHY *****\n");

  // Test playing smithy correctly increments player's handsize.
  // Initialize game with valid game values.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);
  playerHandSize = numHandCards(state);       // Get hand size.
  playerActions = state->numActions;          // Get initial action amount.

  handSizeIncrease = 0;
  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  // Set player 1's first card in hand to be smithy card.
  state->hand[state->whoseTurn][0] = smithy;
  playSmithy(state, state->whoseTurn, 0);         // First card is smithy;

  handSizeIncrease = numHandCards(state) - playerHandSize;       // Find amount players hand size increased by.
  actionDecrease = playerActions - state->numActions;

  // See if any other players handsize increased, don't include player that played smithy.
  for(i = 1; i < numPlayers; i++) {
    if(state->handCount[i] > 0) {
      otherHandIncrease++;
    }
    if(state->deckCount[i] > 10) {
      otherDeckIncrease++;
    }
    if(state->discardCount[i] > 0) {
      otherDiscardIncrease++;
    }
  }

  // Make sure player has no more smithy cards in hand since we only added one to their hand.
  for(i = 0; i < numHandCards(state); i++) {
    if(state->hand[state->whoseTurn][i] == smithy) {        // There is a smithy in hand.
      smithyHandCount++;
    }
  }

  // Make sure player has no smithy cards in discard pile.
  for(i = 0; i < state->discardCount[state->whoseTurn]; i++) {
    if(state->discard[state->whoseTurn][i] == smithy) {        // There is a smithy in discard.
      smithyDiscardCount++;
    }
  }

  // Make sure player has 1 smithy card in played card pile.
  for(i = 0; i < state->playedCardCount; i++) {
    if(state->playedCards[i] == smithy) {        // There is a smithy in played cards.
      smithyDiscardCount++;
    }
  }


  // Player who played card.
  if(handSizeIncrease == 2) {    // Smithy draws 3 cards, but also the player discards smithy making net handsize gain only two.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'hand' size to increase by a total of '2', 'hand' increased by: %d\n", handSizeIncrease);

  if(actionDecrease == 1) {    // Action reduced by 1 the same.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'action' amount to decrease by '1', 'actions' decreased by: %d\n", actionDecrease);

  if(state->numBuys == 1) {    // Number of buys should still be 1.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'buy' amount to be '1', got: %d\n", state->numBuys);

  if(smithyHandCount == 0) {    // No smithy in hand.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1 to have 0 'smithy' cards in hand, got: %d\n", smithyHandCount);

  if(smithyPlayedCount == 1) {    // 1 smithy in played cards pile.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1 to have 1 'smithy' card in played card pile, got: %d\n", smithyPlayedCount);

  if(smithyDiscardCount == 0) {    // 0 smithy in discard.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1 to have 0 'smithy' cards in discard pile, got: %d\n", smithyDiscardCount);

  if(state->coins == 0) {         // 0 coin change.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1 'coins' to be 0 after playing smithy, got: %d\n", state->coins);

  // Other players
  if(otherHandIncrease == 0) {    // Make sure other players hand size doesn't increase.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects other player's 'hand' size to not increase, other player's 'hands' increased by: %d\n", otherHandIncrease);

  if(otherDeckIncrease == 0) {    // Make sure other players deck size doesn't increase.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects other player's 'deck' size to not increase, other player's 'decks' increased by: %d\n", otherDeckIncrease);

  if(otherDiscardIncrease == 0) {    // Make sure other players discard size doesn't increase.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects other player's 'discard' size to not increase, other player's 'discard' pile increased by: %d\n", otherDiscardIncrease);



}

int main() {
  testPlaySmithy();
  return 0;
}
