//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include "interface.h"
#include <time.h>
#include "dominion_helpers.h"
int deckSeed;

struct capture {
    int status;
    int badSeed;

};

float genPro(){

    int prob;
    float ran;
    int i;
    double test = RAND_MAX;

    srand(time(NULL)+i);
    prob = rand();
    ran = prob/test;



    return prob;
};

//http://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))


//Sets up a random card state for each player
void makeRandomState (int players, struct gameState * G){
    int i, j, maxDeck;
    maxDeck = MAX_DECK;
    float l = Random();

    //30% of the time the deck or Hand is 0
    if(l < 0.3){
        maxDeck = 0;
    }

    //set up a  deck for  each player
    ///randdome to size of deck, discount, or hand
    //add one so that it's not a zeo deck or hand
    for(i=0; i < players; i++) {

        G->deckCount[i] =  Random() * maxDeck +1;
        for(j=0; j <  G->deckCount[i]-1; j++){
            G->deck[i][j] = Random() * 19;
        }

        G->discardCount[i] = Random() * maxDeck +1;
        for(j=0; j <  G->discardCount[i]-1; j++){
            G->discard[i][j] = Random() * 19;

        }

        G->handCount[i] = Random() * MAX_HAND +1;
        for(j=0; j <  G->handCount[i]-1; j++){
            G->hand[i][j] = Random() * 19;
        }
    }

}


int testSmithy(struct gameState *state, int currentPlayer, int verbose ){

    //set some beginning vars
    int beginHandCount = state->handCount[currentPlayer];
    int handPos = Random() * state->handCount[currentPlayer]-1;
    struct gameState preState;
    preState = *state;

    struct capture report;

    int status = 0;
    int i;
    int seed = time(NULL);
    srand(seed);
    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);
    assert(handPos >= 0);

    //put the smithy card in the random hand position
    state->deck[currentPlayer][handPos] = smithy;

    //run smithy  int playSmithy(int currentPlayer, struct gameState *state, int handPos)
    playSmithy(currentPlayer, state, handPos);

    //smithy should draw three cards
    //But discard the card being used for a net gain of 2 to the current hand.
    if(state->handCount[currentPlayer] != beginHandCount+2){
        status++;
        if(verbose == 1){
            printf("BeginHand Count was: %i \n", beginHandCount);
            printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
            printf("Hand Count should be: %i \n", beginHandCount+2);
        }else if(verbose == 2){
            printf("HandCount Failed \n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }
    }else{
        if (verbose >= 1) {
            printf("Hand Count Passed:\n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }

    }

    //make sure smithy was "discarded" i.e. set to -1
    if(state->hand[currentPlayer][handPos] == smithy){
        status++;
        if(verbose == 1) {

            printf("Hand Discard Failed\n");
            printf("Actual card in hand was: %i \n", state->hand[currentPlayer][handPos]);
            printf("should be: %i \n", -1);
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);

        }else if(verbose == 2){
            printf(" Hand Discard Failed\n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }
    }else {
        if (verbose >= 1) {
            printf("Hand Discard Passed:\n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }
    }

    //make sure "discard" was increased
    if(state->discardCount[currentPlayer] == preState.discardCount[currentPlayer] +1){
        status++;
        if(verbose == 1) {
            printf("Discard Count Failed\n");
            printf("discard was: %i \n", state->discardCount[currentPlayer]);
            printf("should be: %i \n", preState.discardCount[currentPlayer] +1);
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }else if(verbose == 2){
            printf("Discard Count Failed\n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }
    }else {
        if (verbose >= 1){
            printf("Discard Count Passed\n");
            printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                   preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
        }
    }


    return status;
}


int main(int argc, char** argv) {

    int n, cp;
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    int maxTestsFailed = 0;
    int testResult = 0;
    int totalFailed =0;
    printf ("Starting game. with %i players\n", atoi(argv[1]));

    initializeGame(atoi(argv[1]), k, time(NULL) ,&G);

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int i=0;
    int verbose = atoi(argv[3]);
    int numSmithies = 0;
    int numAdventurers = 0;
    srand(time(NULL));

    printf("\n\nTESTING Smithy CARD: ------------------ \n");

    //Run 100k tests
    //CHECK VERBOSE  is ZERO BEFORE RUNNING HIGH AMOUNTS
    for (n = 0; n < atoi(argv[2]); n++) {

        makeRandomState(atoi(argv[1]), &G);

        //change current player
        //is not working there is a bug with the initialization
        cp = Random()* atoi(argv[1]);

        testResult = testSmithy(&G, cp, verbose);

        if (testResult != 0) {
            totalFailed++;

        }

    }
    if (testResult == 0)
        printf("testSmithy: OK\n");

    printf("Most Failed : %i tests \n", MAX(maxTestsFailed, testResult));
    printf("Total Failed : %i tests of %i \n", totalFailed, n);



return 0;
}