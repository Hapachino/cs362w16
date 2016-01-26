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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;

    int numPlayer = 2;
    int p, r;
    int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
               , remodel, smithy, village, sea_hag, embargo};

    struct gameState G;
    int victoryCount, kingdomCount;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

    // Before testing, check victory and kingdom cards
    printf("========BEFORE PLAYER ACTIONS AND BUYS\n");

    victoryCount = supplyCount(estate, &G);
    printf("estate count: %d\n", victoryCount);
    victoryCount = supplyCount(duchy, &G);
    printf("duchy count: %d\n", victoryCount);
    victoryCount = supplyCount(province, &G);
    printf("province count: %d\n", victoryCount);

    for (i = 0; i < 10; i++) {
        kingdomCount = supplyCount(k[i], &G);
        printf("k[%d] count: %d\n", i, kingdomCount);
    }

    // Enable buy and action phases
    G.numBuys = 1000;
    G.coins = 1000;
    G.numActions = 1000;

    // Start testing
    p = whoseTurn(&G);
    printf("========Player %d's turn:\n", p);

    // Buy smithy
    buyCard(smithy, &G);

    // Check pile counts
    printf("========AFTER BUY SMITHY\n");

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

    // Draw 6 cards
    // Currently 5 in hand
    // Draw will add the following 6 cards to hand:
    // - 5 from deck (for total of 7 coppers and 3 estates)
    // - 1 card from discard (newly acquired smithy)
    // 6th card drawn will be smithy
    for (i = 0; i < 6; i++) {
        drawCard(p, &G);
    }

    // Check pile counts
    printf("========AFTER DRAW CARDS\n");

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

    // Buy cards will add the following to discard:
    // adventurer = 7
    // cutpurse = 21
    // remodel = 12
    // sea_hag = 25
    // village = 14
    buyCard(adventurer, &G);
    buyCard(cutpurse, &G);
    buyCard(remodel, &G);
    buyCard(sea_hag, &G);
    buyCard(village, &G);

    // Check pile counts
    printf("========AFTER BUY CARDS\n");

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

    // smithy should draw 3 cards from player's own pile
    // and add them to player's own hand
    // Other cards bought should go to player's own deck
    playSmithy(0, p, &G, 10);

    // Check pile counts
    printf("========AFTER PLAY SMITHY\n");

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

    // Switch to next player
    endTurn(&G);

    // Should be NO state changes made to next player's decks
    p = whoseTurn(&G);
    printf("========Player %d's turn:\n", p);

    // Check pile counts
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

    // Should be NO state changes made to victory and kingdom cards
    // (besides the changes intentionally made outside of playSmithy)
    victoryCount = supplyCount(estate, &G);
    printf("estate count: %d\n", victoryCount);
    victoryCount = supplyCount(duchy, &G);
    printf("duchy count: %d\n", victoryCount);
    victoryCount = supplyCount(province, &G);
    printf("province count: %d\n", victoryCount);

    // int k[10] = {adventurer, great_hall, cutpurse, gardens, mine
    //            , remodel, smithy, village, sea_hag, embargo};

    for (i = 0; i < 10; i++) {
        kingdomCount = supplyCount(k[i], &G);
        printf("k[%d] count: %d\n", i, kingdomCount);
    }
    
    return 0;
}
