#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dominion.h"

#define PLAYADVENTURER_PASS "playAdventurer() PASS: "
#define PLAYADVENTURER_FAIL "playAdventurer() FAIL: "

#define NUM_TESTS 10000

int randomTreasure() {
  return rand() % 3 + 4;
}

int randomCard() {
  return rand() % 27;
}

// Generates a random deck.
void randomDeck(struct gameState *state) {
  int i = 0;
  int randDeckSize = rand() % (MAX_DECK+1);       // Get random deck size.
  state->deckCount[state->whoseTurn] = randDeckSize;

  if(randDeckSize == 0 || randDeckSize % 9 == 0) {
    // Do nothing.
  } else if(randDeckSize % 3 == 0) {
    for(i = 0; i < state->deckCount[state->whoseTurn]; i++) {
      state->deck[state->whoseTurn][i] = randomTreasure();
    }
  } else if(randDeckSize % 2 == 0) {
    for(i = 0; i < state->deckCount[state->whoseTurn]; i++) {
      state->deck[state->whoseTurn][i] = randomCard();
    }
  }

}

// Generates a random hand.
void randomHand(struct gameState *state) {
  int i = 0;
  int currentCardInPlayTotal = state->deckCount[state->whoseTurn];

  int randHandSize = rand() % ((MAX_HAND+1) - currentCardInPlayTotal);  // Make sure we don't exceed total possible cards in play.
  state->handCount[state->whoseTurn] = randHandSize;

  if(randHandSize == 0 || randHandSize % 9 == 0) {
    // Do nothing.
  } else if(randHandSize % 3 == 0) {
    for(i = 0; i < state->handCount[state->whoseTurn]; i++) {         // Fill hand with treasure.
      state->hand[state->whoseTurn][i] = randomTreasure();
    }
  } else if(randHandSize % 2 == 0) {
    for(i = 0; i < state->handCount[state->whoseTurn]; i++) {         // Fill hand with random cards.
      state->hand[state->whoseTurn][i] = randomCard();
    }
  }
}

// Generates a random discard.
void randomDiscard(struct gameState *state) {
  int i = 0;
  int currentCardInPlayTotal = state->deckCount[state->whoseTurn] + state->handCount[state->whoseTurn];

  int randDiscardSize = rand() % ((MAX_DECK+1) - currentCardInPlayTotal);     // Make sure we don't exceed total possible deck size.
  state->discardCount[state->whoseTurn] = randDiscardSize;

  if(randDiscardSize == 0 || randDiscardSize % 9 == 0) {
    // Do nothing.
  } else if(randDiscardSize % 3 == 0) {
    for(i = 0; i < state->discardCount[state->whoseTurn]; i++) {
      state->discard[state->whoseTurn][i] = randomTreasure();             // Fill discard with treature. copper, silver, gold.
    }
  } else if(randDiscardSize % 2 == 0) {
    for(i = 0; i < state->discardCount[state->whoseTurn]; i++) {
      state->discard[state->whoseTurn][i] = randomCard();                // Fill discard with and random card.
    }
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

// Sets random number of coins.
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
    adventurer,
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
    numPlayers = rand() % 3 + 2;                      // Generate random number between 2 and 4, we are testing playAdventurer not create game so pick good values.
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

    randomPlayer(state);          // Set player.
    randomDeck(state);
    randomHand(state);
    randomDiscard(state);
    randomActions(state);         // Set random number of actions.
    randomBuys(state);            // Set random number of buys.
    randomCoins(state);           // Set random number of coins.

    memcpy(testGame, state, sizeof(struct gameState));                  // Setup clean test game.

    int statePlayer = state->whoseTurn;                                 // Create player variable.
    int testPlayer = testGame->whoseTurn;                               // Create player variable.

    printf("\nGAME STATE: ");
    printf("Players - %d, Whose Turn - %d ", testGame->numPlayers, testPlayer+1);
    printf("Handsize - %d ", testGame->handCount[testPlayer]);
    printf("Deck Size - %d, Discard Size - %d ", testGame->deckCount[testPlayer], testGame->discardCount[testPlayer]);   // Print game condition tests are executing against.
    printf("Num Actions - %d, Num Buys - %d\n", testGame->numActions, testGame->numBuys);

    int successfullyPlayed = playAdventurer(state, statePlayer);   // Play adventurer.

    // TEST - Playing adventurer fails when player has 0 adventurer cards in hand.
    int numAdventurerCardsHand = 0;
    for(j = 0; j < testGame->handCount[testPlayer]; j++) {
      numAdventurerCardsHand++;
    }
    if((numAdventurerCardsHand == 0 && successfullyPlayed != 0) || (numAdventurerCardsHand > 0 && successfullyPlayed == 0))  {
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects playing adventurer to fail when player has 0 adventurer cards in hand, adventurer cards in hand: %d, success play?: %s\n", numAdventurerCardsHand, successfullyPlayed == 0 ? "yes" : "no");



    // TEST - Adventurer puts 2 treasure cards in a players hand.
    int beforeHandTreasure = 0;
    int beforeDeckTreasure = 0;
    int beforeDiscardTreasure = 0;
    int afterHandTreasure = 0;

    //Check how many treasures was in player's hand.
    for(j = 0; j < numHandCards(testGame); j++) {
      // Count up # of treasures.
      if(testGame->hand[testPlayer][j] == copper || testGame->hand[testPlayer][j] == silver || testGame->hand[testPlayer][j] == gold ) {
        beforeHandTreasure++;
      }
    }
    // Count up total number of treasures that was made available in game, if treasure is 1 or less, than player will only draw 1.
    // Check how many treasures was in player's deck.
    for(j = 0; j < testGame->deckCount[testPlayer]; j++) {
      // Count up # of treasures.
      if(testGame->deck[testPlayer][j] == copper || testGame->deck[testPlayer][j] == silver || testGame->deck[testPlayer][j] == gold ) {
        beforeDeckTreasure++;
      }
    }

    // Check how many treasures was in player's discard.
    for(j = 0; j < testGame->discardCount[testPlayer]; j++) {
      // Count up # of treasures.
      if(testGame->discard[testPlayer][j] == copper || testGame->discard[testPlayer][j] == silver || testGame->discard[testPlayer][j] == gold ) {
        beforeDiscardTreasure++;
      }
    }

    int totalTreasuresAvailable = beforeDeckTreasure + beforeDiscardTreasure;

    //Check how many treausres are now in player's hand.
    for(j = 0; j < numHandCards(state); j++) {
      // Count up # of treasures.
      if(state->hand[statePlayer][j] == copper || state->hand[statePlayer][j] == silver || state->hand[statePlayer][j] == gold ) {
        afterHandTreasure++;
      }
    }
    int treasureIncrease = afterHandTreasure - beforeHandTreasure;       // Should equal 2.
    if(treasureIncrease == 2 || totalTreasuresAvailable <= 1) {       // Treasure should have increased by 2 unless there was only 1 treasure available.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d in hand treasure total to increase by '%d', treasure increased by: %d\n", statePlayer+1, totalTreasuresAvailable>1 ? 2 : 1,treasureIncrease);

    // TEST - Adventurer puts 2 treasure cards in a players hand, net handsize increase is 1, if less than 2 treasrues in deck, suffle discard into deck.
    int handSizeIncrease = state->handCount[statePlayer] - testGame->handCount[testPlayer];       // Should equal 1.
    if(handSizeIncrease == 1) {       // If deck
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d 'hand' size to increase by '2', hand increased by: %d\n", statePlayer+1, handSizeIncrease);

    // TEST - Deck count decreases. IF Deck == 0 Special condition.
    int deckCountDecrease = testGame->deckCount[testPlayer] - state->deckCount[statePlayer];
    if(testGame->deckCount[testPlayer] <= 1) {  // No cards or not enough to draw two treasures when adventurer was played so the amount decreased will be negative.
      if(deckCountDecrease < 0) {
        printf(PLAYADVENTURER_PASS);
      } else {
        printf(PLAYADVENTURER_FAIL);
      }
      printf("expects Player %d 'deck' size to increase when playing adventurer with 0 cards in deck, deck increased by: %d\n", statePlayer+1, ((deckCountDecrease)*(-1)));
    } else {                          // Player had cards in deck when adventurer played.
      if(deckCountDecrease > 0) {    // Adventurer draws cards until 2 treasures.
        printf(PLAYADVENTURER_PASS);
      } else {
        printf(PLAYADVENTURER_FAIL);
      }
      printf("expects Player %d 'deck' size to decrease when playing adventurer, deck decreased by: %d\n", statePlayer+1, deckCountDecrease);
    }


    // TEST - Discard count increases by 2 less than deck decreases. IF Deck == 0 Special condition.
    int discardCountIncrease = state->discardCount[statePlayer] - testGame->discardCount[testPlayer];
    if(discardCountIncrease+2 == deckCountDecrease) {
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d 'discard' size to increase by 2 less than deck decreased, discard increased: %d\n", statePlayer+1, deckCountDecrease-discardCountIncrease);


    // TEST - Action reduced by 1.
    int actionDecrease = testGame->numActions - state->numActions;
    if(actionDecrease == 1) {    // Action reduced by 1.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d 'action' amount to decrease by '1', actions decreased by: %d\n", statePlayer+1, actionDecrease);

    // TEST - Number of Buys not reduced.
    int buyDecrease = testGame->numBuys - state->numBuys;
    if(buyDecrease == 0) {    // Number of buys should still be 1.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d 'buy' amount to decrease by '0', buys decreased by: %d\n", statePlayer+1, buyDecrease);

    // TEST - Number of Coins not changed.
    int coinDecrease = testGame->coins - state->coins;
    if(coinDecrease == 0) {         // 0 coin change.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d 'coins' to be the same after playing adventurer, coins changed by: %d\n", statePlayer+1, coinDecrease);


    // TEST - Number of Adventurer in hand after playing.
    int adventurerHandCountAfter = 0;
    for(j = 0; j < state->handCount[statePlayer]; j++) {    // After playing
      if(state->hand[statePlayer][j] == adventurer)             // Card is adventurer.
        adventurerHandCountAfter++;
    }
    int adventurerHandCountBefore = 0;
    for(j = 0; j < testGame->handCount[statePlayer]; j++) {    // After playing
      if(testGame->hand[statePlayer][j] == adventurer)             // Card is adventurer.
        adventurerHandCountBefore++;
    }
    if(adventurerHandCountAfter == adventurerHandCountBefore-1) {    // Adventurer count should be 1 less.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d to have 1 less 'adventurer' card in hand, decreased by: %d\n", statePlayer+1, adventurerHandCountBefore - adventurerHandCountAfter);

    // TEST - Number of adventurer cards in played pile.
    int adventurerPlayedCountAfter = 0;
    for(j = 0; j < state->playedCardCount; j++) {    // After playing
      if(state->playedCards[j] == adventurer)             // Card is adventurer.
        adventurerPlayedCountAfter++;
    }
    int adventurerPlayedCountBefore = 0;
    for(j = 0; j < testGame->playedCardCount; j++) {    // After playing
      if(testGame->playedCards[j] == adventurer)             // Card is adventurer.
        adventurerPlayedCountBefore++;
    }
    if(adventurerPlayedCountAfter == adventurerPlayedCountBefore+1) {    // 1 adventurer in played cards pile.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d to have 1 additional 'adventurer' card in played card pile, additional adventurers: %d\n", statePlayer+1, adventurerPlayedCountAfter - adventurerPlayedCountBefore);

    // TEST - Number of adventurer cards in played pile.
    int adventurerDiscardCountAfter = 0;
    for(j = 0; j < state->discardCount[statePlayer]; j++) {    // After playing
      if(state->discard[statePlayer][j] == adventurer)             // Card is adventurer.
        adventurerPlayedCountAfter++;
    }
    int adventurerDiscardCountBefore = 0;
    for(j = 0; j < testGame->discardCount[testPlayer]; j++) {    // After playing
      if(testGame->discard[testPlayer][j] == adventurer)             // Card is adventurer.
        adventurerPlayedCountBefore++;
    }
    if(adventurerDiscardCountAfter == adventurerDiscardCountBefore) {    // 0 adventurer in discard.
      printf(PLAYADVENTURER_PASS);
    } else {
      printf(PLAYADVENTURER_FAIL);
    }
    printf("expects Player %d to have 0 'adventurer' cards in discard pile, adventurers in discard: %d\n", statePlayer+1, adventurerDiscardCountAfter - adventurerDiscardCountBefore);


    // Other players
    // TEST - Number of cards increased in other players hands, deck, discard.
    int otherHandIncrease = 0;
    int otherDeckIncrease = 0;
    int otherDiscardIncrease = 0;

    for(j = 0; j < state->numPlayers; j++) {
      if(j != statePlayer) {                                // Make sure we aren't counting the current player's increase.
        if(testGame->handCount[j] - state->handCount[j] != 0) {
          otherHandIncrease++;
        }
        if(testGame->deckCount[j] - state->deckCount[j] != 0) {
          otherDeckIncrease++;
        }
        if(testGame->discardCount[j] - state->discardCount[j] != 0) {
          otherDiscardIncrease++;
        }
      }
    }

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
