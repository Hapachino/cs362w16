//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

int testSmithy(struct gameState *state ){

    //set some beginning vars
    int currentPlayer = whoseTurn(state);
    int beginHandCount = state->handCount[currentPlayer];
    int handPos = state->handCount[currentPlayer]-1; // at the end of the handcount I hope
    int status = 0;
    int i;
    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);
    assert(handPos > 0);

    //stack the deck
    for(i = 0; i > state->deckCount[currentPlayer]; i++ ){

        state->deck[currentPlayer][i] = gold;
    }

    //run smithy
    smithyCard(state, handPos);

    //smithy should draw three cards
    //But discard the card being used for a net gain of 2 to the current hand.
    if(state->handCount[currentPlayer] != beginHandCount+2){
        status++;
        printf("BeginHand Count was: %i \n", beginHandCount);
        printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
        printf("Hand Count should be: %i \n", beginHandCount+2);
        status ++;
    }

    if (status != 0){ // no need to check this if the first part fired and failed.

        int pos1 = state->hand[currentPlayer][state->handCount[currentPlayer] -1];
        int pos2 = state->hand[currentPlayer][state->handCount[currentPlayer] -2];

        if(state->hand[currentPlayer][state->handCount[currentPlayer] -1] != gold ){
            status++;
            printf("Top Card was not Gold: %i \n", state->hand[currentPlayer][state->handCount[currentPlayer] -1]);
        }

        status ++;
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
    int currentPlayer = whoseTurn(&G);

    int testResult = testSmithy(&G);
    if( testResult == 0){
        printf ("testSmithy: OK");

    }else{
        printf ("%i FAIL", testResult);
    }

return 0;
}