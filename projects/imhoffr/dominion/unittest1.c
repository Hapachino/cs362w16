/*****************************************************
 * Regina Imhoff
 * imhoffr@oregonstate.edu
 * Date due: 02/02/2016
 * unittest1.c
 * Test of isGameOver()
******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNCTION "isGameOver()"

int main(){
    struct gameState originalGame, testGame;
    
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numberOfPlayers = 2;
    int seed = 1000;
    int i;
    
    // initialize game state and player cards
    initializeGame(numberOfPlayers, cards, seed, &originalGame);

    printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    
    // copy game state to test game
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    
    // ----------- TEST 1: Game is over when no provinces are left --------------

    testGame.supplyCount[province] = 0;
    printf("TEST 1: Game is over when no provinces are left\n");
    assert(isGameOver(&testGame) == 1); // 1 = game is over, 0 = game continues
    
    memcpy(&testGame, &originalGame, sizeof(struct gameState));
    
    testGame.supplyCount[province] = 1;
    
    printf("When there is at least 1 province card:\n");
    
    for(i = 0; i < 25; i++)
    {
        if(i != province){
            testGame.supplyCount[i] = 1; // non zero
        }
    }
    
    // ----------- TEST 2: Game continues when no supply pile is zero --------------
    assert(isGameOver(&testGame) == 0);
    printf("TEST 2: Game continues when no supply pile is zero\n");
    
    // ----------- TEST 3: Game continues when 1 supply pile is zero --------------
    testGame.supplyCount[curse] = 0;
    assert(isGameOver(&testGame) == 0);
    printf("TEST 3: Game continues when 1 supply pile is zero\n");
    
    // ----------- TEST 4: Game continues when 2 supply piles are zero --------------
    testGame.supplyCount[estate] = 0;
    assert(isGameOver(&testGame) == 0);
    printf("TEST 4: Game continues when 2 supply piles are zero\n");
    
    // ----------- TEST 5: Game is over when 3 supply piles are zero --------------
    testGame.supplyCount[duchy] = 0;
    assert(isGameOver(&testGame) == 1);
    printf("TEST 5: Game is over when 3 supply piles are zero");
    
    // ----------- TEST 6: Game is over when 3 or more supply piles are zero --------------
    testGame.supplyCount[copper] =0;
    assert(isGameOver(&testGame) == 1);
    printf("TEST 6: Game is over when 3 or more supply piles are zero\n");
    
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);
    
    return 0;
}
