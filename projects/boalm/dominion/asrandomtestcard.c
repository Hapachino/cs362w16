/*
 * asrandomtestcard.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * asrandomtestcard: asrandomtestcard.c dominion.o rngs.o
 *      gcc -o asrandomtestcard -g  asrandomtestcard.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTCARD "adventurer"

int randomCard() {
    int randNum = rand() % 20;
    //I increased the probality of treasure cards by having them listed twice
    //I guarantee that there is still a large enough chance of less than 2 available to draw.
    int randomCardList[20] = {      
        copper,
        silver,
        gold,
        curse,
        estate,
        duchy,
        province,
        copper,
        silver,
        gold,
        adventurer, 
        embargo, 
        village, 
        minion,    
        mine, 
        cutpurse,
        sea_hag, 
        tribute, 
        smithy, 
        council_room
    };
  return randomCardList[randNum];
}

void randomizeHandCards(struct gameState *testG, int thisPlayer) {
    int i = 1;
    testG->hand[thisPlayer][0] = adventurer;
    for (i = 1; i < testG->handCount[thisPlayer]; ++i){
        testG->hand[thisPlayer][i] = randomCard();
    }
}

void randomizeDiscardCards(struct gameState *testG, int thisPlayer) {
    int i = 0;
    for (i = 0; i < testG->discardCount[thisPlayer]; ++i){
        testG->discard[thisPlayer][i] = randomCard();
    }
}

void randomizeDeckCards(struct gameState *testG, int thisPlayer) {
    int i = 0;
    for (i = 0; i < testG->deckCount[thisPlayer]; ++i){
        testG->deck[thisPlayer][i] = randomCard();
    }
}

void randomizePlayedCards(struct gameState *testG, int thisPlayer) {
    int i = 0;
    for (i = 0; i < testG->playedCardCount; ++i){
        testG->playedCards[i] = randomCard();
    }
}

void randomizeGameState(struct gameState *testG, int thisPlayer) {
    testG->numBuys = rand() % 5 + 1;
    testG->numActions = rand() % 5 + 1;
    testG->coins = rand() % 10;
    
    testG->handCount[thisPlayer] = rand() % 10;  //1 is so we always put the TESTCARD in position 1
    randomizeHandCards(testG, thisPlayer);

    testG->discardCount[thisPlayer] = rand() % 20;
    randomizeDiscardCards(testG, thisPlayer);
    
    testG->playedCardCount = rand() % 10;
    randomizePlayedCards(testG, thisPlayer);
    
    testG->deckCount[thisPlayer] = rand() % 20;
    randomizeDeckCards(testG, thisPlayer);
}

int numTreasureCards(struct gameState *testG, thisPlayer) {
    int treasureCardsFound = 0;
    int i = 0;
    for (i = 0; i < testG->discardCount[thisPlayer]; ++i){
        if(testG->discard[thisPlayer][i] == copper || testG->discard[thisPlayer][i] == silver || testG->discard[thisPlayer][i] == gold) {
            treasureCardsFound += 1;
        }
    }
    for (i = 0; i < testG->deckCount[thisPlayer]; ++i){
        if(testG->deck[thisPlayer][i] == copper || testG->deck[thisPlayer][i] == silver || testG->deck[thisPlayer][i] == gold) {
            treasureCardsFound += 1;
        }
    }
    return treasureCardsFound;
}

void setOracle(struct gameState *testG, struct gameState *oracleG, thisPlayer) {
    //Adventurer will attempt to draw two treasure cards from the deck/discard.
    //The handsize should increase by drawn treasure cards - 1
    //  This can be tested by checking to see if discard + deck is 2 less than previous
    //
    //played cards should increase by 1
    //trashed should be unchanged.  deck + hand + played + discard should be unchanged
    int treasureCards = numTreasureCards(testG, thisPlayer);

    // remove number of drawn treasure cards from discard or deck count
    if( oracleG->discardCount[thisPlayer] >= treasureCards ) {
        oracleG->discardCount[thisPlayer] -= treasureCards;
    } else if( oracleG->deckCount[thisPlayer] >= treasureCards ) {
        oracleG->deckCount[thisPlayer] -= treasureCards;
    } else if ( oracleG->deckCount[thisPlayer] + oracleG->discardCount[thisPlayer] == treasureCards) {
        oracleG->deckCount[thisPlayer] = 0;
        oracleG->discardCount[thisPlayer] = 0;
    } else {
        //deck and discard are 0 so remain unchanged
        //or treasureCards available is 0 so both remain unchanged.
    }

    oracleG->numBuys = treasureCards;  //numBuys is set to the number of treasure cards

    oracleG->playedCardCount += 1;
    oracleG->handCount[thisPlayer] += treasureCards - 1;

}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int drawnCard1 = 0;
    int drawnCard2 = 0;
    srand(time(NULL));

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 645;
    int numPlayers = 2;
    int thisPlayer = 0;
    int otherPlayer = 1;
    struct gameState G, testG, oracleG, beforeG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1: choice1 = 1 = +2 cards --------------
    printf("TEST 1: = Play adventurer card\n");

    // copy a blank gamestate to testG
    memcpy(&testG, &G, sizeof(struct gameState));


    randomizeGameState(&testG, thisPlayer);

    //Set oracleG to values after randomizing gameState
    memcpy(&oracleG, &testG, sizeof(struct gameState));

    //I think beforeG needs to be here, but I don't remember.
    memcpy(&beforeG, &testG, sizeof(struct gameState));

    setOracle(&testG, &oracleG, thisPlayer);

    printf("treasureCardsFound: %d\n", oracleG.numBuys);


    //Perform the test...
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    printf("Stuff %d\n", testG.numBuys);
    printf("Stuff %d, %d, %d, %d, %d, %d, \n", testG.hand[thisPlayer][0], testG.hand[thisPlayer][2], testG.hand[thisPlayer][3], testG.hand[thisPlayer][4], testG.hand[thisPlayer][5], testG.hand[thisPlayer][6]);
    printf("adventurer: %d, silver: %d, gold: %d\n", adventurer, silver, gold);
    testG.hand[thisPlayer][0] = adventurer;
    printf("adventurer: %d\n", testG.hand[thisPlayer][0]);



    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


    return 0;
}


