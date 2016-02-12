#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"

#define PLAYSMITHY_PASS "playSmithy() PASS: "
#define PLAYSMITHY_FAIL "playSmithy() FAIL: "

#define NUM_TESTS 1000

// Generates a random deck.
void randomDeck(struct gameState *state) {
  int i = 0;
  int randDeckSize = rand() % MAX_DECK + 1;       // Get random deck size.
  state->deckCount[state->whoseTurn] = randDeckSize;

  // Loop through each card in deck and initialize hand count.
  for(i = 0; i < state->deckCount[state->whoseTurn]; i++) {
    state->deck[state->whoseTurn][i] = copper;
  }
}

// Generates a random hand.
void randomHand(struct gameState *state) {
  int i = 0;
  int randHandSize = rand() % MAX_HAND + 1;
  state->handCount[state->whoseTurn] = randHandSize;

  // Loop through each card in hand and initialize hand count.
  for(i = 0; i < state->handCount[state->whoseTurn]; i++) {
    state->hand[state->whoseTurn][i] = copper;
  }
}

// Generates a random discard.
void randomDiscard(struct gameState *state) {
  int i = 0;
  int randDiscardSize = rand() % ((MAX_DECK - state->deckCount[state->whoseTurn])+1);     // Make sure we don't exceed total possible deck size.
  state->discardCount[state->whoseTurn] = randDiscardSize;

  // Loop through each card in hand and initialize hand count.
  for(i = 0; i < state->discardCount[state->whoseTurn]; i++) {
    state->discard[state->whoseTurn][i] = copper;
  }
}

// Sets random number of actions.
void randomActions(struct gameState *state) {
  state->numActions = rand() % 100;
}

// Sets random number of buys.
void randomBuys(struct gameState *state) {
  state->numBuys = rand() % 100;
}

// Sets random number of coins.
void randomCoins(struct gameState *state) {
  state->coins = rand() % 100;
}

// Sets random player.
void randomPlayer(struct gameState *state) {
  state->whoseTurn = rand() % state->numPlayers;
}


void testRandomCard() {
  int i = 0;
  int j = 0;
  int k = 0;

  int availableKingdomCards[20] = {
    adventurer,
    council_room,
    feast,
    gardens,
    mine,
    remodel,
    smithy,
    village,
    baron,
    great_hall,
    minion,
    steward,
    tribute,
    ambassador,
    cutpurse,
    embargo,
    outpost,
    salvager,
    sea_hag,
    treasure_map
  };

  int kingdomCards[10];
  int gameRandomSeed = -1;                      // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.

  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();
  int kingdomCardCount;
  int numPlayers = 0;

  for(i = 0; i < NUM_TESTS; i++) {

    // Change number of players.
    numPlayers = rand() % 3 + 2;                      // Generate random number between 2 and 4, we are testing playSmithy not create game so pick good values.
    kingdomCardCount = 0;

    // Fill kingdomCards array with random kingom cards.
    while(kingdomCardCount < sizeof(kingdomCards)/sizeof(int)) {
      int cardExists = 0;                             // Value to determine if the kingdom card exists yet or not.
      int randIndex = rand() % 20;                        // Random kingdom card index.

      for(k = 0; k < kingdomCardCount; k++) {          // Loop through each existing kingdom card and make sure the newly chosen one isn't already set as a kingdom card.
        if(kingdomCards[k] == availableKingdomCards[randIndex]) {     // Card already exists, set flag and break.
          cardExists = 1;
          break;
        }
      }

      if(cardExists == 1) {                           // Card exists so continue loop, don't add it to kingdom card array.
        continue;
      } else {
        kingdomCards[kingdomCardCount] = availableKingdomCards[randIndex];
        kingdomCardCount++;
      }
    }

    initializeGame(numPlayers, kingdomCards, gameRandomSeed, state);    // Initialize game with randomly generated game values.

    // randomPlayer(state);
    randomDeck(state);
    randomHand(state);
    randomDiscard(state);
    randomActions(state);         // Set random number of actions.
    randomBuys(state);            // Set random number of buys.
    randomCoins(state);           // Set random number of coins.

    int smithyIndex = rand() % 5;                                       // Randomize hand position smithy is in.
    memcpy(testGame, state, sizeof(struct gameState));                  // Setup clean test game.

    int statePlayer = state->whoseTurn;                                 // Create player variable.
    int testPlayer = testGame->whoseTurn;                               // Create player variable.

    playSmithy(state, statePlayer, smithyIndex);

    printf("\nGAME STATE: ");
    printf("Players - %d, Whose Turn - %d ", testGame->numPlayers, testGame->whoseTurn);
    printf("Handsize - %d, Smithy Hand Pos - %d ", testGame->handCount[testGame->whoseTurn], smithyIndex);
    printf("Deck Size - %d, Discard Size - %d ", testGame->deckCount[testGame->whoseTurn], testGame->discardCount[testGame->whoseTurn]);   // Print game condition tests are executing against.
    printf("Num Actions - %d, Num Buys - %d\n", testGame->numActions, testGame->numBuys);

    // TEST - Smithy draws 3 cards, but also the player discards smithy making net handsize gain only two.
    int handSizeIncrease = state->handCount[statePlayer] - testGame->handCount[testPlayer];       // Should equal 2.
    if(handSizeIncrease == 2) {
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d 'hand' size to increase by a total of '2', 'hand' increased by: %d\n", statePlayer+1, handSizeIncrease);

    // TEST - Deck count decreased by 3.
    if((testGame->deckCount[testPlayer]+testGame->discardCount[testPlayer]) < 3) {              // Deck should be 0 since total available cards to draw were less than 0.
      if(state->deckCount[statePlayer] == 0) {    // Smithy draws 3 cards so deck should decrease by 3.
        printf(PLAYSMITHY_PASS);
      } else {
        printf(PLAYSMITHY_FAIL);
      }
      printf("expects Player %d 'deck' size to be 0 when total cards in deck and discard is less than 3, 'deck' size: %d\n", statePlayer+1, state->deckCount[statePlayer]);

    } else {
      int deckCountDecrease = testGame->deckCount[testPlayer] - state->deckCount[statePlayer];
      if(deckCountDecrease == 3) {    // Smithy draws 3 cards so deck should decrease by 3.
        printf(PLAYSMITHY_PASS);
      } else {
        printf(PLAYSMITHY_FAIL);
      }
      printf("expects Player %d 'deck' size to decrease by a total of '3', 'deck' decreased by: %d\n", statePlayer+1, deckCountDecrease);
    }

    // TEST - Action reduced by 1.
    int actionDecrease = testGame->numActions - state->numActions;
    if(actionDecrease == 1) {    // Action reduced by 1.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d 'action' amount to decrease by '1', 'actions' decreased by: %d\n", statePlayer+1, actionDecrease);

    // TEST - Number of Buys not reduced.
    int buyDecrease = testGame->numBuys - state->numBuys;
    if(buyDecrease == 0) {    // Number of buys should still be 1.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d 'buy' amount to decrease by '0', 'buys' decreased by: %d\n", statePlayer+1, buyDecrease);

    // TEST - Number of Coins not changed.
    int coinDecrease = testGame->coins - state->coins;
    if(coinDecrease == 0) {         // 0 coin change.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d 'coins' to be the same after playing smithy, changed by: %d\n", statePlayer+1, coinDecrease);


    // TEST - Number of Smithy in hand after playing.
    int smithyHandCountAfter = 0;
    for(j = 0; j < state->handCount[statePlayer]; j++) {    // After playing
      if(state->hand[statePlayer][j] == smithy)             // Card is smithy.
        smithyHandCountAfter++;
    }
    int smithyHandCountBefore = 0;
    for(j = 0; j < testGame->handCount[statePlayer]; j++) {    // After playing
      if(testGame->hand[statePlayer][j] == smithy)             // Card is smithy.
        smithyHandCountBefore++;
    }
    if(smithyHandCountAfter == smithyHandCountBefore-1) {    // Smithy count should be 1 less.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d to have 1 less 'smithy' card in hand, has less: %d\n", statePlayer+1, smithyHandCountBefore - smithyHandCountAfter);

    // TEST - Number of smithy cards in played pile.
    int smithyPlayedCountAfter = 0;
    for(j = 0; j < state->playedCardCount; j++) {    // After playing
      if(state->playedCards[j] == smithy)             // Card is smithy.
        smithyPlayedCountAfter++;
    }
    int smithyPlayedCountBefore = 0;
    for(j = 0; j < testGame->playedCardCount; j++) {    // After playing
      if(testGame->playedCards[j] == smithy)             // Card is smithy.
        smithyPlayedCountBefore++;
    }
    if(smithyPlayedCountAfter == smithyPlayedCountBefore+1) {    // 1 smithy in played cards pile.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d to have 1 more 'smithy' card in played card pile, has more: %d\n", statePlayer+1, smithyPlayedCountAfter - smithyPlayedCountBefore);

    // TEST - Number of smithy cards in played pile.
    int smithyDiscardCountAfter = 0;
    for(j = 0; j < state->discardCount[statePlayer]; j++) {    // After playing
      if(state->discard[statePlayer][j] == smithy)             // Card is smithy.
        smithyPlayedCountAfter++;
    }
    int smithyDiscardCountBefore = 0;
    for(j = 0; j < testGame->discardCount[testPlayer]; j++) {    // After playing
      if(testGame->discard[testPlayer][j] == smithy)             // Card is smithy.
        smithyPlayedCountBefore++;
    }
    if(smithyDiscardCountAfter == smithyDiscardCountBefore) {    // 0 smithy in discard.
      printf(PLAYSMITHY_PASS);
    } else {
      printf(PLAYSMITHY_FAIL);
    }
    printf("expects Player %d to have 0 'smithy' cards in discard pile, has: %d\n", statePlayer+1, smithyDiscardCountAfter - smithyDiscardCountBefore);


    // Other players
    // TEST - Number of cards increased in other players hands, deck, discard.
    int otherHandIncrease = 0;
    int otherDeckIncrease = 0;
    int otherDiscardIncrease = 0;

    for(j = 1; j < state->numPlayers; j++) {
      if(testGame->handCount[j] > 0) {
        otherHandIncrease++;
      }
      if(testGame->deckCount[j] > 10) {
        otherDeckIncrease++;
      }
      if(testGame->discardCount[j] > 0) {
        otherDiscardIncrease++;
      }
    }

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

  // Free memory.
  free(state);
  state = 0;

  free(testGame);
  testGame = 0;
}


int main() {

  testRandomCard();

  return 0;
}
