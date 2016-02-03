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

//trashon Trash Off
int tesTrash(int cPlayer, struct gameState *state, struct gameState preState, int status, int handPos){

    //check the the right card went it
    if(state->playedCards[state->playedCardCount-1] != preState.hand[cPlayer][handPos]){
        status++;
        printf("Trash Failed - no match");
        printf("PlayedCard  is: %i, but should have been %i\n",state->playedCards[state->playedCardCount],  preState.hand[cPlayer][handPos]);
    }

    //make sure the counts change
    if(state->playedCardCount != preState.playedCardCount+1){
        status++;
        printf("Trash Failed - played cards not increased\n");
        printf("playerd Card count is %i - Prestate is %i\n\n", state->playedCardCount, preState.playedCardCount+1);
    }
    return status;
}

// discardCard
int testDiscardCard(int cPlayer, struct gameState *state, int trash ) {

    //set some beginning vars
    int i,k;
    int status = 0;
    struct gameState preState;
    preState = *state;

    struct gameState alterState;

    assert(state->handCount[cPlayer] > 0);

    //use the end card in the players deck
    discardCard(state->handCount[cPlayer]-1, cPlayer, state, trash);

    if(state->handCount[cPlayer] != preState.handCount[cPlayer] -1){
        status++;
        printf("Last Card Removal Failed\n" );
        printf("handCount is: %i, but should have been %i\n\n",state->handCount[cPlayer], preState.handCount[cPlayer]-1);

    }

    if(trash == 0){
        tesTrash(cPlayer, state, preState, status, preState.handCount[cPlayer]-1 );
    }


     //use all but last one
    for(i = 0; i < state->handCount[cPlayer]-1; i++) {
        assert(state->handCount[cPlayer] >= 2);

        alterState = *state; // capture the state
        discardCard(i, cPlayer, state, trash);


        //check card position is replaced correctly
        if(state->hand[cPlayer][i] != alterState.hand[cPlayer][ (alterState.handCount[cPlayer] - 1)]){
            status++;
            printf("Hand position replacement %i Failed\n", i );
            printf("Hand position is: %i, but should have been %i\n\n",state->hand[cPlayer][i], alterState.hand[cPlayer][ (alterState.handCount[cPlayer] - 1)]);

        }


        //check that last card was changed to minus -1
        if(state->hand[cPlayer][state->handCount[cPlayer]+1] != -1){
            status++;
            printf("Hand with %i not set to -1\n", i );
            printf("Handpos is: %i, but should have been -1\n\n", state->hand[cPlayer][i]);
        }

        //check hand count
        if(state->handCount[cPlayer] != alterState.handCount[cPlayer]-1){
            status++;
            printf("Hand Count %i Failed", i );
            printf("handCount is: %i, but should have been %i\n\n",state->handCount[cPlayer], alterState.handCount[cPlayer]-1);

        }



        if(trash == 0){
            tesTrash(cPlayer, state, alterState, status, i);
        }

    }


    //use the last card in the deck
    //set it to 0
    state->handCount[cPlayer] = 1;
    alterState = *state;
    discardCard(state->handCount[cPlayer]-1, cPlayer, state, 1);
    if(state->handCount[cPlayer] != alterState.handCount[cPlayer] -1){
        status++;
        printf("Last Card Removal Failed\n" );
        printf("handCount is: %i, but should have been %i\n",state->handCount[cPlayer], alterState.handCount[cPlayer]);

    }

    if(state->handCount[cPlayer] != 0){

        status++;
        printf("Hand Count not 0" );
        printf("handCount is: %i, but should have been 0\n",state->handCount[cPlayer]);

    };

    //reup the count because we never took car of position 1
    state->handCount[cPlayer] = 1;
    discardCard(1, cPlayer, state, 1); // get rid of last card

    //Make sure all positions were set to -1;
    for(i = 0; i < preState.handCount[cPlayer]; i++){

        if(state->hand[cPlayer][i] != -1){
            status++;
            printf("All positions not -1" );
            printf("handpos is: %i, but should have been -1\n",state->hand[cPlayer][i]);
            //printHand(cPlayer, state);
            for(i=0; i < preState.handCount[cPlayer]; i++){
                printf("its: %i, but should have been -1\n",state->hand[cPlayer][i]);
            }
        }
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
    struct gameState iniState;
    iniState = G;


    printf ("\n\nTESTING discardCard: ------------------ \n");
    //TEst with trash on
    int testResult = testDiscardCard( currentPlayer, &G, 0);
    if( testResult == 0){
        printf ("test discardCard with Trash on: OK \n");

    }else{
        printf ("FAILED : %i tests", testResult );
    }


    int result = testDiscardCard( currentPlayer, &iniState, 1);
    if( result == 0){
        printf ("test discardCard with Trash off: OK \n");

    }else{
        printf ("FAILED : %i tests", result );
    }

return 0;
}