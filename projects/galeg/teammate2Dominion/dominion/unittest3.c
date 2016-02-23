
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    int maxHandCount = 5;
    int deckSize = 0;
    int player1 = 0;
    int player2 = 1;

    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING fullDeckCount():\n");

    printf("Testing with no cards added.  Game starts with 10 cards each\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    deckSize = fullDeckCount(player1, copper, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 10, deckSize);
    assert(10 == deckSize);
    deckSize = fullDeckCount(player2, 0, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 10, deckSize);
    assert(10 == deckSize);

    printf("Testing with 10 cards added to player2's discard\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    for(i = 0; i < 10; i++) {
        testG.discard[player2][testG.discardCount[player2]] = curse;
        testG.discardCount[player2] += 1;
    }
    for(i = 0; i < 5; i++) {
        testG.deck[player1][testG.deckCount[player1]] = curse;
        testG.deckCount[player1] += 1;
    }
    deckSize = fullDeckCount(player1, copper, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 15, deckSize);
    assert(15 == deckSize);
    deckSize = fullDeckCount(player2, 0, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 20, deckSize);
    assert(20 == deckSize);


    printf("\nAll tests passed!\n\n\n");

    return 0;
}
