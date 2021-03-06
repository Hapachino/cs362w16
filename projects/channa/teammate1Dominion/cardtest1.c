/* -----------------------------------------------------------------------
 * test smithy
 * 
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

    struct gameState G;
    int count;
    bool pass = true;

    // Use for checking state change
    int victoryCount, kingdomCount;
    int victory_kingdom[13];
    int index = 0;
    bool equal = true;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    printf("----------------- Testing smithy\n");

    // Before testing, check victory and kingdom cards
    // victory_kingdom[] saves pre-test pile counts
    printf("----------------- BEFORE PLAYER ACTIONS AND BUYS\n");

    victoryCount = G.supplyCount[estate];
    victory_kingdom[index] = victoryCount;
    index++;
    printf("estate count: %d\n", victoryCount);

    victoryCount = G.supplyCount[duchy];
    victory_kingdom[index] = victoryCount;
    index++;
    printf("duchy count: %d\n", victoryCount);

    victoryCount = G.supplyCount[province];
    victory_kingdom[index] = victoryCount;
    index++;
    printf("province count: %d\n", victoryCount);

    for (i = 0; i < 10; i++) {
        kingdomCount = G.supplyCount[ k[i] ];
        victory_kingdom[index] = kingdomCount;
        index++;
        printf("k[%d] count: %d\n", i, kingdomCount);
    }

    // Start testing
    p = 0;
    printf("----------------- Player %d:\n", p);

    // Put smithy in hand
    G.hand[p][ G.handCount[p] ] = smithy;
    G.handCount[p]++;

    // Check pile counts
    printf("----------------- AFTER PUT SMITHY IN HAND\n");

    printf("DECK COUNT\n");
    for (i = 0; i < G.deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.deck[p][i]);
    }

    printf("DISCARD COUNT\n");
    for (i = 0; i < G.discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.discard[p][i]);
    }

    printf("HAND COUNT\n");
    for (i = 0; i < G.handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.hand[p][i]);
    }

    // Put cards in deck:
    // adventurer = 7
    // cutpurse = 21
    // remodel = 12
    // sea_hag = 25
    // village = 14
    G.deck[p][ G.deckCount[p] ] = adventurer;
    G.deckCount[p]++;
    G.deck[p][ G.deckCount[p] ] = cutpurse;
    G.deckCount[p]++;
    G.deck[p][ G.deckCount[p] ] = remodel;
    G.deckCount[p]++;
    G.deck[p][ G.deckCount[p] ] = sea_hag;
    G.deckCount[p]++;
    G.deck[p][ G.deckCount[p] ] = village;
    G.deckCount[p]++;

    // Check pile counts
    printf("----------------- AFTER PUT 5 MORE CARDS IN DECK\n");

    printf("DECK COUNT\n");
    for (i = 0; i < G.deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.deck[p][i]);
    }

    printf("DISCARD COUNT\n");
    for (i = 0; i < G.discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.discard[p][i]);
    }

    printf("HAND COUNT\n");
    for (i = 0; i < G.handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.hand[p][i]);
    }

    // smithy should draw 3 cards from player's own discard
    // and add them to player's own hand
    // 14, 25, and 12 should be drawn and added to hand
    // 7 and 21 should stay in the deck
    // smithy should be added to discard
    playSmithy(&G, p, 5);

    // Check pile counts
    printf("----------------- AFTER PLAY SMITHY\n");

    printf("DECK COUNT\n");
    for (i = 0; i < G.deckCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.deck[p][i]);
    }

    // Verify
    int check1[] = {estate, estate, copper, copper, copper, adventurer, cutpurse};
    count = sizeof(check1)/sizeof(check1[0]);

    printf("Deck count: %d, Expected: %d\n", G.deckCount[p], count);
    if (G.deckCount[p] != count) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    printf("DISCARD COUNT\n");
    for (i = 0; i < G.discardCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.discard[p][i]);
    }

    // Verify
    int check2[] = {smithy};
    count = sizeof(check2)/sizeof(check2[0]);

    printf("Discard count: %d, Expected: %d\n", G.discardCount[p], count);
    if (G.discardCount[p] != count) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    printf("HAND COUNT\n");
    for (i = 0; i < G.handCount[p]; i++)
    {
        printf("Position %d, Card: %d\n", i, G.hand[p][i]);
    }

    // Verify
    int check3[] = {copper, copper, estate, copper, copper, village, sea_hag, remodel};
    count = sizeof(check3)/sizeof(check3[0]);

    printf("Hand count: %d, Expected: %d\n", G.handCount[p], count);
    if (G.handCount[p] != count) {
        printf("----------------- TEST FAILED!\n");
        pass = false;
    }

    // Should be NO state changes made to next player's decks
    p = 1;
    printf("----------------- Player %d:\n", p);
    printf("----------------- Check that no state changes were made to other player's deck\n");

    // Check pile counts
    int copperCount = 0;
    int estateCount = 0;

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

    // Should be NO state changes made to victory and kingdom cards
    // (besides the changes intentionally made outside of playSmithy)
    printf("----------------- Check that no state changes were made to victory and kingdom card piles\n");

    victoryCount = G.supplyCount[estate];
    printf("estate count: %d\n", victoryCount);
    assert(victoryCount == victory_kingdom[0]);

    victoryCount = G.supplyCount[duchy];
    printf("duchy count: %d\n", victoryCount);
    assert(victoryCount == victory_kingdom[1]);

    victoryCount = G.supplyCount[province];
    printf("province count: %d\n", victoryCount);
    assert(victoryCount == victory_kingdom[2]);

    // index 0 to 2 = victory
    // index 3 to 12 = kingdom
    int x = 3;

    for (i = 0; i < 10; i++) {
        kingdomCount = G.supplyCount[ k[i] ];
        printf("k[%d] count: %d\n", i, kingdomCount);
        if (victory_kingdom[x] != kingdomCount) {
            equal = false;
            break;
        }
        x++;
    }

    printf("No state changes for victory and kingdom card piles: %d\n", equal);

    if (pass) {
        printf("\nAll tests passed!\n");
    }
    else {
        printf("\nSome test(s) failed!\n");
    }
    
    return 0;
}
