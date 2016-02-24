#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dominion.h"

#define PLAYREMODEL_PASS "playRemodel() PASS: "
#define PLAYREMODEL_FAIL "playRemodel() FAIL: "


void testPlayRemodel() {
  int i = 0;

  int remodelHandCount = 0;
  int remodelDiscardCount = 0;
  int remodelPlayedCount = 0;

  int adventurerHandCount = 0;
  int adventurerDiscardCount = 0;
  int adventurerPlayedCount = 0;

  int treasureCount = 0;        // Starting treasure amount.
  int increasedTreasure = 0;    // Amount treasure increased.

  int otherHandIncrease = 0;
  int otherDeckIncrease = 0;
  int otherDiscardIncrease = 0;


  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, remodel, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();


  initializeGame(numPlayers, kingdomCards, randomSeed, state);      // Initialize game with valid game values.

  printf("\n***** TESTING PLAY REMODEL *****\n");

  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  otherHandIncrease = 0;
  otherDeckIncrease = 0;
  otherDiscardIncrease = 0;

  // Set player 1's first card in hand to be adventurer card.
  testGame->hand[testGame->whoseTurn][0] = remodel;
  testGame->hand[testGame->whoseTurn][1] = adventurer;
  int gardensDiscardCount = 0;

  int r = 0;
  //playRemodel(testGame, testGame->whoseTurn, 0, 1, 1);      // Trying to buy gardens by trashing a adventurer.
  cardEffect(remodel, 1,1,1, testGame, 0 ,&r);

  // See if any other players handsize increased, don't include player that played remodel.
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

  // Check what player has in hand after playing remodel.
  for(i = 0; i < numHandCards(testGame); i++) {
    if(testGame->hand[testGame->whoseTurn][i] == remodel) {        // There is a remodel in hand.
      remodelHandCount++;
    }

    if(testGame->hand[testGame->whoseTurn][i] == adventurer) {
      adventurerHandCount++;
    }

    // Count up # of treasures.
    if(testGame->hand[testGame->whoseTurn][i] == copper || testGame->hand[testGame->whoseTurn][i] == silver || testGame->hand[testGame->whoseTurn][i] == gold ) {
      increasedTreasure++;
    }
  }

  increasedTreasure = increasedTreasure - treasureCount;    // Determine total quantity treasure increased by.

  // Make sure player has no remodel cards in discard pile.
  for(i = 0; i < testGame->discardCount[testGame->whoseTurn]; i++) {
    if(testGame->discard[testGame->whoseTurn][i] == remodel) {        // There is a remodel in discard.
      remodelDiscardCount++;
    }

    if(testGame->discard[testGame->whoseTurn][i] == adventurer) {
      adventurerDiscardCount++;
    }

    if(testGame->discard[testGame->whoseTurn][i] == gardens) {        // See how many gardens are in discarded cards because we bought one.
      gardensDiscardCount++;
    }
  }

  // Make sure player has 1 remodel card in played card pile.
  for(i = 0; i < testGame->playedCardCount; i++) {
    if(testGame->playedCards[i] == remodel) {        // There is a remodel in played cards.
      remodelPlayedCount++;
    }

    if(testGame->playedCards[i] == adventurer) {
      adventurerPlayedCount++;
    }
  }

  // Player who played card.
  if(state->handCount[state->whoseTurn]-2 == testGame->handCount[testGame->whoseTurn]) {    // Discard remodel, trash another, gained card goes to discard pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'garden' by trashing a 'adventurer' to decrease handsize by a total of '2', 'hand' decreased by: %d\n", state->handCount[state->whoseTurn]-testGame->handCount[testGame->whoseTurn]);

  if(state->handCount[state->whoseTurn]-1 == testGame->handCount[testGame->whoseTurn]) {    // Action reduced by 1 the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'garden' by trashing a 'adventurer' to decrease actions by '1', 'actions' decreased by: %d\n", state->handCount[state->whoseTurn]-testGame->handCount[testGame->whoseTurn]);

  if(state->numBuys == testGame->numBuys) {    // Number of buys should still be 1.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'garden' by trashing a 'adventurer' to keep 'buy' amount at '1', got: %d\n", testGame->numBuys);

  if(remodelHandCount == 0) {    // No remodel in hand.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'garden' by trashing a 'adventurer' to no longer have 'remodel' cards in hand, got: %d\n", remodelHandCount);

  if(remodelPlayedCount == 1) {    // one remodel in played cards pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 'remodel' card in played card pile after playing it, got: %d\n", remodelPlayedCount);

  if(remodelDiscardCount == 0) {    // 0 remodel in discard because we are trying to buy a gardens.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 0 'remodel' cards in discard pile after playing it, got: %d\n", remodelDiscardCount);

  if(gardensDiscardCount == 1) {    // 1 gardens in discard because we bought a gardens.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 'gardens' card in discard pile after buying it, got: %d\n", gardensDiscardCount);

  if(testGame->playedCardCount == 1) {    // Only one card in played card pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have 1 card in played card pile after playing remodel, got: %d\n", testGame->playedCardCount);

  if(adventurerHandCount == 0) {    // Only one card in played card pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have no 'adventurer' cards in hand after selecting it to trash, number of adventurers in hand: %d\n", adventurerHandCount);

  if(adventurerDiscardCount == 0) {    // Only one card in played card pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have no 'adventurer' cards in discard after selecting it to trash, number of adventurers in hand: %d\n", adventurerDiscardCount);

  if(adventurerPlayedCount == 0) {    // Only one card in played card pile.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects Player 1 to have no 'adventurer' cards in played card pile after selecting it to trash, number of adventurers in played card pile: %d\n", adventurerPlayedCount);


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




  // Try buying a card thats to expensive
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  // Set player 1's first card in hand to be adventurer card.
  testGame->hand[testGame->whoseTurn][0] = remodel;
  testGame->hand[testGame->whoseTurn][1] = copper;

  r = 0;
  //cardEffect(remodel, 1,7,1, testGame, 0 ,&r);
  int succussfulRemodel = cardEffect(remodel, 1,7,1, testGame, 0 ,&r);      // Trying to buy adventurer by trashing a copper.

  if(testGame->handCount[testGame->whoseTurn] == state->handCount[state->whoseTurn]) {    // Make sure hand count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'adventurer' by trashing a 'copper', to not change hand size, hand size changed by: %d\n", testGame->handCount[testGame->whoseTurn]-state->handCount[state->whoseTurn]);

  if(testGame->deckCount[testGame->whoseTurn] == state->deckCount[state->whoseTurn]) {    // Make sure deck count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'adventurer' by trashing a 'copper', to not change deck size, deck size changed by: %d\n", testGame->deckCount[testGame->whoseTurn]-state->deckCount[state->whoseTurn]);

  if(testGame->discardCount[testGame->whoseTurn] == state->discardCount[state->whoseTurn]) {    // Make sure discard count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'adventurer' by trashing a 'copper', to not change discard pile size, discard pile size changed by: %d\n", testGame->discardCount[testGame->whoseTurn]-state->discardCount[state->whoseTurn]);

  if(succussfulRemodel == -1) {    // Make sure other players discard size doesn't increase.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'adventurer' by trashing a 'copper', to return '-1', got: %d\n", succussfulRemodel);




  // Try buying a card thats the exact amount affordable amount, garden is 4 so is feast.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  // Set player 1's first card in hand to be adventurer card.
  testGame->hand[testGame->whoseTurn][0] = remodel;
  testGame->hand[testGame->whoseTurn][1] = gardens;


  succussfulRemodel = cardEffect(remodel, 1,9,1, testGame, 0 ,&r);      // Trying to buy feast by trashing a garden.

  if(testGame->handCount[testGame->whoseTurn] == state->handCount[state->whoseTurn]-2) {    // Make sure hand count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'feast' by trashing a 'garden', to decrease handsize by 2, hand size changed by: %d\n", testGame->handCount[testGame->whoseTurn]-state->handCount[state->whoseTurn]);

  if(testGame->deckCount[testGame->whoseTurn] == state->deckCount[state->whoseTurn]) {    // Make sure deck count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'feast' by trashing a 'garden', to not increase deck size, deck size changed by: %d\n", testGame->deckCount[testGame->whoseTurn]-state->deckCount[state->whoseTurn]);

  if(testGame->discardCount[testGame->whoseTurn] == state->discardCount[state->whoseTurn]+2) {    // Make sure discard count stays the same.
    printf(PLAYREMODEL_PASS);
  } else {
    printf(PLAYREMODEL_FAIL);
  }
  printf("expects attempt to buy 'feast' by trashing a 'garden', to increase discard pile size by 2, discard pile size changed by: %d\n", testGame->discardCount[testGame->whoseTurn]-state->discardCount[state->whoseTurn]);


  // Clear memory
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;

}

int main() {
  testPlayRemodel();
  return 0;
}
