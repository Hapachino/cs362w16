/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * cardtest1.c
 * Test of the smithy card
 ******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTCARD "smithy"

int foundCardInHand(struct gameState *state, int player, int card){
    int found = 0;
    int i;
    
    for(i = 0; i < state->handCount[player]; i++){
        if(state->hand[player][i] == card){
            found = 1;
            break;
        }
    }
    
    return found;
}

int main(){
    struct gameState originalGame, testGame;
    
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numberOfPlayers = 2;
    int player = 0;
    int seed = 1000;
    int handPos = 0;
    int handCountAfter;
    int firstCard = estate;
    int secondCard = duchy;
    int thirdCard = province;
    
    
    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // ----------- TEST 1: There are no cards in the deck --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = smithy;
    testGame.deckCount[player] = 0;
    playSmithy(player, &testGame, handPos);
    handCountAfter = testGame.handCount[player];
    
    printf("Test 1: There are no cards in the deck\n");
    printf("Hand count = %d, expected = %d\n\n", handCountAfter, 0);
    assert(handCountAfter == 0);
    
    
    // ----------- TEST 2: one card in hand --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][0] = smithy;
    testGame.deckCount[player] = 1;
    
    testGame.deck[player][0] = firstCard;
    
    playSmithy(player, &testGame, handPos);
    handCountAfter = testGame.handCount[player];
    
    printf("Test 2: one card in hand\n");
    printf("Hand count = %d, expected = %d\n", handCountAfter, 1);
    printf("Card in hand = %d, expected = %d\n\n", testGame.hand[player][0], firstCard);
    assert(handCountAfter == 1);
    assert(testGame.hand[player][0] == firstCard);
    
    // ----------- TEST 3: two cards in hand --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][0] = smithy;
    testGame.deckCount[player] = 2;
    
    testGame.deck[player][0] = firstCard;
    testGame.deck[player][1] = secondCard;
    
    playSmithy(player, &testGame, handPos);
    handCountAfter = testGame.handCount[player];
    
    printf("Test 3: two cards in hand\n");
    printf("Hand count = %d, expected = %d\n", handCountAfter, 2);
    printf("Card in first position = %d, expected = %d\n", testGame.hand[player][0], firstCard);
    printf("Card in second position = %d, expected = %d\n\n", testGame.hand[player][1], secondCard);
    assert(handCountAfter == 2);
    assert(testGame.hand[player][0] == firstCard);
    assert(testGame.hand[player][1] == secondCard);
    
    // ----------- TEST 4: three cards in hand --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][0] = smithy;
    testGame.deckCount[player] = 3;
    
    testGame.deck[player][0] = firstCard;
    testGame.deck[player][1] = secondCard;
    testGame.deck[player][2] = thirdCard;
    
    playSmithy(player, &testGame, handPos);
    handCountAfter = testGame.handCount[player];
    
    printf("Test 4: three cards in hand\n");
    printf("Hand count = %d, expected = %d\n", handCountAfter, 3);
    
    int firstCardFound = foundCardInHand(&testGame, player, firstCard);
    int secondCardFound = foundCardInHand(&testGame, player, secondCard);
    int thirdCardFound = foundCardInHand(&testGame, player, thirdCard);

    
    printf("Card %d in hand = %d, expected = %d\n", firstCard, firstCardFound, 1);
    printf("Card %d in hand = %d, expected = %d\n", secondCard, secondCardFound, 1);
    printf("Card %d in hand = %d, expected = %d\n\n", thirdCard, thirdCardFound, 1);
    assert(handCountAfter == 3);
    assert(firstCardFound);
    assert(secondCardFound);
    assert(thirdCardFound);
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    
    return 0;
}
