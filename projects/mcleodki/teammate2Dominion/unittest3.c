/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * unittest3.c
 * Test of updateCoins()
 ******************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNCTION "updateCoins()"

int main(){
    struct gameState originalGame, testGame;
    
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numberOfPlayers = 2;
    int player = 0;
    int seed = 1000;
    int bonus;
    int copperCoin = 1;
    int silverCoin = 2;
    int goldCoin = 3;
    
    initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

    // ----------- TEST 1: coins get reset - if no bonus and handCount --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    int coinsBefore = 1;
    bonus = 0;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 0;
    updateCoins(player, &testGame, bonus);

    printf("Test 1: coins get reset - if no bonus and handCount\n");
    printf("coins = %d, expected = %d\n", testGame.coins, 0);
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == 0);
    
    // ----------- TEST 2: empty hand, 5 bonus coins --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 5;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 0;
    updateCoins(player, &testGame, bonus);
    
    printf("Test 2: empty hand, 5 bonus coins\n");
    printf("coins = %d, expected = %d\n", testGame.coins, bonus);
    
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == bonus);
    
    // ----------- TEST 3: copper coins add 1 --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    coinsBefore = 2;
    bonus = 0;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 1; //add just the copper coin
    testGame.hand[player][0] = copper;
    updateCoins(player, &testGame, bonus);
    
    printf("Test 3: copper coin adds 1\n");
    printf("coins = %d, expected = %d\n", testGame.coins, copperCoin);
    
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == copperCoin);
    
    // ----------- TEST 4: silver coins adds 2 --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 0;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 1;
    testGame.hand[player][0] = silver;
    updateCoins(player, &testGame, bonus);
    
    printf("Test 4: silver coin adds 2\n");
    printf("coins = %d, expected = %d\n", testGame.coins, silverCoin);
    
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == silverCoin);
    
    // ----------- TEST 5: gold coins adds 3 --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 0;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 1;
    testGame.hand[player][0] = gold;
    updateCoins(player, &testGame, bonus);
    
    printf("Test 5: gold coin adds 3\n");
    printf("coins = %d, expected = %d\n", testGame.coins, goldCoin);
    
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == goldCoin);

    // ----------- TEST 6: add 1 copper, 2 silver, 1 gold, one bonus --------------
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 1;
    testGame.coins = coinsBefore;
    testGame.handCount[player] = 4;
    
    int complexCoins = copperCoin + silverCoin + silverCoin + goldCoin + bonus;
    
    testGame.hand[player][0] = copper;
    testGame.hand[player][1] = silver;
    testGame.hand[player][2] = silver;
    testGame.hand[player][3] = gold;

    updateCoins(player, &testGame, bonus);
    
    printf("TEST 6: add 1 copper, 2 silver, 1 gold, one bonus\n");
    printf("coins = %d, expected = %d\n", testGame.coins, complexCoins);
    
    assert(testGame.coins != coinsBefore);
    assert(testGame.coins == complexCoins);
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);
    
    return 0;
}