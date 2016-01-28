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

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
               , remodel, smithy, village, sea_hag, embargo};

    struct gameState G, testG;
    bool pass = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing remodel\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Start testing
    p = 0;
    printf("----------------- Trash embargo\n");

    // Card enum - Name        - Cost 
    // 22        - embargo     - 2
    // 14        - village     - 3
    // 13        - smithy      - 4
    // 11        - mine        - 5
    //  7        - adventurer  - 6
    int toTest[] = {embargo, village, smithy, mine, adventurer};

    // choice1: 2, choice2: 2
    // Expect: 0
    // choice1: 2, choice2: 3
    // Expect: 0
    // choice1: 2, choice2: 4
    // Expect: 0
    // choice1: 2, choice2: 5
    // Expect: -1
    // choice1: 2, choice2: 6
    // Expect: -1
    int expected1[] = {0, 0, 0, -1, -1};
    remodelTrash(&testG, p, embargo, toTest, expected1);
    
    p = 0;
    printf("----------------- Trash village\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // choice1: 3, choice2: 2
    // Expect: 0
    // choice1: 3, choice2: 3
    // Expect: 0
    // choice1: 3, choice2: 4
    // Expect: 0
    // choice1: 3, choice2: 5
    // Expect: 0
    // choice1: 3, choice2: 6
    // Expect: -1
    int expected2[] = {0, 0, 0, 0, -1};
    remodelTrash(&testG, p, village, toTest, expected2);

    p = 0;
    printf("----------------- Trash smithy\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // choice1: 4, choice2: 2
    // Expect: 0
    // choice1: 4, choice2: 3
    // Expect: 0
    // choice1: 4, choice2: 4
    // Expect: 0
    // choice1: 4, choice2: 5
    // Expect: 0
    // choice1: 4, choice2: 6
    // Expect: 0
    int expected3[] = {0, 0, 0, 0, 0};
    remodelTrash(&testG, p, smithy, toTest, expected3);

    p = 0;
    printf("----------------- Trash mine\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // choice1: 5, choice2: 2
    // Expect: 0
    // choice1: 5, choice2: 3
    // Expect: 0
    // choice1: 5, choice2: 4
    // Expect: 0
    // choice1: 5, choice2: 5
    // Expect: 0
    // choice1: 5, choice2: 6
    // Expect: 0
    int expected4[] = {0, 0, 0, 0, 0};
    remodelTrash(&testG, p, mine, toTest, expected4);

    p = 0;
    printf("----------------- Trash adventurer\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // choice1: 5, choice2: 2
    // Expect: 0
    // choice1: 5, choice2: 3
    // Expect: 0
    // choice1: 5, choice2: 4
    // Expect: 0
    // choice1: 5, choice2: 5
    // Expect: 0
    // choice1: 5, choice2: 6
    // Expect: 0
    int expected5[] = {0, 0, 0, 0, 0};
    remodelTrash(&testG, p, adventurer, toTest, expected5);

    if (pass) {
        printf("All tests passed!");
    }
    else {
        printf("Some test(s) failed!");
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

int remodelTrash(struct gameState *state, int p, int trashCard, int toTest[], int expected[]) {
    int i, j;
    int result;

    // int playRemodel(int j, struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos, int i)
    for (i = 0; i < 5; i++) {
        // Shift elements over so 
        // remodel always at index 0
        // trashCard always at index 1
        for (j = state->handCount[p] + 1; j > 0; j--) {
            state->hand[p][j] = state->hand[p][j - 2];
        }

        // Put remodel in hand
        state->hand[p][0] = remodel;
        state->handCount[p]++;

        // Put card to trash in hand
        state->hand[p][1] = trashCard;
        state->handCount[p]++;

        displayDeck(state, p);

        // card to trash: int choice1 = trashCard (testG.hand[p][1])
        // card to gain : int choice2 = toTest[]
        // remodel index: int handPos = 0 (testG.hand[p][0])
        result = playRemodel(0, state, p, 1, toTest[i], 0, 0);
        printf("choice1 cost: %d, choice2 cost: %d\n", getCost(trashCard), getCost(toTest[i]));
        printf("Result: %d, Expected: %d\n\n", result, expected[i]);

        // displayDeck(state, p);
    }

    return 0;
}