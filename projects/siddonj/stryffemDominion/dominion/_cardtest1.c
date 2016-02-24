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
  struct gameState *testGame = newGame();

  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Initialize game with valid game values.


  printf("\n***** TESTING PLAY SMITHY *****\n");

  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  // Test playing smithy correctly increments player's handsize.
  playerHandSize = numHandCards(testGame);       // Get hand size.
  playerActions = testGame->numActions;          // Get initial action amount.

  handSizeIncrease = 0;
  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  // Set player 1's first card in hand to be smithy card.
  testGame->hand[testGame->whoseTurn][0] = smithy;

  
  smithyCard(0, testGame->whoseTurn, testGame);         // First card is smithy;

  handSizeIncrease = numHandCards(testGame) - playerHandSize;       // Find amount players hand size increased by.
  actionDecrease = playerActions - testGame->numActions;

  // See if any other players handsize increased, don't include player that played smithy.
  for(i = 1; i < numPlayers; i++) {
    if(testGame->handCount[i] > 0) {
      otherHandIncrease++;
    }
    if(testGame->deckCount[i] > 10) {
      otherDeckIncrease++;
    }
    if(testGame->discardCount[i] > 0) {
      otherDiscardIncrease++;
    }
  }

  // Make sure player has no more smithy cards in hand since we only added one to their hand.
  for(i = 0; i < numHandCards(testGame); i++) {
    if(testGame->hand[testGame->whoseTurn][i] == smithy) {        // There is a smithy in hand.
      smithyHandCount++;
    }
  }

  // Make sure player has no smithy cards in discard pile.
  for(i = 0; i < testGame->discardCount[testGame->whoseTurn]; i++) {
    if(testGame->discard[testGame->whoseTurn][i] == smithy) {        // There is a smithy in discard.
      smithyDiscardCount++;
    }
  }

  // Make sure player has 1 smithy card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == smithy) {        // There is a smithy in played cards.
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

  if(state->deckCount[state->whoseTurn] == testGame->deckCount[testGame->whoseTurn]+3) {    // Smithy draws 3 cards so deck should decrease by 3.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'deck' size to decrease by a total of '3', 'deck' decreased by: %d\n", state->deckCount[state->whoseTurn]-testGame->deckCount[testGame->whoseTurn]);

  if(actionDecrease == 1) {    // Action reduced by 1 the same.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'action' amount to decrease by '1', 'actions' decreased by: %d\n", actionDecrease);

  if(testGame->numBuys == 1) {    // Number of buys should still be 1.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1's 'buy' amount to be '1', got: %d\n", testGame->numBuys);

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

  if(testGame->coins == state->coins) {         // 0 coin change.
    printf(PLAYSMITHY_PASS);
  } else {
    printf(PLAYSMITHY_FAIL);
  }
  printf("expects Player 1 'coins' to be the same after playing smithy, changed by: %d\n", testGame->coins-state->coins);

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


  // Free memory
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;

}

int main() {
  testPlaySmithy();
  return 0;
}
