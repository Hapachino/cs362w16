/* -----------------------------------------------------------------------
 * test remodel
 * 
 *
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g  randomtestcard.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

int trashOK(int trashCard, int gainCard);

int main() {
    int i;
    int seed = 1000;

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
               , remodel, smithy, village, sea_hag, embargo};

    struct gameState G, testG;
    // Card enum - Name        - Cost 
    // 0         - curse       - 0
    // 22        - embargo     - 2
    // 14        - village     - 3
    // 13        - smithy      - 4
    // 11        - mine        - 5
    //  7        - adventurer  - 6
    //  3        - province    - 8
    // toTest[] is the list of cards we will try to gain
    int toTest[] = {curse, embargo, village, smithy, mine, adventurer, province};

    int index;
    int trashCard, trashIndex;
    int gainCard, gainIndex;
    int preDeck, preDiscard, preHand;
    int expectDiscard, expectHand;
    int result, expected;
    bool pass = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing remodel\n");

    // Copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // Start testing
    p = 0;
    printf("\n----------------- Test\n");

    // Initialize card counts
    testG.deckCount[p] = 0;
    testG.discardCount[p] = 0;
    testG.handCount[p] = 0;

    // Create hand of 10 random cards
    for (i = 0; i < 10; i++) {
        index = floor(Random() * 10);
        testG.hand[p][i] = k[index];
        testG.handCount[p]++;
    }

    // Put remodel in hand
    testG.hand[p][0] = remodel;

    // Decide on card to trash
    // trashIndex = (Random() % max - min + 1)) + min
    // max = 9, min = 1 (remodel is at index 0)
    trashIndex = (floor(Random() * 9)) + 1;
    // trashCard is the card at trashIndex
    trashCard = testG.hand[p][trashIndex];

    // Decide on card to gain
    // gainIndex = (Random() % max - min + 1)) + min
    // max = 6, min = 0
    gainIndex = floor(Random() * 6);
    // trashCard is the card at trashIndex
    gainCard = toTest[gainIndex];

    // Save pre-test values
    preDeck = testG.deckCount[p];
    preDiscard = testG.discardCount[p];
    preHand = testG.handCount[p];

    // game state
    // player
    // card to trash: int choice1 = trashIndex
    // card to gain : int choice2 = gainIndex
    // remodel index: int handPos = 0 (testG.hand[p][0])
    result = playRemodel(&testG, p, trashIndex, gainIndex, 0);
    expected = trashOK(trashCard, gainCard);

    printf("\nchoice1 cost: %d, choice2 cost: %d\n", getCost(trashCard), getCost(gainCard));
    printf("Result: %d, Expected: %d\n", result, expected);
    if (result != expected) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    // Successful trash and gain
    // discardCount should be 2 because gained a card and played remodel
    // handCount should be 3 (-2 because played remodel and trashed a card)
    expectDiscard = preDiscard + 2;
    expectHand = preHand - 2;

    if (expected == 1) {
        printf("Discard count: %d, Expected: %d\n", testG.discardCount[p], expectDiscard);
        if (testG.discardCount[p] != expectDiscard) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }

        printf("Hand count: %d, Expected: %d\n", testG.handCount[p], expectHand);
        if (testG.handCount[p] != expectHand) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }
    }

    // Unsuccessful - no trash/gain
    // discardCount should be 0
    // gainedCard should be 0
    // handCount should be 5 (keep remodel and could not trash card to gain card)
    expectDiscard = preDiscard;
    expectHand = preHand;

    if (expected == 0) {
        printf("Discard count: %d, Expected: %d\n", testG.discardCount[p], expectDiscard);
        if (testG.discardCount[p] != expectDiscard) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }

        printf("Hand count: %d, Expected: %d\n", testG.handCount[p], expectHand);
        if (testG.handCount[p] != expectHand) {
            printf("----------------- TEST FAILED!\n");
            pass = false;
        }
    }

    return 0;
}

int trashOK(int trashCard, int gainCard) {
    // Gain a card costing up to 2 more than the trashed card.
    if (getCost(trashCard) + 2 >= getCost(gainCard)) {
        return 1;
    }

    return 0;
}
