/* -----------------------------------------------------------------------
 * test adventurer
 * 
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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
    int count;

    // Default
    int estateDefault = 8;
    // Check pile counts
    int copperCount = 0;
    int estateCount = 0;
    bool pass = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing adventurer\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Player 1
    p = 0;
    printf("----------------- Player %d:\n", p);

    printf("----------------- Test 1: coppers at top of deck\n");
    printf("----------------- Initial counts\n");

    // 1, 1, 4, 4, 4
    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Empty
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // 4, 4, 1, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    printf("----------------- After playAdventurer\n");

    // int playAdventurer (struct gameState *state, int currentPlayer, int drawntreasure, int cardDrawn, int temphand[], int z);
    playAdventurer(&testG, p);

    // 1, 1, 4,
    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Should have taken 2 coppers from top
    int expected1[] = {1, 1, 4};
    count = sizeof(expected1)/sizeof(expected1[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.deckCount[p], count);
    assert(testG.deckCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected1[i]);
        assert(testG.deck[p][i] == expected1[i]);
    }

    // Empty
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // No non-treasure cards revealed so no discards
    int expected2[] = {};
    count = sizeof(expected2)/sizeof(expected2[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.discardCount[p], count);
    assert(testG.discardCount[p] == count);

    // 4, 4, 1, 4, 4, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    // 2 coppers added to hand
    int expected3[] = {4, 4, 1, 4, 4, 4, 4};
    count = sizeof(expected3)/sizeof(expected3[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.handCount[p], count);
    assert(testG.handCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected3[i]);
        assert(testG.hand[p][i] == expected3[i]);
    }

    printf("----------------- Test 2: coppers at bottom of deck\n");
    printf("----------------- Initial counts\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // 4, 4, 4, 1, 1
    for (i = 0; i < 3; i++) {
        testG.deck[p][i] = copper;
    }

    for (i = 3; i < 5; i++) {
        testG.deck[p][i] = estate;
    }

    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Empty
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // 4, 4, 1, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    printf("----------------- After playAdventurer\n");

    playAdventurer(&testG, p);

    // 4
    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Should have discarded 2 estates and taken 2 coppers
    int expected4[] = {4};
    count = sizeof(expected4)/sizeof(expected4[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.deckCount[p], count);
    assert(testG.deckCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected4[i]);
        assert(testG.deck[p][i] == expected4[i]);
    }

    // 1, 1
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // Should have discarded 2 estates
    int expected5[] = {1, 1};
    count = sizeof(expected5)/sizeof(expected5[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.discardCount[p], count);
    if (testG.discardCount[p] != count) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected5[i]);
        if (testG.discard[p][i] != expected5[i]) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }
    }

    // 4, 4, 1, 4, 4, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    // 2 coppers added to hand
    int expected6[] = {4, 4, 1, 4, 4, 4, 4};
    count = sizeof(expected6)/sizeof(expected6[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.handCount[p], count);
    assert(testG.handCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected6[i]);
        assert(testG.hand[p][i] == expected6[i]);
    }

    printf("----------------- Test 3: coppers interspersed through deck\n");
    printf("----------------- Initial counts\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    // 4, 1, 4, 1, 4
    for (i = 0; i < 5; i = i + 2) {
        testG.deck[p][i] = copper;
    }

    for (i = 1; i < 5; i = i + 2) {
        testG.deck[p][i] = estate;
    }

    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Empty
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // 4, 4, 1, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    printf("----------------- After playAdventurer\n");

    playAdventurer(&testG, p);

    // 4, 1
    printf("DECK COUNT\n");
    for (i = 0; i < testG.deckCount[p]; i++) {
        printf("%d\n", testG.deck[p][i]);
    }

    // Should have discarded 1 estate and taken 2 coppers
    int expected7[] = {4, 1};
    count = sizeof(expected7)/sizeof(expected7[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.deckCount[p], count);
    assert(testG.deckCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected7[i]);
        assert(testG.deck[p][i] == expected7[i]);
    }

    // 1
    printf("DISCARD COUNT\n");
    for (i = 0; i < testG.discardCount[p]; i++) {
        printf("%d\n", testG.discard[p][i]);
    }

    // Should have discarded 1 estate
    int expected8[] = {1};
    count = sizeof(expected8)/sizeof(expected8[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.discardCount[p], count);
    if (testG.discardCount[p] != count) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected8[i]);
        if (testG.discard[p][i] != expected8[i]) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }
    }

    // 4, 4, 1, 4, 4, 4, 4
    printf("HAND COUNT\n");
    for (i = 0; i < testG.handCount[p]; i++) {
        printf("%d\n", testG.hand[p][i]);
    }

    // 2 coppers added to hand
    int expected9[] = {4, 4, 1, 4, 4, 4, 4};
    count = sizeof(expected9)/sizeof(expected9[0]);

    // Check that count of cards is correct
    printf("Card count: %d, Expected: %d\n", testG.handCount[p], count);
    assert(testG.handCount[p] == count);

    // Check that names of cards are correct
    printf("Expected:\n");
    for (i = 0; i < count; i++) {
        printf("%d\n", expected9[i]);
        assert(testG.hand[p][i] == expected9[i]);
    }

    // Should be NO state changes made to next player's decks
    p = 1;
    printf("----------------- Player %d:\n", p);
    printf("----------------- Test 4: Check that no state changes were made to other player's deck\n");

    printf("DECK COUNT\n");
    for (i = 0; i < G.deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.deck[p][i]);
        if (G.deck[p][i] == copper) {
            copperCount++;
        }
        if (G.deck[p][i] == estate) {
            estateCount++;
        }
    }

    // Verify
    printf("Copper count: %d, Expected: 7\n", copperCount);
    printf("Estate count: %d, Expected: 3\n", estateCount);
    assert(copperCount == 7);
    assert(estateCount == 3);

    printf("Deck count: %d, Expected: 10\n", G.deckCount[p]);
    assert(G.deckCount[p] == 10);

    printf("DISCARD COUNT\n");
    for (i = 0; i < G.discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.discard[p][i]);
    }

    // Verify
    printf("Discard count: %d, Expected: 0\n", G.discardCount[p]);
    assert(G.discardCount[p] == 0);

    printf("HAND COUNT\n");
    for (i = 0; i < G.handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.hand[p][i]);
    }

    // Verify
    printf("Hand count: %d, Expected: 0\n", G.handCount[p]);
    assert(G.handCount[p] == 0);

    printf("----------------- Test 5: Check that no state changes were made to estate pile\n");
    printf("Estate count: %d, Expected: %d\n", G.supplyCount[estate], estateDefault);
    assert(G.supplyCount[estate] == estateDefault);

    if (pass) {
        printf("\nAll tests passed!\n");
    }
    else {
        printf("\nSome test(s) failed!\n");
    }
    
    return 0;
}
