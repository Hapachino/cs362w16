//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"

int testAdventurer(struct gameState *state ){

    //set some beginning vars
    int currentPlayer = whoseTurn(state);
    int beginHandCount = state->handCount[currentPlayer];
    int status = 0;
    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);
    int beginDiscardCount = state->discardCount[currentPlayer];
    int i;

    //stack the deck
    for( i = 0; i > state->deckCount[currentPlayer]; i++ ){
        //todo fix this it cannot equal "gold"
        state->deck[currentPlayer][i] = gold;
    }

    //run adventurer
    adventurerCard(state);

    //Adventurer should draw two cards to the deck
    //But discard the card being used for a net gain of 2 to the current hand.
    if(state->handCount[currentPlayer] != beginHandCount+2){
        status ++;
        printf("BeginHand Count was: %i \n", beginHandCount);
        printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
        printf("Hand Count should be: %i \n", beginHandCount+2);
    }

    //Test 1
    //since the entire deck is gold just check to see if
    //the discard count hasn't grown
    if (beginDiscardCount != state->discardCount[currentPlayer] ){
        status++;
        printf("solid gold - discard count mismatch \n");
        printf("BeginDiscard Count was: %i \n", beginDiscardCount);
        printf("Actual Count was: %i \n", state->discardCount[currentPlayer]);
        printf("Hand Count should be same as BeginDiscard \n");
    }


    //Test2
    //Make each card something else other than gold, copper, silver

    //stack the deck
    for(i = 0; i > state->deckCount[currentPlayer]; i++ ){

        state->deck[currentPlayer][i] = estate;
    }

    //run adventurer
    adventurerCard(state);

    if (beginDiscardCount + state->deckCount[currentPlayer] != state->discardCount[currentPlayer] ){
        status++;
        printf("solid estate - discard count mismatch");
        printf("BeginDiscard Count was: %i \n", beginDiscardCount);
        printf("DeckCount was: %i \n", state->deckCount[currentPlayer]);
        printf("Actual Count was: %i \n", state->discardCount[currentPlayer]);
        printf("Hand Count should be %i \n", beginDiscardCount + state->deckCount[currentPlayer]);
    }


    //Test3
    //Case of Empty Deck

    //set deck count = 0
    state->deckCount[currentPlayer] = 0;


    //run adventurer
    int empty = adventurerCard(state);

    if (empty != -1 ){
        status++;
        printf("empty set but still returned value, Expected -1 \n");

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

    int testResult = testAdventurer(&G);
    if( testResult == 0){
        printf ("testAdventurer: OK");

    }else{
        printf ("FAILD : %i tests", testResult );
    }

return 0;
}