/* -----------------------------------------------------------------------
 * test adventurer
 * 
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

int displayAll(struct gameState *state, int p);
int displayDeck(struct gameState *state, int p);
int displayDiscard(struct gameState *state, int p);
int displayHand(struct gameState *state, int p);

int main() {
    int i, j;
    int seed = 1000;

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
               , remodel, smithy, village, sea_hag, embargo};

    int cards[10] = {copper, smithy, village, silver, mine, gold,
                gardens, remodel, embargo, cutpurse};

    struct gameState G, testG;
    int index, count;
    int treasureCount;
    int treasureDrawn, otherRevealed;
    int preDeck, preDiscard, preHand;
    bool pass = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing adventurer\n");

    // Number of runs
    for (j = 1; j < 1001; j++) {
        // Copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        // Player 0
        p = 0;
        printf("----------------- Random Deck Test %d\n", j);
        printf("----------------- Initial counts\n");

        // Initialize deckCount and treasureCount
        testG.deckCount[p] = 0;
        treasureCount = 0;

        // Create deck of 10 random cards
        for (i = 0; i < 10; i++) {
            index = floor(Random() * 10);
            testG.deck[p][i] = cards[index];
            testG.deckCount[p]++;
        }

        // Check deck for number of treasures
        for (i = 0; i < testG.deckCount[p]; i++) {
            if (testG.deck[p][i] == copper || testG.deck[p][i] == silver || testG.deck[p][i] == gold) {
                treasureCount++;
            }
        }

        // Discard should be empty
        testG.discardCount[p] = 0;

        // Create fixed hand of 5 cards
        testG.handCount[p] = 0;
        for (i = 0; i < 5; i++) {
            testG.hand[p][i] = estate;
            testG.handCount[p]++;
        }

        // Save pre-test values
        preDeck = testG.deckCount[p];
        preDiscard = testG.discardCount[p];
        preHand = testG.handCount[p];

        // Calculate expected values
        // If no treasures in deck, then reveal all cards in deck
        if (treasureCount == 0) {
            treasureDrawn = 0;
            otherRevealed = testG.deckCount[p];
        }
        // If 1 treasure in deck,
        // then reveal all cards in deck in an attempt to get 2 treasures
        else if (treasureCount == 1) {
            treasureDrawn = 1;
            otherRevealed = testG.deckCount[p] - treasureDrawn;
        }
        // If at least 2 treasures in deck
        else {
            treasureDrawn = 0;
            otherRevealed = 0;
            i = testG.deckCount[p] - 1;
            while (treasureDrawn < 2) {
                if (testG.deck[p][i] == copper || testG.deck[p][i] == silver || testG.deck[p][i] == gold) {
                    treasureDrawn++;
                    i--;
                }
                else {
                    otherRevealed++;
                    i--;
                }
            }
        }

        displayAll(&testG, p);
    
        printf("----------------- After playAdventurer\n");

        playAdventurer(&testG, p);

        displayDeck(&testG, p);

        // Check that deck is correct
        count = preDeck - otherRevealed - treasureDrawn;
        printf("Deck count: %d, Expected: %d\n", testG.deckCount[p], count);
        if (testG.deckCount[p] != count) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }

        displayDiscard(&testG, p);

        // Check that discard is correct
        count = preDiscard + otherRevealed;
        printf("Discard count: %d, Expected: %d\n", testG.discardCount[p], count);
        if (testG.discardCount[p] != count) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }

        displayHand(&testG, p);

        // Check that count of cards is correct
        count = preHand + treasureDrawn;
        printf("Hand count: %d, Expected: %d\n", testG.handCount[p], count);
        if (testG.handCount[p] != count) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }
    }

    if (pass) {
        printf("\nAll tests passed!\n");
    }
    else {
        printf("\nSome test(s) failed!\n");
    }
    
    return 0;
}

int displayAll(struct gameState *state, int p) {
    int i;

    printf("DECK\n");
    for (i = 0; i < state->deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->deck[p][i]);
    }

    printf("DISCARD\n");
    for (i = 0; i < state->discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->discard[p][i]);
    }

    printf("HAND\n");
    for (i = 0; i < state->handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->hand[p][i]);
    }

    return 0;
}

int displayDeck(struct gameState *state, int p) {
    int i;

    printf("DECK\n");
    for (i = 0; i < state->deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->deck[p][i]);
    }

    return 0;
}

int displayDiscard(struct gameState *state, int p) {
    int i;

    printf("DISCARD\n");
    for (i = 0; i < state->discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->discard[p][i]);
    }

    return 0;
}

int displayHand(struct gameState *state, int p) {
    int i;

    printf("HAND\n");
    for (i = 0; i < state->handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, state->hand[p][i]);
    }

    return 0;
}
