#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dominion.h"

#define PLAYREMODEL_PASS "playRemodel() PASS: "
#define PLAYREMODEL_FAIL "playRemodel() FAIL: "


void testPlayRemodel() {
  int i = 0;
  int playerHandSize = 0;       // Get hand size.
  int playerActions = 0;
  int handSizeDecrease = 0;
  int actionDecrease = 0;
  int remodelHandCount = 0;
  int remodelDiscardCount = 0;
  int remodelPlayedCount = 0;
  int treasureCount = 0;        // Starting treasure amount.
  int increasedTreasure = 0;    // Amount treasure increased.

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;


  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  struct gameState *state = newGame();          // Initialize game state.


  printf("\n***** TESTING PLAY REMODEL *****\n");
  // Initialize game with valid game values.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);
  playerHandSize = numHandCards(state);       // Get hand size.
  playerActions = state->numActions;          // Get initial action amount.

  handSizeDecrease = 0;
  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;


  // Set player 1's first card in hand to be adventurer card.
  state->hand[state->whoseTurn][0] = remodel;
  state->hand[state->whoseTurn][1] = adventurer;
  int gardensDiscardCount = 0;
  // (state, player, remodel card hand position, card position to buy, card hand position to trash)
  playRemodel(state, state->whoseTurn, 0, 1, 1);      // Trying to buy gardens by trashing a adventurer.

  handSizeDecrease = playerHandSize - numHandCards(state);       // Find amount players hand size increased by.
  actionDecrease = playerActions - state->numActions;            // Find amount players action decreased by.

  // See if any other players handsize increased, don't include player that played adventurer.
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

  // Check what player has in hand.
  for(i = 0; i < numHandCards(state); i++) {
    if(state->hand[state->whoseTurn][i] == remodel) {        // There is a remodel in hand.
      remodelHandCount++;
    }

    // Count up # of treasures.
    if(state->hand[state->whoseTurn][i] == copper || state->hand[state->whoseTurn][i] == silver || state->hand[state->whoseTurn][i] == gold ) {
      increasedTreasure++;
    }
  }

  increasedTreasure = increasedTreasure - treasureCount;    // Determine total quantity treasure increased by.

  // Make sure player has no remodel cards in discard pile.
  for(i = 0; i < state->discardCount[state->whoseTurn]; i++) {
    if(state->discard[state->whoseTurn][i] == remodel) {        // There is a remodel in discard.
      remodelDiscardCount++;
    }

    if(state->discard[state->whoseTurn][i] == gardens) {        // There is a gardens in discarded cards because we bought one.
      gardensDiscardCount++;
    }
  }

  // Make sure player has 1 remodel card in played card pile.
  for(i = 0; i < state->playedCardCount; i++) {
    if(state->playedCards[i] == remodel) {        // There is a remodel in played cards.
      remodelPlayedCount++;
    }
  }

  // Player who played card.
  if(handSizeDecrease == 2) {    // Discard remodel, trash another, gained card goes to discard pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1's 'hand' size to decrease by a total of '2', 'hand' decreased by: %d\n", handSizeDecrease);

  if(actionDecrease == 1) {    // Action reduced by 1 the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1's 'action' amount to decrease by '1', 'actions' decreased by: %d\n", actionDecrease);

  if(state->numBuys == 1) {    // Number of buys should still be 1.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1's 'buy' amount to be '1', got: %d\n", state->numBuys);

  if(remodelHandCount == 0) {    // No remodel in hand.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 0 'adventurer' cards in hand, got: %d\n", remodelHandCount);

  if(remodelPlayedCount == 1) {    // one remodel in played cards pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 'remodel' card in played card pile, got: %d\n", remodelPlayedCount);

  if(remodelDiscardCount == 0) {    // 0 remodel in discard because we are trying to buy a gardens.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 0 'remodel' cards in discard pile, got: %d\n", remodelDiscardCount);

  if(gardensDiscardCount == 1) {    // 1 gardens in discard because we bought a gardens.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 'gardens' card in discard pile, got: %d\n", gardensDiscardCount);

  if(state->playedCardCount == 1) {    // Only one card in played card pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 card in played card pile, got: %d\n", state->playedCardCount);

  // if(state->coins == 0) {             // 0 coin change.
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects Player 1 'coins' to be 0 after playing adventurer, got: %d\n", state->coins);

  // if(increasedTreasure == 2) {         // Player should have 2 more treasures in hand.
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects Player 1 to have 2 additional treasures in hand after playing adventurer, got: %d\n", increasedTreasure);

  // Other players
  if(otherHandIncrease == 0) {    // Make sure other players hand size doesn't increase.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects other player's 'hand' size to not increase, other player's 'hands' increased by: %d\n", otherHandIncrease);

  if(otherDeckIncrease == 0) {    // Make sure other players deck size doesn't increase.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects other player's 'deck' size to not increase, other player's 'decks' increased by: %d\n", otherDeckIncrease);

  if(otherDiscardIncrease == 0) {    // Make sure other players discard size doesn't increase.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects other player's 'discard' size to not increase, other player's 'discard' pile increased by: %d\n", otherDiscardIncrease);


  // Initialize new game.
  // Initialize game with valid game values.

  // successfulInit = initializeGame(numPlayers, kingdomCards, randomSeed, state);
  // int failPlay = PLAYREMODEL(state, state->whoseTurn);   // Don't put adventurer card in player 1's hand.
  //
  // if(failPlay == -1) {    // Should return error.
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects method to return '-1', when player doesn't have adventurer in hand and tries to play one, got: %d\n", failPlay);


  // // Initialize new game, test playing without deck.
  // // Initialize game with valid game values.
  // successfulInit = initializeGame(numPlayers, kingdomCards, randomSeed, state);
  //
  // // Set each card in players hand to a treasure.
  // for(i = 0; i < state->handCount[state->whoseTurn]; i++) {
  //   state->hand[state->whoseTurn][i] = copper;
  // }
  //
  // // Set each card remaining in deck to a treasure.
  // for(i = 0; i < state->deckCount[state->whoseTurn]; i++) {
  //   state->deck[state->whoseTurn][i] = copper;
  // }
  //
  // // Draw entire deck and discard each card. Sets deck to empty.
  // for(i = 0; i < state->deckCount[state->whoseTurn]; i++) {
  //   drawCard(state->whoseTurn, state);              // Draw card.
  //   discardCard(i, state->whoseTurn, state, 0);     // Discard card.
  // }
  // state->hand[state->whoseTurn][0] = adventurer;    // Turn first card in hand to adventurer.
  // failPlay = PLAYREMODEL(state, state->whoseTurn);          // Play adventurer with empty deck.
  //
  // if(failPlay == 0) {    // Should be successful.
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects method to return '0', when player plays adventurer with no cards in deck, got: %d\n", failPlay);
  //
  // // Since each card in players hand and deck was set to treasure, there should be cards remaning in deck after playing adventure.
  // if(state->deckCount[state->whoseTurn] > 0) {
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects deck to contain more than '0', after player plays adventurer with no cards in deck, got: %d\n", state->deckCount[state->whoseTurn]);
  //
  // if(state->discardCount[state->whoseTurn] == 0) {
  //   printf(PLAYREMODEL_PASS);
  // } else {
  //   printf(PLAYREMODEL_FAIL);
  // }
  // printf("expects discard to contain '0' cards, after player plays adventurer with no cards in deck, got: %d\n", state->discardCount[state->whoseTurn]);
  //













}

int main() {
  testPlayRemodel();
  return 0;
}
