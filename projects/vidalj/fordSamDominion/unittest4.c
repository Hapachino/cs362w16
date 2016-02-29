/* Test the updateCoins() function
   NOTE: It's not entirely clear to me what exactly updateCoins() should do.
   Every single treasure card in a player's hand is played upon execution, so
   it would seem like this function only has the purpose of playing the
   player's treasure cards.  I wouldn't except a more general-purpose function
   to update coins to reset the coin count upon execution, so I'm merely
   testing to ensure that the updateCoins function works in a predictable
   fashion according to how it was designed (whatever its real purpose may be).

   It may be that updateCoins() should also be calling discardCard() on each
   played treasure card (to move it to the playedCards pile) but it's unclear
   what the precise use case of updateCoins() is at this point.
*/
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "fordsamTest.h"

#define P1 0

void testUpdateCoins() {
  int passCount = 0;
  int testCount = 0;
  int result = 0;
  struct gameState initialState = {0};
  struct gameState state = {0};
  struct gameState preState = {0};
  struct gameStateComparison gsc = {0};

  printf("----- Testing updateCoins() -----\n");

  /* Test updateCoins() with a handCount of 0 */
  printf("----- Test: coins = 0, handCount = 0, hand has 3 treasure cards\n");
  state.coins = 0;
  state.hand[P1][0] = copper;
  state.hand[P1][1] = remodel;
  state.hand[P1][2] = silver;
  state.hand[P1][3] = adventurer;
  state.hand[P1][4] = gold;
  state.handCount[P1] = 0;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = updateCoins(P1, &state, 0);

  /* Should not modify state when handCount == 0 */
  testCount += 1;
  passCount += fakeAssert(
    "Should not modify state when handCount == 0",
    (compareState(&state, &preState, &gsc) == 0)
  );

  /* Test a hand with only a copper */
  printf("\n----- Test: coins = 0, handCount = 1, hand has copper\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.hand[P1][0] = copper;
  state.handCount[P1] = 1;
  result = updateCoins(P1, &state, 0);

  /* Should add 1 coin for a copper */
  testCount += 1;
  passCount += fakeAssert(
    "Should add 1 coin for a copper",
    (state.coins == 1)
  );

  /* Test a hand with only a silver */
  printf("\n----- Test: coins = 0, handCount = 1, hand has silver\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.hand[P1][0] = silver;
  state.handCount[P1] = 1;
  result = updateCoins(P1, &state, 0);

  /* Should add 2 coins for a silver */
  testCount += 1;
  passCount += fakeAssert(
    "Should add 2 coins for a silver",
    (state.coins == 2)
  );

  /* Test a hand with only a gold */
  printf("\n----- Test: coins = 0, handCount = 1, hand has gold\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.hand[P1][0] = gold;
  state.handCount[P1] = 1;
  result = updateCoins(P1, &state, 0);

  /* Should add 3 coins for a gold */
  testCount += 1;
  passCount += fakeAssert(
    "Should add 3 coins for a gold",
    (state.coins == 3)
  );

  /* Test an empty hand with a bonus */
  printf("\n----- Test: coins = 0, handCount = 0, bonus = 5\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.handCount[P1] = 0;
  result = updateCoins(P1, &state, 5);

  /* Should add the passed bonus to coins */
  testCount += 1;
  passCount += fakeAssert(
    "Should add the passed bonus to coins",
    (state.coins == 5)
  );

  /* Test a hand with a treasure card while adding a bonus */
  printf(
    "\n----- Test: coins = 0, handCount = 1, hand has copper, bonus = 5\n"
  );
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.hand[P1][0] = copper;
  state.handCount[P1] = 1;
  result = updateCoins(P1, &state, 5);

  /* Should add treasure cards AND bonus to coins */
  testCount += 1;
  passCount += fakeAssert(
    "Should add treasure cards AND bonus to coins",
    (state.coins == 6)
  );

  /* Test adding to an existing coin count */
  printf("\n----- Test: coins = 5, handCount = 1, hand has copper\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 5;
  state.hand[P1][0] = copper;
  state.handCount[P1] = 1;
  memcpy(&preState, &state, sizeof(struct gameState));
  result = updateCoins(P1, &state, 0);

  /* Should preserve any pre-existing coins while adding */
  testCount += 1;
  passCount += fakeAssert(
    "Should preserve any pre-existing coins",
    (state.coins == preState.coins + 1)
  );

  /* Test a hand with a variety of treasure/non-treasure cards */
  printf("\n----- Test: coins = 0, handCount = 7, hand has gold, silver,");
  printf(" and 2x copper\n");
  memcpy(&state, &initialState, sizeof(struct gameState));
  state.coins = 0;
  state.hand[P1][0] = gold;
  state.hand[P1][1] = baron;
  state.hand[P1][2] = cutpurse;
  state.hand[P1][3] = copper;
  state.hand[P1][4] = estate;
  state.hand[P1][5] = silver;
  state.hand[P1][6] = copper;
  state.handCount[P1] = 7;
  result = updateCoins(P1, &state, 0);

  /* Should properly handle both treasure and non-treasure cards */
  testCount += 1;
  passCount += fakeAssert(
    "Should ignore non-treasure cards in player's hand",
    (state.coins == 7)
  );

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);
}

int main() {
  testUpdateCoins();
  return 0;
}
