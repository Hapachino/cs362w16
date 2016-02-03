/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * unittest4.c
 * Test of fullDeckCount()
 ******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNCTION "fullDeckCount()"

int main(){
    struct gameState originalGame, testGame;
    
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numberOfPlayers = 2;
    int player = 0;
    int seed = 1000;
    int count = 0;
    int card = estate;
    int secondCard = duchy;
    
    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // ----------- TEST 1:  Full deck count is zero when deck count, hand count, and discard count are all zero --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 0;
    testGame.handCount[player] = 0;
    testGame.discardCount[player] = 0;
    count = fullDeckCount(player, card, &testGame);
    printf("Test 1: Full deck count is zero when deck count, hand count, and discard count are all zero\n");
    printf("Full deck count = %d, expected %d\n", count, 0);
    assert(count == 0);

    // ----------- TEST 2: Mix of cards in deck for deckCount --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 3;
    testGame.handCount[player] = 0;
    testGame.discardCount[player] = 0;
    testGame.deck[player][0] = card;
    testGame.deck[player][1] = secondCard;
    testGame.deck[player][2] = card;
    count = fullDeckCount(player, card, &testGame);
    printf("TEST 2: Mix of cards, two of same card testing deckCount\n");
    printf("Full deck count = %d, expected = %d\n", count, 2);
    assert(count == 2);

    // ----------- TEST 3: Mix of cards in deck for handCount --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 0;
    testGame.handCount[player] = 3;
    testGame.discardCount[player] = 0;
    testGame.hand[player][0] = card;
    testGame.hand[player][1] = secondCard;
    testGame.hand[player][2] = card;
    count = fullDeckCount(player, card, &testGame);
    printf("TEST 3: Mix of cards, two of same card testing handCount\n");
    printf("Full hand count = %d, expected = %d\n", count, 2);
    assert(count == 2);
    
    // ----------- TEST 4: Mix of cards in deck for discardCount --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 0;
    testGame.handCount[player] = 0;
    testGame.discardCount[player] = 3;
    testGame.discard[player][0] = card;
    testGame.discard[player][1] = secondCard;
    testGame.discard[player][2] = card;
    count = fullDeckCount(player, card, &testGame);
    printf("TEST 4: Mix of cards, two of same card testing discardCount\n");
    printf("Full hand count = %d, expected = %d\n", count, 2);
    assert(count == 2);
    
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);
    
    return 0;
}