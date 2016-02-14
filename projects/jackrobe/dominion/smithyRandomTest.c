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
//
//
//
//
//
//
//
//void printHand(int player, struct gameState *game) {
//    int handCount = game->handCount[player];
//    int handIndex;
//    printf("Player %d's hand:\n", player);
//    if(handCount > 0) printf("#  Card\n");
//    for(handIndex = 0; handIndex < handCount; handIndex++) {
//        int card = game->hand[player][handIndex];
//        char name[MAX_STRING_LENGTH];
//        cardNumToName(card, name);
//        printf("%-2d %-13s\n", handIndex, name);
//    }
//    printf("\n");
//}
//
//
//
//void printDeck(int player, struct gameState *game) {
//    int deckCount = game->deckCount[player];
//    int deckIndex;
//    printf("Player %d's deck: \n", player);
//    if(deckCount > 0) printf("#  Card\n");
//    for(deckIndex = 0; deckIndex < deckCount; deckIndex++) {
//        int card = game->deck[player][deckIndex];
//        char name[MAX_STRING_LENGTH];
//        cardNumToName(card, name);
//        printf("%-2d %-13s\n", deckIndex, name);
//    }
//    printf("\n");
//}

struct gameState makeRandomState (int players){

    //Set up
    struct gameState G;

    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy};

    int money = 0;
    int smithyPos = -1;
    int adventurerPos = -1;
    int j,p,i=0;

    int numSmithies = 0;
    int numAdventurers = 0;
    int prob, quartprob;
    int maxDeck = MAX_DECK;

    //initialize
    initializeGame(2, k, players, &G);
    srand(time(NULL));

     p= rand()%11;

    //30% of the time the deck is 0
    if(genPro() < 0.3){
        maxDeck = 0;
    }



    //set up a  deck for  each player
    ///randdome to size of deck, discount, or hand
    //add one so that it's not a zeo deck or hand
    for(i=0; i < players-1; i++) {
        srand(time(NULL)+i);
        i=0;
        G.deckCount[i] =  rand()% maxDeck +1;
        for(j=0; j < G.deckCount[i]-1; j++){
            srand(time(NULL)+j);
            G.deck[i][j] = rand()%11;
        }

        G.discardCount[i] = rand()% maxDeck;
        for(j=0; j < G.discardCount[i]-1; j++){
            srand(time(NULL)+j);
            G.discard[i][j] = rand()% 11;

        }

        G.handCount[i] = floor(rand()% maxDeck +1);
        for(j=0; j < G.handCount[i]-1; j++){
            srand(time(NULL)+j);
            G.hand[i][j] = rand()% 11;
        }
    }

return G;
}


int testSmithy(struct gameState *state ){

    //set some beginning vars
    int currentPlayer = whoseTurn(state);
    int beginHandCount = state->handCount[currentPlayer];
    int handPos = rand()% state->handCount[currentPlayer]+1;

    struct gameState preState;
    preState = *state;

    struct capture report;

    int status = 0;
    int i;
    int seed = time(NULL);
    srand(seed);
    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);
    assert(handPos > 0);


    //put the smithy card in the random hand position
    state->deck[currentPlayer][handPos] = smithy;

    //run smithy
    smithyCard(state, handPos);

    //smithy should draw three cards
    //But discard the card being used for a net gain of 2 to the current hand.
    if(state->handCount[currentPlayer] != beginHandCount+2){
        status++;
        printf("BeginHand Count was: %i \n", beginHandCount);
        printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
        printf("Hand Count should be: %i \n", beginHandCount+2);
    }

    //make sure smithy was "discarded" i.e. set to -1
    if(state->hand[currentPlayer][handPos] == smithy){
        status++;
        printf("Actual card in hand was: %i \n", state->hand[currentPlayer][handPos]);
        printf("Hand Count should be: %i \n", -1);

    }

    //make sure correct deck cards were drawn
    if(state->hand[currentPlayer][state->handCount[currentPlayer] -1] != preState.deck[currentPlayer][preState.deckCount[currentPlayer]-2]){
        status++;
        printf("Actual card in hand was: %i \n", state->hand[currentPlayer][state->handCount[currentPlayer] -1]);
        printf(" should be: %i \n", preState.deck[currentPlayer][preState.deckCount[currentPlayer]-2]);
    }
    if(state->hand[currentPlayer][state->handCount[currentPlayer] -2] != preState.deck[currentPlayer][preState.deckCount[currentPlayer]-1]){
        status++;
        printf("Actual card in hand was: %i \n", state->hand[currentPlayer][state->handCount[currentPlayer] -2]);
        printf(" should be: %i \n", preState.deck[currentPlayer][preState.deckCount[currentPlayer]-1]);
    }

    //printf("%i", seed);
    report.status = status;
    report.badSeed = seed;

    return status;
}


int main(int argc, char** argv) {

    int n;

    struct gameState G;

    //G = makeRandomState(atoi(argv[1]));
    int maxTestsFailed =0;
    int badSeed = 0;
    int testResult = 0;
    int totalFailed =0;
    printf("\n\nTESTING Smithy CARD: ------------------ \n");
    for (n = 0; n < 1000; n++) {
        srand(time(NULL));
        struct gameState G;

        G = makeRandomState(atoi(argv[1]));

        testResult = testSmithy(&G);

        if (testResult == 0) {
            printf("testSmithy: OK\n");

        } else {
            printf("FAILED : %i tests \n", testResult);
            maxTestsFailed = MAX(maxTestsFailed, testResult);
            printf("Most Failed : %i tests \n", maxTestsFailed);
            printf("Total Failed : %i tests of %i \n", totalFailed, n);
            totalFailed++;
            //printf("BadSeed : %i  \n", badSeed);
        }

    }
//    int i;
//    for(i =0; i < 2000; i++){
//
//        int p = Random() * 11;
//        printf("%i\n",p);
//    }

return 0;
}