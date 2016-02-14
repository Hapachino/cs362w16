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

#define TESTCARD "sea_hag"

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
    testG->hand[thisPlayer][0] = sea_hag;
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

void randomizePlayedCards(struct gameState *testG) {
    int i = 0;
    for (i = 0; i < testG->playedCardCount; ++i){
        testG->playedCards[i] = randomCard();
    }
}

void randomizeGameState(struct gameState *testG, int playerArray[4]) {
    int i = 0;

    testG->playedCardCount = rand() % 10;
    randomizePlayedCards(testG);
    testG->numActions = rand() % 5 + 1;
    testG->coins = rand() % 10;
    
    for (int i = 0; i < 4; ++i)
    {
        
        testG->handCount[playerArray[i]] = rand() % 10 + 1;  //1 is so we always put the TESTCARD in position 1
        randomizeHandCards(testG, playerArray[i]);

        testG->discardCount[playerArray[i]] = rand() % 20;
        randomizeDiscardCards(testG, playerArray[i]);
        
        testG->deckCount[playerArray[i]] = rand() % 20;
        randomizeDeckCards(testG, playerArray[i]);
    }
}

void setOracle(struct gameState *testG, struct gameState *oracleG, int playerArray[4], int currentPlayer) {
    //sea_hag is supposed to remove the top card from the deck of each opposing player and replace it with a curse
    //Deck size should remain unchanged.  
    //  If the deck was empty, it should increase by 1
    //state of current player shouldn't change
    //discard should increase by 1 if deck started not empty
    //total cards will always increse by 1
    int i = 0;
    int thisPlayer = 0;
    for (i = 0; i < 4; ++i)
    {
        thisPlayer = playerArray[i];
        if (thisPlayer == currentPlayer) { //don't do anything for current player
            oracleG->playedCardCount += 1;
            oracleG->handCount[thisPlayer] -= 1;
            continue;
        }

        //increase discard by 1 if deck is not empty
        //move top card to discard
        if(testG->deckCount[thisPlayer] > 0) {
            oracleG->discard[thisPlayer][oracleG->discardCount[thisPlayer]] = oracleG->deck[thisPlayer][oracleG->deckCount[thisPlayer] - 1];
            oracleG->discardCount[thisPlayer] += 1;
        } else {
            //increase deck count to 1
            oracleG->deckCount[thisPlayer]++;
        }
        //set top card to curse
        oracleG->deck[thisPlayer][oracleG->deckCount[thisPlayer] - 1] = curse;
    }
}

int totalCardsInPlay(struct gameState *someG, int thisPlayer) {
    return someG->discardCount[thisPlayer] + someG->playedCardCount + someG->handCount[thisPlayer] + someG->deckCount[thisPlayer];
}

int checkOracle(struct gameState *testG, struct gameState *oracleG, int playerArray[4]) {
    int i = 0;
    int thisPlayer = playerArray[i];

    //test for this player
    if(testG->numActions != oracleG->numActions) 
        return 0;
    if(testG->coins != oracleG->coins)
        return 0;

    //This should indicate that the played card was put in the playedCards pile
    if(testG->playedCardCount != oracleG->playedCardCount)
        return 0;

    for (i = 0; i < 4; ++i)
    {
        thisPlayer = playerArray[i];

        //This should indicate that the correct number of treasure cards were grabbed from the deck/discard
        if(testG->discardCount[thisPlayer] != oracleG->discardCount[thisPlayer])
            return 0;
        //total cards for both oracle and test should be the same
        if(totalCardsInPlay(testG, thisPlayer) != totalCardsInPlay(oracleG, thisPlayer))
            return 0;

        //hand count should be decremented by 1 or unchanged on other players
        if(testG->handCount[thisPlayer] != oracleG->handCount[thisPlayer]) 
            return 0;

        //top card should be curse
        if(testG->deck[thisPlayer][testG->deckCount[thisPlayer]] != oracleG->deck[thisPlayer][oracleG->deckCount[thisPlayer]])
            return 0;

        //top discard card should be curse
        if(testG->discard[thisPlayer][testG->discardCount[thisPlayer]] != oracleG->discard[thisPlayer][oracleG->discardCount[thisPlayer]])
            return 0;

        //check the discard counts match
        if(testG->discardCount[thisPlayer] != oracleG->discardCount[thisPlayer])
            return 0;
    }

    //true
    return 1;
}

void printG(struct gameState *someG, int thisPlayer) {
    if(thisPlayer == 0) {
        printf(" numBuys: %d\n", someG->numBuys);
        printf(" playedCardCount: %d\n", someG->playedCardCount);
        printf(" Total Cards Available: %d\n", totalCardsInPlay(someG, thisPlayer));
    }
    printf(" handCount: %d\n", someG->handCount[thisPlayer]);
    printf(" deckCount: %d\n", someG->deckCount[thisPlayer]);
    printf(" discardCount: %d\n", someG->discardCount[thisPlayer]);
    printf(" Top Card: %d   note: It should be curse if not first player: %d\n", someG->deck[thisPlayer][someG->deckCount[thisPlayer] - 1], curse);
}

void printErrorReport(struct gameState *testG, struct gameState *oracleG, struct gameState *beforeG, int playerArray[4], int i) {
    int j = 0;
    int thisPlayer = 0;
    printf("Test number %d failed.  Report: \n", i);
    for (i = 0; i < 4; ++i)
    {
        thisPlayer = playerArray[i];
        printf("\nbeforeG: (state after randomizing, but before card was played\n");
        printG(beforeG, thisPlayer);
        printf("\ntestG:\n");
        printG(testG, thisPlayer);
        printf("\noracleG:  (note: numBuys = expected treasureCards)\n");
        printG(oracleG, thisPlayer);
    }
    printf("--------------------------------------------------------------\n\n");
}

int main() {
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffledCards = 0;
    int drawnCard1 = 0;
    int drawnCard2 = 0;
    srand(time(NULL));

    int i = 0;
    int failed = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 645;
    int numPlayers = 4;
    int thisPlayer = 0;
    int player2 = 1;
    int player3 = 2;
    int player4 = 3;
    int playerArray[4] = {thisPlayer, player2, player3, player4};
    struct gameState G, testG, oracleG, beforeG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // ----------- TEST 1: choice1 = 1 = +2 cards --------------
    printf("RANDOM TEST : = Play adventurer card\n\n\n");

    for (i = 0; i < 1000000; ++i)
    {

        // copy a blank gamestate to testG
        memcpy(&testG, &G, sizeof(struct gameState));


        randomizeGameState(&testG, playerArray);

        //Set oracleG to values after randomizing gameState
        memcpy(&oracleG, &testG, sizeof(struct gameState));

        //This is so the original state can be printed if there is an error.
        memcpy(&beforeG, &testG, sizeof(struct gameState));

        setOracle(&testG, &oracleG, playerArray, thisPlayer);

        //Perform the test...
        cardEffect(sea_hag, choice1, choice2, choice3, &testG, handpos, &bonus);

        if(!checkOracle(&testG, &oracleG, playerArray)) {
            printErrorReport(&testG, &oracleG, &beforeG, playerArray, i + 1);
            failed++;
        } 
    }
    printf("The test ran %d times and resulted in %d failures.\n", i, failed);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


    return 0;
}


