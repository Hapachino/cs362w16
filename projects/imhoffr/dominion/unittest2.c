/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * unittest2.c
 * Test of gainCard()
 ******************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNCTION "gainCard()"

int main(){
    struct gameState originalGame, testGame;

    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numberOfPlayers = 2;
    int player = 0;
    int seed = 1000;
    int supplyPos = 1;
    int gainCardOutput;
    int supplyCountBefore;
    
    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand
    int toFlag = 1;
    
    
    // need to clear the game state??
    

    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // ----------- TEST 1: No cards left in the pile --------------
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.supplyCount[supplyPos] = 0; // you can't get a card if there aren't any cards in the pile
    printf("TEST 1: No cards left in the pile\n");
    assert(gainCard(supplyPos, &testGame, toFlag, player) == -1);

    // ----------- TEST 2: Sending card to deck --------------
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.supplyCount[supplyPos] = 1;
    int deckCountBefore = testGame.deckCount[player];
    supplyCountBefore = testGame.supplyCount[supplyPos];
    gainCardOutput = gainCard(supplyPos, &testGame, 1, player); // toFlag = 1
    printf("TEST 2: Sending card to deck\n");
    printf("deck count = %d, expect = %d\n", testGame.deckCount[player], deckCountBefore + 1);
    printf("Last card in deck = %d, expect = %d\n", testGame.deck[player][testGame.deckCount[player] - 1], supplyPos);
    printf("supply count = %d, expect = %d\n", testGame.supplyCount[supplyPos], supplyCountBefore - 1);
    
    assert(testGame.deckCount[player] == deckCountBefore + 1);
    assert(testGame.deck[player][testGame.deckCount[player] - 1] == supplyPos);
    assert(testGame.supplyCount[supplyPos] == supplyCountBefore - 1);
    assert(gainCardOutput == 0);
    
    // ----------- TEST 3: Sending card to hand --------------
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.supplyCount[supplyPos] = 1;
    int handCountBefore = testGame.handCount[player];
    supplyCountBefore = testGame.supplyCount[supplyPos];
    gainCardOutput = gainCard(supplyPos, &testGame, 2, player); //toFlag = 2
    printf("TEST 3: Sending card to hand\n");
    printf("hand count = %d, expect = %d\n", testGame.handCount[player], handCountBefore + 1);
    printf("Last card in hand = %d, expect = %d\n", testGame.hand[player][testGame.handCount[player] - 1], supplyPos);
    printf("supply count = %d, expect = %d\n", testGame.supplyCount[supplyPos], supplyCountBefore - 1);
    
    assert(testGame.handCount[player] == handCountBefore + 1);
    assert(testGame.hand[player][testGame.handCount[player] - 1] == supplyPos);
    assert(testGame.supplyCount[supplyPos] == supplyCountBefore - 1);
    assert(gainCardOutput == 0);
    
    
    // ----------- TEST 4: Sending card to hand --------------
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    testGame.supplyCount[supplyPos] = 1;
    int discardCountBefore = testGame.discardCount[player];
    supplyCountBefore = testGame.supplyCount[supplyPos];
    gainCardOutput = gainCard(supplyPos, &testGame, 0, player); //toFlag = 0
    printf("TEST 4: Sending card to discard\n");
    printf("discard count = %d, expect = %d\n", testGame.discardCount[player], discardCountBefore + 1);
    printf("Last card in discard = %d, expect = %d\n", testGame.discard[player][testGame.discardCount[player] - 1], supplyPos);
    printf("supply count = %d, expect = %d\n", testGame.supplyCount[supplyPos], supplyCountBefore - 1);
    
    assert(testGame.discardCount[player] == discardCountBefore + 1);
    assert(testGame.discard[player][testGame.discardCount[player] - 1] == supplyPos);
    assert(testGame.supplyCount[supplyPos] == supplyCountBefore - 1);
    assert(gainCardOutput == 0);
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);
    
    return 0;
}
