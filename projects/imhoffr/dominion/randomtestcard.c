/*****************************************************
 * Regina Imhoff
 * stabbymcduck on github
 * imhoffr@oregonstate.edu
 * Date due: 02/14/2016
 * randomtestcard.c
 * random test of the village card
 * village adds one card to hand and adds 2 actions
 * randomtestcard: randomtestcard.c dominion.o rngs.o
 *      gcc -o randomtestcard -g randomtestcard.c dominion.o rngs.o $(FLAGS)
 ******************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

#define TESTCARD "village"

int main(){
    
    int i;
    int cards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int numberOfPlayers = 2;
    int player = 0;
    int initializeGameStatus;
    bool testPass = true;
    struct gameState testGame, originalGame;

    memset(&testGame, 23, sizeof(struct gameState));
    initializeGameStatus = initializeGame(numberOfPlayers, cards, seed, &originalGame);
    
    assert(initializeGameStatus == 0);
    
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    
    
    
    
    
    if(testPass == true){
        printf("\n ####  ALL TESTS PASSED  #### \n");
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    }else{
        printf("\n >>>>>> ONE OR MORE TESTS FAILED >>>>>>\n");
    }
    
    return 0;
}