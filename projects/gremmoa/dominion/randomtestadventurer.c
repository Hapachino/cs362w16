/* Random Tester for playAdventurer
 * Requirements
 * 1. Current player adds 2 treasure cards to hand
 * 2. 2 treasure cards come from own deck
 * 3. 0-n amount of cards are drawn until 2 treasure cards have been revealed
 * 4. The non-treasure cards that were drawn are discarded
 * 5. No state change should occur for other players
 * 6. No state change should occur to the victory/kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
  int i, j;
  int card;
  int cardTypes = 27;
  int newCards = 2;
  int discarded = 1;
  int gameTreasureCount;
  int testGameTreasureCount;
  int handSize;
  int maxHandSize = 5;
  int discardSize = 3;
  int deckSize;
  int maxDeckSize = 5;
  int handPos, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  for (i = 1; i <= 1000; i++) {
    initializeGame(numPlayers, k, i, &G);
    gameTreasureCount = 0;
    testGameTreasureCount = 0;
    handSize = rand() % maxHandSize + 1; //generate a hand size between 1 and 5
    handPos = rand() % handSize; // generate a hand position between 0 and handSize
    deckSize = rand() % maxDeckSize + 1; // generate a discard size between 1 and 5
    G.handCount[thisPlayer] = handSize;
    G.deckCount[thisPlayer] = deckSize;

    for (j = 0; j < discardSize; j++) {
      G.discardCount[thisPlayer]++;
      G.discard[thisPlayer][j] = rand() % 3 + 4; //seed a discard pile position with copper, silver or gold
    }

    for (j = 0; j < maxHandSize; j++) {
      if (j < handSize) {
        G.hand[thisPlayer][j] = rand() % cardTypes;
      } else {
        G.hand[thisPlayer][j] = -1;
      }
    }

    for (j = 0; j < G.handCount[thisPlayer]; j++) {
      card = G.hand[thisPlayer][j];
      if (handPos != j && (card == 4 || card == 5 || card == 6)) {
        gameTreasureCount++;
      }
    }

    printf("----------------- Test #: %d ----------------\n", i);
    printf("Testing handPos = %d, handSize = %d, deckSize = %d, card1 = %d, card2 = %d, card3 = %d, card4 = %d, card = %d\n", handPos, handSize, deckSize, G.hand[thisPlayer][0], G.hand[thisPlayer][1], G.hand[thisPlayer][2], G.hand[thisPlayer][3], G.hand[thisPlayer][4]);
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

    for (j = 0; j < testG.handCount[thisPlayer]; j++) {
      card = testG.hand[thisPlayer][j];
      if (card == 4 || card == 5 || card == 6) {
        testGameTreasureCount++;
      }
    }

    printf("--- Current Player ---\n");
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count (%d) + discard count (%d) = %d, expected = %d\n", testG.deckCount[thisPlayer], testG.discardCount[thisPlayer], testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards);
    assert(testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] == G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards);

    printf("treasure count = %d, expected = %d\n", testGameTreasureCount, gameTreasureCount + newCards);
    assert(testGameTreasureCount == gameTreasureCount + newCards);

    printf("--- Other Player ---\n");
    printf("hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
    assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
    printf("deck count = %d, expected = %d\n", testG.deckCount[otherPlayer], G.deckCount[otherPlayer]);
    assert(testG.deckCount[otherPlayer] == G.deckCount[otherPlayer]);

    printf("--- Kingdom/Victory Pile ---\n");
    for (j = 0; j < cardTypes; j++) {
      printf("Card type %d count = %d, expected = %d\n", j, testG.supplyCount[j], G.supplyCount[j]);
      assert(testG.supplyCount[j] == G.supplyCount[j]);
    }
  }

  printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}