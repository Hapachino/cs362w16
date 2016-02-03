/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * cardtest1.c
 * Test of the adventurer card
 ******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTCARD "adventurer"

int foundCardInHand(struct gameState *state, int player, int card){
    int found = 0;
    
    for(int i = 0; i < state->handCount[player]; i++){
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
    int drawntreasure = 0;
    int z = 0;
    int cardDrawn;
    int temphand[MAX_HAND];
    int handPos = 0;
    int handCountAfter;
    
    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    
    // ----------- TEST 1:  drawn treasure = 1 when the treasure is copper--------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = adventurer;
    testGame.deckCount[player] = 1;
    testGame.deck[player][0] = copper;
    playAdventurer(player, &testGame);
    
    int copperInHand = foundCardInHand(&testGame, player, copper);
    
    printf("Test 1: drawn treasure = 1 when the treasure is copper\n");
    printf("Card %d in hand = %d, expected = %d\n\n", copper, copperInHand, 1);
    assert(copperInHand);
    
    // ----------- TEST 2:  drawn treasure = 1 when the treasure is silver --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = adventurer;
    testGame.deckCount[player] = 1;
    testGame.deck[player][0] = silver;
    playAdventurer(player, &testGame);
    
    int silverInHand = foundCardInHand(&testGame, player, silver);
    
    printf("Test 2:drawn treasure = 1 when the treasure is silver\n");
    printf("Card %d in hand = %d, expected = %d\n\n", silver, silverInHand, 1);
    assert(silverInHand);

    // ----------- TEST 2:  drawn treasure = 1 when the treasure is silver --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = adventurer;
    testGame.deckCount[player] = 1;
    testGame.deck[player][0] = gold;
    playAdventurer(player, &testGame);
    
    int goldInHand = foundCardInHand(&testGame, player, gold);
    
    printf("Test 2:drawn treasure = 1 when the treasure is gold\n");
    printf("Card %d in hand = %d, expected = %d\n\n", gold, goldInHand, 1);
    assert(goldInHand);
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    
    return 0;
}