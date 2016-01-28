/* -----------------------------------------------------------------------
 * test remodel
 * 
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

int main() {
    int i;
    int seed = 1000;

    int numPlayer = 3;
    int p, r;
    int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
               , remodel, smithy, village, sea_hag, embargo};

    struct gameState G, testG;
    int result;
    bool pass = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing remodel\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Start testing
    p = 0;
    printf("----------------- Player %d:\n", p);

    // Put remodel in hand
    testG.hand[p][ testG.handCount[p] ] = remodel;
    testG.handCount[p]++;

    displayDeck(&testG, p);

    // int playRemodel(int j, struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos, int i)

    printf("Left: %d\n", getCost(testG.hand[p][embargo]) + 2);
    printf("Right: %d\n", getCost(0));

    result = playRemodel(0, &testG, p, 0, embargo, 5, 0);
    printf("Success: %d\n", result);

    printf("Left: %d\n", getCost(testG.hand[p][embargo]) + 2);
    printf("Right: %d\n", getCost(1));

    result = playRemodel(0, &testG, p, 1, embargo, 5, 0);
    printf("Success: %d\n", result);

    printf("Left: %d\n", getCost(testG.hand[p][embargo]) + 2);
    printf("Right: %d\n", getCost(2));

    result = playRemodel(0, &testG, p, 2, embargo, 5, 0);
    printf("Success: %d\n", result);

    printf("Left: %d\n", getCost(testG.hand[p][embargo]) + 2);
    printf("Right: %d\n", getCost(3));

    result = playRemodel(0, &testG, p, 3, embargo, 5, 0);
    printf("Success: %d\n", result);

    printf("Left: %d\n", getCost(testG.hand[p][embargo]) + 2);
    printf("Right: %d\n", getCost(4));

    result = playRemodel(0, &testG, p, 4, embargo, 5, 0);
    printf("Success: %d\n", result);

    displayDeck(&testG, p);

    if (pass) {
        printf("\nAll tests passed!");
    }
    else {
        printf("\nSome test(s) failed!");
    }

    return 0;
}

int displayDeck(struct gameState *state, int p) {
    int i;

    printf("DECK COUNT\n");
    for (i = 0; i < state->deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->deck[p][i]);
    }

    printf("DISCARD COUNT\n");
    for (i = 0; i < state->discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->discard[p][i]);
    }

    printf("HAND COUNT\n");
    for (i = 0; i < state->handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->hand[p][i]);
    }

    return 0;
}