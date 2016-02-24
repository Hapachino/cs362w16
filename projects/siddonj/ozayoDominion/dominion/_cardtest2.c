#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dominion.h"
#include "dominion_helpers.h"

#define PLAYADVENTURER_PASS "playAdventurer() PASS: "
#define PLAYADVENTURER_FAIL "playAdventurer() FAIL: "


void testPlayAdventurer() {
  int i = 0;

  int adventurerHandCount = 0;
  int adventurerDiscardCount = 0;
  int adventurerPlayedCount = 0;
  int treasureCount = 0;        // Starting treasure amount.
  int increasedTreasure = 0;    // Amount treasure increased.

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;


  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();

  initializeGame(numPlayers, kingdomCards, randomSeed, state);  // Initialize game with valid game values.

  printf("\n***** TESTING PLAY ADVENTURER *****\n");
  memcpy(testGame, state, sizeof(struct gameState));            // Clean out previous state.

  // Figure out how many treasure in player's hand before playing adventurer.
  for(i = 0; i < testGame->handCount[testGame->whoseTurn]; i++) {
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      treasureCount++;
    }
  }

  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  // Set player 1's first card in hand to be adventurer card.
  testGame->hand[testGame->whoseTurn][0] = adventurer;
  adventurerCard(testGame);         // First card is adventurer;


  // See if any other players handsize increased, don't include player that played adventurer.
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

  // Check what player has in hand.
  for(i = 0; i < numHandCards(testGame); i++) {
    if(testGame->hand[testGame->whoseTurn][i] == adventurer) {        // There is a adventurer in hand.
      adventurerHandCount++;
    }

    // Count up # of treasures.
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      increasedTreasure++;
    }
  }

  increasedTreasure = increasedTreasure - treasureCount;    // Determine total quantity treasure increased by.

  // Make sure player has no adventurer cards in discard pile.
  for(i = 0; i < testGame->discardCount[testGame->whoseTurn]; i++) {
    if(testGame->discard[testGame->whoseTurn][i] == adventurer) {        // There is a adventurer in discard.
      adventurerDiscardCount++;
    }
  }

  // Make sure player has 1 adventurer card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == adventurer) {        // There is a adventurer in played cards.
      adventurerDiscardCount++;
    }
  }

  // Player who played card.
  if(state->handCount[state->whoseTurn]+1 == testGame->handCount[testGame->whoseTurn]) {    // Adventurer puts two treasures in hand but discards Adventurer making net handsize gain only 1.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1's 'hand' size to increase by a total of '1', 'hand' increased by: %d\n", testGame->handCount[testGame->whoseTurn]-state->handCount[state->whoseTurn]);

  if(state->numActions-1 == testGame->numActions) {    // Action reduced by 1 the same.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1's 'action' amount to decrease by '1', 'actions' decreased by: %d\n", state->numActions-testGame->numActions);

  if(testGame->numBuys == state->numBuys) {    // Number of buys should still be 1.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1's 'buy' amount to not change, changed by: %d\n", state->numBuys-testGame->numBuys);

  if(adventurerHandCount == 0) {    // No adventurer in hand.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1 to have 0 'adventurer' cards in hand after playing it, got: %d\n", adventurerHandCount);

  if(adventurerPlayedCount == 1) {    // 1 adventurer in played cards pile.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1 to have 1 'adventurer' card in played card pile after playing it, got: %d\n", adventurerPlayedCount);

  if(adventurerDiscardCount == 0) {    // 0 adventurer in discard.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1 to have 0 'adventurer' cards in discard pile after playing it, got: %d\n", adventurerDiscardCount);

  if(testGame->coins == state->coins) {         // 0 coin change.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1 'coins' to be the same after playing adventurer, changed by: %d\n", testGame->coins-state->coins);

  if(increasedTreasure == 2) {         // Player should have 2 more treasures in hand.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects Player 1 to have 2 additional treasures in hand after playing adventurer, got: %d\n", increasedTreasure);

  // Other players
  if(otherHandIncrease == 0) {    // Make sure other players hand size doesn't increase.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects other player's 'hand' size to not increase, other player's 'hands' increased by: %d\n", otherHandIncrease);

  if(otherDeckIncrease == 0) {    // Make sure other players deck size doesn't increase.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects other player's 'deck' size to not increase, other player's 'decks' increased by: %d\n", otherDeckIncrease);

  if(otherDiscardIncrease == 0) {    // Make sure other players discard size doesn't increase.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects other player's 'discard' size to not increase, other player's 'discard' pile increased by: %d\n", otherDiscardIncrease);


  // Initialize new game.
  // Initialize game with valid game values.
  memcpy(testGame, state, sizeof(struct gameState));            // Clean out previous state.
  int failPlay = adventurerCard(testGame);   // Don't put adventurer card in player 1's hand.

  if(failPlay == -1) {    // Should return error.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects method to return '-1', when player doesn't have adventurer in hand and tries to play one, got: %d\n", failPlay);


  // Initialize new game, test playing without deck.
  // Initialize game with valid game values.
  memcpy(testGame, state, sizeof(struct gameState));            // Clean out previous state.

  // Set each card in players hand to a treasure.
  for(i = 0; i < testGame->handCount[testGame->whoseTurn]; i++) {
    testGame->hand[testGame->whoseTurn][i] = copper;
  }

  // Set each card remaining in deck to a treasure.
  for(i = 0; i < testGame->deckCount[testGame->whoseTurn]; i++) {
    testGame->deck[testGame->whoseTurn][i] = copper;
  }

  // Draw entire deck and discard each card. Sets deck to empty.
  for(i = 0; i < testGame->deckCount[testGame->whoseTurn]; i++) {
    drawCard(testGame->whoseTurn, testGame);              // Draw card.
    discardCard(i, testGame->whoseTurn, testGame, 0);     // Discard card.
  }
  testGame->hand[testGame->whoseTurn][0] = adventurer;    // Turn first card in hand to adventurer.
  testGame->handCount[testGame->whoseTurn] = 1;                                // Set hand total to only 1.

  failPlay = adventurerCard(testGame);          // Play adventurer with empty deck.

  if(failPlay == 0) {    // Should be successful.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects method to return '0', when player plays adventurer with no cards in deck, got: %d\n", failPlay);

  // Since each card in players hand and deck was set to treasure, there should be cards remaning in deck after playing adventure.
  if(testGame->deckCount[testGame->whoseTurn] > 0) {
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects deck to contain more than '0' cards, after player plays adventurer with no cards in deck, deck contains: %d\n", testGame->deckCount[testGame->whoseTurn]);

  if(testGame->discardCount[testGame->whoseTurn] == 0) {
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects discard to contain '0' cards, after player plays adventurer with no cards in deck, discard contains: %d\n", testGame->discardCount[testGame->whoseTurn]);



  // Initialize new game, test playing with only 1 treasure in deck.
  // Initialize game with valid game values.
  memcpy(testGame, state, sizeof(struct gameState));            // Clean out previous state.

  // Set each card in players hand to a estate.
  for(i = 0; i < testGame->handCount[testGame->whoseTurn]; i++) {
    testGame->hand[testGame->whoseTurn][i] = estate;
  }

  // Set each card remaining in deck to a estate.
  for(i = 0; i < testGame->deckCount[testGame->whoseTurn]; i++) {
    testGame->deck[testGame->whoseTurn][i] = estate;
  }

  testGame->deck[testGame->whoseTurn][0] = copper;              // Set first card in deck to copper.
  testGame->hand[testGame->whoseTurn][0] = adventurer;          // Turn first card in hand to adventurer.

  failPlay = adventurerCard(testGame);          // Play adventurer with 1 copper in deck.

  if(failPlay == 0) {    // Should be successful.
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects method to return '0', when player plays adventurer with 1 treasure in deck, got: %d\n", failPlay);

  if(testGame->handCount[testGame->whoseTurn] == state->handCount[state->whoseTurn]+1) {
    printf(PLAYADVENTURER_PASS);
  } else {
    printf(PLAYADVENTURER_FAIL);
  }
  printf("expects players hand count to only increase by 1 when deck only contains 1 treasure card in deck, got increase of: %d\n", testGame->handCount[testGame->whoseTurn]-state->handCount[state->whoseTurn]);


  // Clean memory
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;

}

int main() {
  testPlayAdventurer();
  return 0;
}
