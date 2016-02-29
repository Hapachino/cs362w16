//
// Created by Robert on 2/2/2016.
// Test Gain Card

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdio.h>
#include "interface.h"
#include "rngs.h"

// gain card
int testGainCard(int cPlayer, struct gameState *state ) {

    //set some beginning vars
    int i,k;
    int status = 0;
    int cards = treasure_map - curse;
    int  addHandCount = cards;
    int  addDeckCount = cards;
    int addDiscardCount = cards;
    struct gameState preState;
    preState = *state;

    //put one of each card in the deck hand and discard
    for ( i =0; i < cards; i++){

        int gcDeckResult = gainCard(i, state, 1, cPlayer);

        //if the resource was not there
        //we need to change the count
        if(gcDeckResult == -1){
            addDeckCount--;
        }

        int gcHandResult = gainCard(i, state, 2, cPlayer);

        //if the resource was not there
        //we need to change the count
        if(gcHandResult == -1){
            addHandCount--;
        }

        int gcDisResult = gainCard(i, state, 0, cPlayer);

        //if the resource was not there
        //we need to change the count
        if(gcDisResult == -1){
            addDiscardCount--;
        }


    }

    if(state->deckCount[cPlayer] != preState.deckCount[cPlayer] + addDeckCount){
        status++;
        printf("Deck count is wrong" );
        printf("Deckcount is: %i, but should have been %i\n",state->deckCount[cPlayer],preState.deckCount[cPlayer] + addDeckCount);

    }

    if(state->handCount[cPlayer] != preState.handCount[cPlayer] + addHandCount){
        status++;
        printf("Hand count is wrong" );
        printf("Deckcount is: %i, but should have been %i\n",state->deckCount[cPlayer],preState.deckCount[cPlayer] + addHandCount);

    }

    if(state->discardCount[cPlayer] != preState.discardCount[cPlayer] + addDiscardCount){
        status++;
        printf("Discard count is wrong" );
        printf("Discard is: %i, but should have been %i\n",state->discardCount[cPlayer],preState.discardCount[cPlayer] + addDiscardCount);

    }

    return status;
}


int main(int argc, char** argv) {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    printf ("Starting game.\n");

    initializeGame(2, k, atoi(argv[1]), &G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i=0;

    int numSmithies = 0;
    int numAdventurers = 0;
    srand(time(NULL));
    //VIP Must start at player 0
    int currentPlayer = 0;

    printf ("\n\nTESTING gainCard: ------------------ \n");
    int testResult = testGainCard( currentPlayer, &G );

    if( testResult == 0){
        printf ("test Gain Card: OK \n");

    }else{
        printf ("FAILED : %i tests\n", testResult );
    }

return 0;
}