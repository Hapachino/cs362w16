/* Paul Zotz
 * CS 362 Winter 2016
 * Assignment 3 - unit test 3 - gainCard()
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int returnVal;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int toDeck = 1;
    int toHand = 2;
    int toDiscard = 0;
    int currentPlayer = 0;

    // int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
    printf ("TESTING gainCard:\n");
    initializeGame(numPlayer, k, seed, &G);

    // test 1 - current player gains estate to deck
    memcpy(&testG, &G, sizeof(struct gameState));
    returnVal = gainCard(estate, &testG, toDeck, currentPlayer);
#if (NOISY_TEST == 1)
    printf("\n");
    printf("Current player gains estate to deck\n");
    printf("Return value: %d, expected: %d\n", returnVal, 0);
    printf("Current player deck count: %d, expected: %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] + 1);
    printf("Current player newest card to deck: %d, expected: %d\n", testG.deck[currentPlayer][G.deckCount[currentPlayer]], estate);
    printf("Estate supply count: %d, expected: %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
#endif
    assert(returnVal == 0);
    assert(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] + 1);
    assert(testG.deck[currentPlayer][G.deckCount[currentPlayer]] == estate);
    assert(testG.supplyCount[estate] == G.supplyCount[estate] - 1);

    // test 2 - current player gains estate to hand
    memcpy(&testG, &G, sizeof(struct gameState));
    returnVal = gainCard(estate, &testG, toHand, currentPlayer);
#if (NOISY_TEST == 1)
    printf("\n");
    printf("Current player gains estate to hand\n");
    printf("Return value: %d, expected: %d\n", returnVal, 0);
    printf("Current player hand count: %d, expected: %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1);
    printf("Current player newest card to hand: %d, expected: %d\n", testG.hand[currentPlayer][G.handCount[currentPlayer]], estate);
    printf("Estate supply count: %d, expected: %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
#endif
    assert(returnVal == 0);
    assert(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 1);
    assert(testG.hand[currentPlayer][G.handCount[currentPlayer]] == estate);
    assert(testG.supplyCount[estate] == G.supplyCount[estate] - 1);

    // test 3 - current player gains estate to discard
    memcpy(&testG, &G, sizeof(struct gameState));
    returnVal = gainCard(estate, &testG, toDiscard, currentPlayer);
#if (NOISY_TEST == 1)
    printf("\n");
    printf("Current player gains estate to discard\n");
    printf("Return value: %d, expected: %d\n", returnVal, 0);
    printf("Current player discard count: %d, expected: %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer] + 1);
    printf("Current player newest card to discard: %d, expected: %d\n", testG.discard[currentPlayer][G.discardCount[currentPlayer]], estate);
    printf("Estate supply count: %d, expected: %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
#endif
    assert(returnVal == 0);
    assert(testG.discardCount[currentPlayer] == G.discardCount[currentPlayer] + 1);
    assert(testG.discard[currentPlayer][G.discardCount[currentPlayer]] == estate);
    assert(testG.supplyCount[estate] == G.supplyCount[estate] - 1);

    // test 4 - player cannot gain a card with empty supply pile
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[estate] = 0; // set supply of estates to zero
    returnVal = gainCard(estate, &testG, toDeck, currentPlayer);
#if (NOISY_TEST == 1)
    printf("\n");
    printf("Player cannot gain a card with empty supply pile of that card\n");
    printf("Return value: %d, expected: %d\n", returnVal, -1);
    printf("Current player deck count: %d, expected: %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer]);
    printf("Current player newest card to deck: %d, expected: %d\n", testG.deck[currentPlayer][testG.deckCount[currentPlayer] - 1], G.deck[currentPlayer][G.deckCount[currentPlayer] - 1]);
    printf("Estate supply count: %d, expected: %d\n", testG.supplyCount[estate], 0);
#endif
    assert(returnVal == -1);
    assert(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer]);
    assert(testG.deck[currentPlayer][testG.deckCount[currentPlayer]- 1] == G.deck[currentPlayer][G.deckCount[currentPlayer] - 1]);
    assert(testG.supplyCount[estate] == 0);

    printf("All tests passed!\n");

    return 0;
}


