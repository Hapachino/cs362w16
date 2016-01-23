


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dominion.h"

#define BUYCARD_PASS "buyCard() PASS: "
#define BUYCARD_FAIL "buyCard() FAIL: "

// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state) {

void testBuyCard() {
  int i = 0;                  // Initialize iterators.
  int j = 0;

  int successfulBuy = 0;
  int numBought = 0;

  // Initilize game variables.
  int numPlayers = 2;
  int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
  int randomSeed = 3;

  // Create game.
  struct gameState *state = newGame();          // Initialize game state.

  srand(time(NULL));

  // Test buying kingdom card with no buys available.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);
  state->numBuys = 0;                                             // Set number of buys to 0.

  successfulBuy = 0;
  numBought = 0;

  for (i = 0; i < 10; i++) {                      // Try to buy any card available in supply.
    successfulBuy = buyCard(kingdomCards[i], state);
    if(successfulBuy > -1) {
      numBought++;
    }
  }

  // Check no buy was successful.
  if (successfulBuy == -1) {
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expects player be unable to buy a kingdom card with 0 'buys', bought: ");
  printf("%d", numBought);
  printf(" cards.\n");
  // END


  // Test buying kingdom card with no supply available.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);
  state->numBuys = 3;                                             // Set number of buys to 0.
  state->coins = 30;

  successfulBuy = 0;
  numBought = 0;

  // Set each Kingdom card to 0.
  for (i = adventurer; i <= treasure_map; i++)  {
    for (j = 0; j < 10; j++) {
      if (kingdomCards[j] == i) {
	      state->supplyCount[i] = 0;
		  }
    }
  }

  for (i = 0; i < 10; i++) {                      // Try to buy any card available in supply.
    successfulBuy = buyCard(kingdomCards[i], state);
    if(successfulBuy > -1) {
      numBought++;
    }
  }

  // Check no buy was successful.
  if (successfulBuy == -1) {
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expects player be unable to buy a kingdom card with 0 'supply' of any card available, bought: ");
  printf("%d", numBought);
  printf(" cards.\n");
  // END


  // Test buying treasure card with no buys available.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Reset game to starting state.
  state->numBuys = 0;                                             // Set number of buys to 0.

  successfulBuy = 0;            // Reset buy counters.
  numBought = 0;

  // Try to buy each type of treasure.
  successfulBuy = buyCard(copper, state);             // Buy copper.
  if (successfulBuy == -1) {
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expects player be unable to buy 'copper' card with 0 'buys'.\n");


  // Test buying treasure with no supply available.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Reset game to starting state.
  state->numBuys = 3;                                             // Set number of buys to 0.
  state->supplyCount[copper] = 0;

  successfulBuy = 0;            // Reset buy counters.
  numBought = 0;

  // Try to buy each type of treasure.
  successfulBuy = buyCard(copper, state);             // Buy copper.
  if (successfulBuy == -1) {
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expects player be unable to buy 'copper' with 0 supply available.\n");


  // Test buying treasure with no supply available.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Reset game to starting state.
  state->numBuys = 3;                                             // Set number of buys to 0.
  state->supplyCount[copper] = 0;

  successfulBuy = 0;            // Reset buy counters.
  numBought = 0;

  // Try to buy each type of treasure.
  successfulBuy = buyCard(copper, state);             // Buy copper.
  if (successfulBuy == -1) {
    printf(BUYCARD_PASS);
  } else {
    printf(BUYCARD_FAIL);
  }
  printf("expects player be unable to buy 'copper' with 0 supply available.\n");


  // Test buying kingdom cards, make sure correct amount of coin is required.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);    // Reset game to starting state.
  state->numBuys = 40;                                             // Set number of buys to 0.
  state->coins = 1000;
  int randomKingdomCard = 0;
  int beforeCoins = 0;

  successfulBuy = 0;            // Reset buy counters.
  numBought = 0;

  // Try to buy a bunch of random cards.
  for(i = 0; i < state->numBuys; i++) {
    randomKingdomCard = rand() % 9;
    beforeCoins = state->coins;                                         // Get coin total before purchase.
    buyCard(kingdomCards[randomKingdomCard], state);                    // Buy a random card.

    // Check what was bought.
    if (kingdomCards[randomKingdomCard] == curse) {                             // curse
      if (state->coins + 0 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'curse' to cost 0 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == estate) {                     // estate
      if (state->coins + 2 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'estate' to cost 2 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == duchy) {                      // duchy
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'duchy' to cost 5 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == province) {                   // province
      if (state->coins + 8 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'province' to cost 8 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == copper) {                     // copper
      if (state->coins + 8 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'copper' to cost 0 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == silver) {                     // silver
      if (state->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'silver' to cost 3 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == gold) {                       // gold
      if (state->coins + 6 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'gold' to cost 6 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == adventurer) {                 // adventurer
      if (state->coins + 6 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'adventurer' to cost 6 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == council_room) {               // council_room
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'council_room' to cost 5 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == feast) {                      // feast
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'feast' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == gardens) {                    // gardens
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'gardens' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == mine) {                       // mine
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'mine' to cost 5 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == remodel) {                    // remodel
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'remodel' to cost 4 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == smithy) {                     // smithy
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'smithy' to cost 4 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == village) {                    // village
      if (state->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'village' to cost 3 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == baron) {                      // baron
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'baron' to cost 4 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == great_hall) {                 // great_hall
      if (state->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'great_hall' to cost 3 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == minion) {                     // steward
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'minion' to cost 5 coins, instead costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == steward) {                    // steward
      if (state->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'steward' to cost 3 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == tribute) {                    // tribute
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'tribute' to cost 5 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == ambassador) {                 // ambassador
      if (state->coins + 3 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'ambassador' to cost 3 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == cutpurse) {                   // cutpurse
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'cutpurse' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == embargo) {                    // embargo
      if (state->coins + 2 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'embargo' to cost 2 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == outpost) {                    // outpost
      if (state->coins + 5 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'outpost' to cost 5 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == salvager) {                   // salvager
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'salvager' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == sea_hag) {                    // sea_hag
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'sea_hag' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    } else if (kingdomCards[randomKingdomCard] == treasure_map) {               // treasure_map
      if (state->coins + 4 != beforeCoins) {
        printf(BUYCARD_FAIL);
      } else {
        printf(BUYCARD_PASS);
      }
      printf("expects purchasing a 'treasure_map' to cost 4 coins, costs: ");
      printf("%d", beforeCoins-state->coins);

    }
    printf("\n");

  } // End buy loop.
  // END


  // Test buying a card correctly decrements the number of buys.
  initializeGame(numPlayers, kingdomCards, randomSeed, state);
  state->numBuys = 5;                                             // Set number of buys to 0.
  state->coins = 40;

  int startingBuys = state->numBuys;
  int totalBuysMade = 0;

  // Use all buys.
  for (i = 0; i < startingBuys; i++)  {
    randomKingdomCard = rand() % 9;
    buyCard(kingdomCards[randomKingdomCard], state);              // Buy a random card.
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





}


int main() {
  testBuyCard();
  return 0;
}
