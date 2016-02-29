/* Random Tester for playSmithy
 * Requirements
 * 1. Current player receives 3 cards
 * 2. 3 Cards come from players own pile
 * 3. No state change should occur for other players
 * 4. No state change should occur to the victory/kingdom card piles
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
  int i, j;
  int cardTypes = 27;
  int newCards = 3;
  int discarded = 1;
  int handSize;
  int maxHandSize = 5;
  int handPos, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int numPlayers = 2;
  int thisPlayer = 0;
  int otherPlayer = 1;
  struct gameState G, testG;
  int k[10] = {adventurer, smithy, council_room, remodel, great_hall, mine,
      baron, feast, gardens, village};

  for (i = 1; i <= 1000; i++) {
    initializeGame(numPlayers, k, i, &G);
    handSize = rand() % maxHandSize + 1; //generate a hand size between 1 and 5
    handPos = rand() % handSize; // generate a hand position between 0 and handSize
    G.handCount[thisPlayer] = handSize;

    for (j = 0; j < maxHandSize; j++) {
      if (j < handSize) {
        G.hand[thisPlayer][j] = rand() % cardTypes;
      } else {
        G.hand[thisPlayer][j] = -1;
      }
    }

    printf("----------------- Test #: %d ----------------\n", i);
    printf("Testing handPos = %d, handSize = %d, card1 = %d, card2 = %d, card3 = %d, card4 = %d, card = %d\n", handPos, handSize, G.hand[thisPlayer][0], G.hand[thisPlayer][1], G.hand[thisPlayer][2], G.hand[thisPlayer][3], G.hand[thisPlayer][4]);
    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);

    printf("--- Current Player ---\n");
    printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
    assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);

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

  printf("\n >>>>> SUCCESS: Random Testing complete %s <<<<<\n\n", TESTCARD);

  return 0;
}