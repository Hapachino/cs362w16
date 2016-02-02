/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * cardtest3.c
 * Test of the village card
 ******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTCARD "village"

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
    int handPos = 0;
    int bonus = 0;
    
    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1:  draw one card from empty deck --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 0;
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = village;
    int beforeNumberOfActions = testGame.numActions;
    
    cardEffect(village, 0, 0, 0, &testGame, handPos, &bonus);
   
    int afterNumberOfActions = testGame.numActions;
    
    printf("Test 1: draw one card from empty deck\n");
    printf("Hand Count = %d, expected = %d\n", testGame.handCount[player], 0);
    printf("Number of Actions = %d, expected = %d\n\n", afterNumberOfActions, beforeNumberOfActions + 2);
    assert(testGame.handCount[player] == 0);
    assert(afterNumberOfActions == beforeNumberOfActions + 2);

    // ----------- TEST 2:  draw one card from non-empty deck --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 1;
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = village;
    
    beforeNumberOfActions = testGame.numActions;
    
    cardEffect(village, 0, 0, 0, &testGame, handPos, &bonus);
    
    afterNumberOfActions = testGame.numActions;
    
    printf("Test 2: draw one card from non-empty deck\n");
    printf("Hand Count = %d, expected = %d\n", testGame.handCount[player], 1);
    printf("Number of Actions = %d, expected = %d\n\n", afterNumberOfActions, beforeNumberOfActions + 2);
    assert(testGame.handCount[player] == 1);
    assert(afterNumberOfActions == beforeNumberOfActions + 2);

    
    // ----------- TEST 3: Card gets discarded --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.deckCount[player] = 1;
    testGame.handCount[player] = 1;
    testGame.hand[player][handPos] = village;
    
    cardEffect(village, 0, 0, 0, &testGame, handPos, &bonus);
  
    int villageFound = foundCardInHand(&testGame, player, village);
    
    printf("Test 3: number of actions increases by 1\n");
    printf("Card found in hand = %d, expected %d\n", villageFound, 0);
    printf("Number of Actions = %d, expected = %d\n\n", afterNumberOfActions, beforeNumberOfActions + 2);
    assert(villageFound == 0);
    assert(afterNumberOfActions == beforeNumberOfActions + 2);
    
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

    return 0;
}