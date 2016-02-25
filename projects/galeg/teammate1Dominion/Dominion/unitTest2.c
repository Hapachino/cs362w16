
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
    int score = 0;
    int player1 = 0;
    int player2 = 1;

    initializeGame(numPlayer, k, seed, &G);

    printf ("TESTING ScoreFor():\n");

    printf("Testing with no scoring cards added.  Game starts with 3 each\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 3, score);
    assert(3 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 3, score);
    assert(3 == score);

    printf("Add a province to the hand of each player\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[player1][testG.handCount[player1]] = province;
    testG.handCount[player1] += 1;
    testG.hand[player2][testG.handCount[player2]] = province;
    testG.handCount[player2] += 1;
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 9, score);
    assert(9 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 9, score);
    assert(9 == score);

    printf("Add a province to the discard of each player\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.discard[player1][testG.discardCount[player1]] = province;
    testG.discardCount[player1] += 1;
    testG.discard[player2][testG.discardCount[player2]] = province;
    testG.discardCount[player2] += 1;
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 9, score);
    assert(9 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 9, score);
    assert(9 == score);

    printf("Add a province to the deck of each player\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deck[player1][testG.deckCount[player1]] = province;
    testG.deckCount[player1] += 1;
    testG.deck[player2][testG.deckCount[player2]] = province;
    testG.deckCount[player2] += 1;
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 9, score);
    assert(9 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 9, score);
    assert(9 == score);

    printf("Add a province to the deck of player1 and a duchy to the discard of player2\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deck[player1][testG.deckCount[player1]] = province;
    testG.deckCount[player1] += 1;
    testG.discard[player2][testG.discardCount[player2]] = duchy;
    testG.discardCount[player2] += 1;
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 9, score);
    assert(9 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", 6, score);
    assert(6 == score);

  	printf("Add a province to the deck of player1 and a several curses to player2\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deck[player1][testG.deckCount[player1]] = province;
    testG.deckCount[player1] += 1;
    for(i = 0; i < 10; i++) {
       	testG.discard[player2][testG.discardCount[player2]] = curse;
    	testG.discardCount[player2] += 1;
    }
    score = scoreFor(player1, &testG);
    printf("expected score for player1 = %d, actual = %d\n", 9, score);
    assert(9 == score);
    score = scoreFor(player2, &testG);
    printf("expected score for player2 = %d, actual = %d\n", -7, score);
    assert(-7 == score);

    printf("\nAll tests passed!\n\n\n");

    return 0;
}
