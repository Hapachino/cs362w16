#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"

#define BUYCARD_PASS "buyCard() PASS: "
#define BUYCARD_FAIL "buyCard() FAIL: "


void testBuyCard() {
  int i = 0;                  // Initialize iterators.
  int j = 0;
  int k = 0;

  int successfulBuy = 0;
  int numBought = 0;
  int beforeDeckCount = 0;        // Variable to hold players deck count before any buys could have been made.
  int initialDiscardCount = 0;

  // Initilize game variables.
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
  int randomSeed = -1;                          // Set randomSeed to less than 0 so it is based off system clock in the initializeGame method.

  // Create game.
  struct gameState *state = newGame();          // Initialize game state.
  struct gameState *testGame = newGame();

  initializeGame(numPlayers, kingdomCards, randomSeed, state);       // Set game state to a 'clean' state.

  printf("\n***** TESTING BUY CARD *****\n");

  // BUY Kingdoms.
  // Kingdom - No buys
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.

  testGame->numBuys = 0;                                                // Set number of buys to 0.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    for (i = 0; k < 10; k++) {                                         // Try to buy each of kingdom cards available in supply.
      successfulBuy = buyCard(kingdomCards[k], testGame);
      if(successfulBuy > -1) {
        numBought++;
      }
    }

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a kingdom card with no buys available, Player %d's deck increased by: %d cards\n", j+1, numBought);
  }

  // Kingdom - No supply
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 50;                                               // Give suer plenty of buys to purchase with.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;

  // Set each Kingdom card supply to 0.
  for (i = adventurer; i <= treasure_map; i++)  {
    for (j = 0; j < 10; j++) {
      if (kingdomCards[j] == i) {
        testGame->supplyCount[i] = 0;
      }
    }
  }

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    for (i = 0; k < 10; k++) {                      // Try to buy each of kingdom cards available in supply.
      successfulBuy = buyCard(kingdomCards[k], testGame);
      if(successfulBuy > -1) {
        numBought++;
      }
    }

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a kingdom card with no supply available, Player %d's deck increased by: %d cards\n", j+1, numBought);
  }



  // Treasure - no buys
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 0;                                             // Set number of buys to 0.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;                                              // Reset buy counters.

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    // If any treasure buy was succesful increment counter. TODO: fix repetitive code.
    successfulBuy = buyCard(copper, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(silver, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(gold, testGame);
    if(successfulBuy > -1)
      numBought++;

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a treasure card with no buys available, Player %d's deck increased by: %d cards\n", j+1, beforeDeckCount-testGame->deckCount[j]);
  }

  // Treasure - no supply
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 50;                                               // Set number of buys.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;                                                    // Reset buy counters.

  // Set all treasure to 0.
  testGame->supplyCount[copper] = 0;
  testGame->supplyCount[silver] = 0;
  testGame->supplyCount[gold] = 0;

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    // If any treasure buy was succesful increment counter. TODO: fix repetitive code.
    successfulBuy = buyCard(copper, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(silver, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(gold, testGame);
    if(successfulBuy > -1)
      numBought++;

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a treasure card with no supply available, Player %d's deck increased by: %d cards\n", j+1, beforeDeckCount-testGame->deckCount[j]);
  }


  // Victory - no buys
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 0;                                                // Set number of buys to 0.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    // If any victory card buy was succesful increment counter. TODO: fix repetitive code.
    successfulBuy = buyCard(estate, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(duchy, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(province, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(curse, testGame);
    if(successfulBuy > -1)
      numBought++;

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a victory card with no buys available, Player %d's deck increased by: %d cards\n", j+1, beforeDeckCount-testGame->deckCount[j]);
  }

  // Victory - no supply
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 50;                                               // Set number of buys to 50.
  testGame->coins = 1000;                                              // Give user enough coins to buy.
  successfulBuy = 0;

  // Set all victory to 0.
  testGame->supplyCount[estate] = 0;
  testGame->supplyCount[duchy] = 0;
  testGame->supplyCount[province] = 0;
  testGame->supplyCount[curse] = 0;

  // Loop through each player in game to make sure no player's deck size increases from attempted buy.
  for(j = 0; j < numPlayers; j++) {
    numBought = 0;
    beforeDeckCount = testGame->deckCount[j];

    // If any victory card buy was succesful increment counter. TODO: fix repetitive code.
    successfulBuy = buyCard(estate, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(duchy, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(province, testGame);
    if(successfulBuy > -1)
      numBought++;
    successfulBuy = buyCard(curse, testGame);
    if(successfulBuy > -1)
      numBought++;

    if(beforeDeckCount == testGame->deckCount[j]) {
      printf(BUYCARD_PASS);
    } else {
      printf(BUYCARD_FAIL);
    }
    printf("expects Player %d's deck size to not increase when Player 1 ", j+1);
    printf("attempts to purchase a victory card with no supply available, Player %d's deck increased by: %d cards\n", j+1, beforeDeckCount-testGame->deckCount[j]);
  }
  // END




  // Test buying kingdom cards, make sure correct amount of coin is required.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 40;                                             // Set number of buys to 0.
  testGame->coins = 5000;
  int randomKingdomCard = 0;
  int beforeCoins = 0;

  successfulBuy = 0;            // Reset buy counters.
  numBought = 0;

  // Try to buy a bunch of random cards.
  for(i = 0; i < testGame->numBuys; i++) {
    randomKingdomCard = rand() % 10;
    beforeCoins = testGame->coins;                                         // Get coin total before purchase.
    buyCard(kingdomCards[randomKingdomCard], testGame);                    // Buy a random card.

    // Check what was bought.
    if (kingdomCards[randomKingdomCard] == curse) {                             // curse
      if (testGame->coins + 0 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'curse' to cost 0 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == estate) {                     // estate
      if (testGame->coins + 2 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'estate' to cost 2 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == duchy) {                      // duchy
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'duchy' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == province) {                   // province
      if (testGame->coins + 8 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'province' to cost 8 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == copper) {                     // copper
      if (testGame->coins + 8 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'copper' to cost 0 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == silver) {                     // silver
      if (testGame->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'silver' to cost 3 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == gold) {                       // gold
      if (testGame->coins + 6 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'gold' to cost 6 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == adventurer) {                 // adventurer
      if (testGame->coins + 6 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'adventurer' to cost 6 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == council_room) {               // council_room
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'council_room' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == feast) {                      // feast
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'feast' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == gardens) {                    // gardens
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'gardens' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == mine) {                       // mine
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'mine' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == remodel) {                    // remodel
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'remodel' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == smithy) {                     // smithy
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'smithy' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == village) {                    // village
      if (testGame->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'village' to cost 3 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == baron) {                      // baron
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'baron' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == great_hall) {                 // great_hall
      if (testGame->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'great_hall' to cost 3 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == minion) {                     // steward
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'minion' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == steward) {                    // steward
      if (testGame->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'steward' to cost 3 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == tribute) {                    // tribute
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'tribute' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == ambassador) {                 // ambassador
      if (testGame->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'ambassador' to cost 3 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == cutpurse) {                   // cutpurse
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'cutpurse' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == embargo) {                    // embargo
      if (testGame->coins + 2 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'embargo' to cost 2 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == outpost) {                    // outpost
      if (testGame->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'outpost' to cost 5 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == salvager) {                   // salvager
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'salvager' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == sea_hag) {                    // sea_hag
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'sea_hag' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    } else if (kingdomCards[randomKingdomCard] == treasure_map) {               // treasure_map
      if (testGame->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'treasure_map' to cost 4 coins, costs: %d", beforeCoins-testGame->coins);

    }
    printf("\n");

  } // End buy loop.
  // END


  // Test buying a card correctly decrements the number of buys from buying player.
  memcpy(testGame, state, sizeof(struct gameState));                    // Setup clean test game.
  testGame->numBuys = 5;                                                // Set number of buys to 5.
  testGame->coins = 500;

  int startingBuys = testGame->numBuys;
  int totalBuysMade = 0;

  // Use all buys.
  for (i = 0; i < startingBuys; i++)  {
    randomKingdomCard = rand() % 10;
    buyCard(kingdomCards[randomKingdomCard], testGame);              // Buy a random card.
    totalBuysMade++;
  }

  if(totalBuysMade != startingBuys) {                                  // Expected buys doesn't match actual made.
    printf(BUYCARD_FAIL);
    printf("expected to make '%d' buys, instead only made '%d' buys.\n", startingBuys, totalBuysMade);
  } else {
    printf(BUYCARD_PASS);
    printf("expected to make '%d' buys, made '%d' buys.\n", startingBuys, totalBuysMade);
  }
  // END


  // Test buying a card correctly sets the phase to '1' after a successful buy.
  initializeGame(numPlayers, kingdomCards, randomSeed, testGame);
  testGame->numBuys = 5;                                             // Set number of buys to 0.
  testGame->coins = 500;
  initialDiscardCount = testGame->discardCount[testGame->whoseTurn];

  // Buys.
  randomKingdomCard = rand() % 10;
  buyCard(kingdomCards[randomKingdomCard], testGame);              // Buy a random card.
  int discardIncrease = testGame->discardCount[testGame->whoseTurn]-initialDiscardCount;

  if(testGame->phase == 1) {                                  // Expected buys doesn't match actual made.
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expected to make buy to set phase to '1', phase now: %d\n", testGame->phase);

  if(discardIncrease == 1) {              // Discard count is increased by 1.
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expected buy to increase discard pile by 1, discard pile increased by: %d\n", discardIncrease);
  // END

}


int main() {
  testBuyCard();
  return 0;
}
