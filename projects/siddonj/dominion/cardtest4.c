#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dominion.h"

#define PLAYVILLAGE_PASS "playVillage() PASS: "
#define PLAYVILLAGE_FAIL "playVillage() FAIL: "


void testPlayVillage() {
  int i = 0;
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.

  int villageHandCount = 0;
  int villageDiscardCount = 0;
  int villagePlayedCount = 0;

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;

  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();


  initializeGame(numPlayers, kingdomCards, randomSeed, state);

  printf("\n***** TESTING PLAY VILLAGE *****\n");


  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  // Set player 1's first card in hand to be village card.
  testGame->hand[testGame->whoseTurn][0] = village;

  playVillage(testGame, testGame->whoseTurn, 0);         // First card is village;

  // See if any other players handsize increased, don't include player that played village.
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

  // Make sure player has no more village cards in hand since we only added one to their hand.
  for(i = 0; i < numHandCards(testGame); i++) {
    if(testGame->hand[testGame->whoseTurn][i] == village) {        // There is a village in hand.
      villageHandCount++;
    }
  }

  // Make sure player has no village cards in discard pile.
  for(i = 0; i < testGame->discardCount[testGame->whoseTurn]; i++) {
    if(testGame->discard[testGame->whoseTurn][i] == village) {        // There is a village in discard.
      villageDiscardCount++;
    }
  }

  // Make sure player has 1 village card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == village) {        // There is a village in played cards.
      villagePlayedCount++;
    }
  }

  // Player who played card.
  if(testGame->handCount[testGame->whoseTurn] == state->handCount[state->whoseTurn]) {    // village draws 1 cards, but also the player discards village making net handsize gain 0.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1's 'hand' size to increase by a total of '0', 'hand' increased by: %d\n", testGame->handCount[testGame->whoseTurn]-state->handCount[state->whoseTurn]);

  if(testGame->numActions == state->numActions+2) {    // Action increase 2.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1's 'action' amount to increase by '2', 'actions' increased by: %d\n", testGame->numActions-state->numActions);

  if(testGame->numBuys == 1) {    // Number of buys should still be 1.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1's 'buy' amount to be '1', got: %d\n", testGame->numBuys);

  if(villageHandCount == 0) {    // No village in hand.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1 to have 0 'village' cards in hand, got: %d\n", villageHandCount);

  if(villagePlayedCount == 1) {    // 1 village in played cards pile.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1 to have 1 'village' card in played card pile, got: %d\n", villagePlayedCount);

  if(villageDiscardCount == 0) {    // 0 village in discard.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1 to have 0 'village' cards in discard pile, got: %d\n", villageDiscardCount);

  if(testGame->coins == state->coins) {         // 0 coin change.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects Player 1 'coins' to be the same after playing village, changed by: %d\n", testGame->coins-state->coins);

  // Other players
  if(otherHandIncrease == 0) {    // Make sure other players hand size doesn't increase.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects other player's 'hand' size to not increase, other player's 'hands' increased by: %d\n", otherHandIncrease);

  if(otherDeckIncrease == 0) {    // Make sure other players deck size doesn't increase.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects other player's 'deck' size to not increase, other player's 'decks' increased by: %d\n", otherDeckIncrease);

  if(otherDiscardIncrease == 0) {    // Make sure other players discard size doesn't increase.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects other player's 'discard' size to not increase, other player's 'discard' pile increased by: %d\n", otherDiscardIncrease);



  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  // Set player 1's first card in hand to be copper card.
  testGame->hand[testGame->whoseTurn][0] = copper;

  playVillage(testGame, testGame->whoseTurn, 0);         // First card is copper, not village;

  if(state->numActions == testGame->numActions) {    // Players actions shouldn't update.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects player's 'actions' to not increase when they select a card to play that isn't a village, actions increased by: %d\n", testGame->numActions-state->numActions);


  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  // Clear deck
  testGame->discard[testGame->whoseTurn][0] = testGame->hand[testGame->whoseTurn][0];
  testGame->discardCount[testGame->whoseTurn] = 1;
  testGame->deckCount[testGame->whoseTurn] = 0;

  testGame->hand[testGame->whoseTurn][0] = village;

  playVillage(testGame, testGame->whoseTurn, 0);         // First card is copper, not village;

  if(state->discardCount[state->whoseTurn] == testGame->discardCount[testGame->whoseTurn]) {    // Players actions shouldn't update.
    printf(PLAYVILLAGE_PASS);
  } else {
    printf(PLAYVILLAGE_FAIL);
  }
  printf("expects player's 'discard' to contain 0 cards when they play a village with not cards in deck and 1 card in discard, discard pile is: %d\n", testGame->discardCount[testGame->whoseTurn]);



  // Free memory
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;


}

int main() {
  testPlayVillage();
  return 0;
}
