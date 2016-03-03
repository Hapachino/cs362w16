//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include "interface.h"
#include <time.h>
#include <math.h>
#include "dominion_helpers.h"
//http://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

//Sets up a random state of cards
// stacks the deck to have all cards other than coins
int makeRandomState (int players, struct gameState * G){
    int i, j, maxDeck, maxDisc;
    float l = Random();
    float pro1 = 0.2;
    maxDeck = MAX_DECK;
    maxDisc = MAX_DECK;

    //20% of the time the deck or discard or Hand is 0
    if(l < 0.2){
        maxDeck = 0;
       // printf("  set maxDeck  ");
    }

    //can't both be 0
    if((l < 0.4) && (maxDeck !=0 )){
        maxDisc = 0;
        //printf("  set maxDisc  ");
    }

    //printf("maxDisc %i , maxDeck %i , rand %f\n", maxDisc, maxDeck, l);
    //set up a  deck for  each player
    ///randdome to size of deck, discount, or hand
    for(i=0; i < players; i++) {

        G->deckCount[i] =  Random() * maxDeck ;
        for(j=0; j <  G->deckCount[i]-1; j++){

            //set the whole deck to something other than treasure
            G->deck[i][j] = Random() * 13 + 7;
        }

        G->discardCount[i] = Random() * maxDisc ;
        for(j=0; j <  G->discardCount[i]-1; j++){

            G->discard[i][j] = Random() * 19;
            //set the whole deck to something other than treasure
            G->deck[i][j] = Random() * 13 + 7;

        }

        G->handCount[i] = Random() * maxDeck +2;
        for(j=0; j <  G->handCount[i]-1; j++){
           // G->hand[i][j] = Random() * 19;
            //set the whole deck to something other than treasure
            G->deck[i][j] = Random() * 13 + 7;
        }
    }
    return 0;

}

int testAdventurer(struct gameState *state, int currentPlayer, int verbose ) {

    //set some beginning vars
    //int currentPlayer = whoseTurn(state);
    int beginHandCount = state->handCount[currentPlayer];
    int beginDeckCount = state->deckCount[currentPlayer];
    int beginDiscardCount = state->discardCount[currentPlayer];
    int status = 0;
    int i;
    struct gameState preState;
    preState = * state;
    assert(currentPlayer >= 0);
    assert(beginHandCount > 0);


    //stack the decks 50% prob  with either 2 treasure cards on top or on bottom
    int topbot = Random() * 2;

    //some trickery because enum doesnt like that damn randumb function
    int sCard =6;
    float cardSet =  floor((Random() * 3)) + 4;
    float randPos =  floor((Random() * state->deckCount[currentPlayer]-2)) + 2;

    if(verbose == 1)
        printf("topbot = %i, cardSet = %i" , topbot, (int)cardSet);

    if (topbot == 1) {

        //bottom two are coin meaning we have to discard most of the deck
        for (i = 0; i < 2; i++) {
            state->deck[currentPlayer][i] = (int)cardSet;
        }

    } else if (topbot == 0){

        //top two are coin meaning we wont discard any in the deck
        for (i = state->deckCount[currentPlayer] - 2; i < state->deckCount[currentPlayer]; i++) {
            state->deck[currentPlayer][i] = (int)cardSet;
        }

        //put them somewhere else in the deck
    }else{

        for (i = (int)randPos; i < (int)randPos+2; i++) {
            state->deck[currentPlayer][i] = (int)cardSet;
        }

    }
    //printDeck(currentPlayer,state );

    //run adventurer int playAdventurer(struct gameState *state, int currentPlayer) {
    playAdventurer(currentPlayer, state);

    if (verbose == 1){
        printf("DECKS ---------------: \n");
        printDeck(currentPlayer, state);
        printf("PERFORMING Tests ---------------: \n");
    }

    if(state->deckCount[currentPlayer] > 0){
        //Adventurer should draw two cards from the deck
        if (topbot == 0) {
            if (state->handCount[currentPlayer] != beginHandCount + 2) {
                status++;
                if (verbose == 1) {
                    printf("FAIL - top: hand count mismatch \n");
                    printf("BeginHand Count was: %i \n", beginHandCount);
                    printf("Actual Hand Count was: %i \n", state->handCount[currentPlayer]);
                    printf("Hand Count should be: %i \n", beginHandCount + 2);
                }else if(verbose == 2){
                    printf("FAIL - top: Hand count mismatch \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }

            } else if (state->deckCount[currentPlayer] != beginDeckCount - 2) {
                status++;
                if (verbose == 1) {
                    printf("FAIL - top: Deck count mismatch \n");
                    printf("Begin DECK Count was: %i \n", beginDeckCount);
                    printf("Actual DECK Count was: %i \n", state->deckCount[currentPlayer]);
                    printf("Hand Count should be: %i \n", beginDeckCount - 2);
                }else if(verbose == 2){
                    printf("FAIL - top: Deck count mismatch \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i Player - %i\n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer], preState.whoseTurn);
                }

            } else if (state->discardCount[currentPlayer] != beginDiscardCount) {
                status++;
                if (verbose == 1) {
                    printf("FAIL - top: discard count mismatch \n");
                    printf("Begin DiscardCount was:\t\t %i \n", beginDiscardCount);
                    printf("actual DiscardCount was:\t\t %i \n",state->discardCount[currentPlayer] );
                } else if(verbose == 2){
                    printf("FAIL - top: discard count mismatch \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }

            }

            else {
                if (verbose >= 1 ) {
                    printf("PASSED Top Draw Test \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }
            }

        } else {

            //Adventurer should draw only the last two cards from the deck
            //Discard Check
            if (state->discardCount[currentPlayer] != beginDiscardCount + beginDeckCount - 2) {
                status++;
                if (verbose == 1) {

                    printf("FAIL - Bottom: discard count mismatch \n");
                    printf("Begin DiscardCount was:\t\t %i \n", beginDiscardCount);
                    printf("Begin DeckCount was:\t\t %i \n", beginDeckCount);
                    printf("Actual Discard Count was:\t %i \n", state->discardCount[currentPlayer]);
                    printf("Actual deck Count was:\t\t %i \n", state->deckCount[currentPlayer]);
                    printf("DiscardCount should be:\t\t %i \n", beginDiscardCount + beginDeckCount);
                    printf("DeckCount should be:\t\t 0 \n");

                }else if(verbose == 2){
                    printf("FAIL - Bottom: discard count mismatch \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }
            }

                //should make hand be equal to beginning hand + 2
            else if (state->handCount[currentPlayer] != beginHandCount + 2) {

                status++;
                if (verbose == 1) {
                    printf("FAIL - Bottom: Hand count mismatch on Hand Count \n");
                    printf("Begin HandCount was:\t\t %i \n", beginHandCount);
                    printf("Actual hand Count was:\t\t %i \n", state->handCount[currentPlayer]);
                    printf("handCount should be:\t\t %i \n", beginHandCount);

                }else if(verbose == 2){
                    printf("FAIL - Bottom: Hand count mismatch on Hand Count \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }

            }

            else if (state->deckCount[currentPlayer] != 0) {
                status++;
                if (verbose == 1) {
                    printf("FAIL - Bottom: DECK COUNT - Deck not Zero \n");
                    printf("Begin DeckCount was:\t\t %i \n", beginDeckCount);
                    printf("Actual deck Count was:\t\t %i \n", state->deckCount[currentPlayer]);
                    printf("DeckCount should be:\t\t 0 \n");
                    printDeck(currentPlayer, state);
                }else if(verbose == 2){
                    printf("FAIL - Bottom: DECK COUNT - Deck not Zero \n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }

            } else {
                if (verbose >= 1) {
                    printf("PASSED Bottom Draw Test\n");
                    printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                           preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
                }
            }

        }
    }else{
        // empty deck scenario functions differently in adventurer
        //when the deck is 0, nothing should get discarded either
        assert(state->deckCount[currentPlayer] == 0);
        if(state->discardCount[currentPlayer] > beginDiscardCount) {
            status++;
            if (verbose == 1) {
                printf("FAIL Empty Deck: Begin DiscardCount was: %i \n", beginDiscardCount);
                printf("Begin DeckCount was: %i \n", beginDeckCount);
                printf("Begin HandCount was: %i \n", beginHandCount);
                printf("Actual Discard Count was: %i \n", state->discardCount[currentPlayer]);
                printf("Actual deck Count was: %i \n", state->deckCount[currentPlayer]);
                printf("Actual hand Count was: %i \n", state->handCount[currentPlayer]);

            }else if(verbose == 2){
                printf("FAIL Empty Deck: Begin DiscardCount was: %i \n", beginDiscardCount);
                printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                       preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
            }
        }else{

            if (verbose >= 1) {
                printf("PASSED \n");
                printf("summary:  DeckCount-%i, DisCC - %i, HandCount - %i \n", preState.deckCount[currentPlayer],
                       preState.discardCount[currentPlayer], preState.handCount[currentPlayer]);
            }
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

    int numSmithies = 0;
    int numAdventurers = 0;
    int verbose = atoi(argv[3]);

    printf("TESTING Adventurer CARD: ------------------ \n");

    //Run 100k tests
    //CHECK VERBOSE  is ZERO BEFORE RUNNING HIGH AMOUNTS
    for (n = 0; n < atoi(argv[2]); n++) {

        testResult =0; // reset

        // establish a random state
        makeRandomState(atoi(argv[1]), &G);

        //change current player
        cp = Random()* atoi(argv[1]);

        testResult = testAdventurer(&G, cp, verbose);
        maxTestsFailed = MAX(maxTestsFailed, testResult);

        if (testResult != 0) {
            totalFailed++;

            if(verbose == 2)
                printf("FAIL Run----: %i ------\n", n);
        }

    }
    if (totalFailed == 0)
        printf("test adventurer: OK\n");

    printf("Most Failed : %i tests \n", maxTestsFailed);
    printf("Total Failed : %i tests of %i \n\n\n", totalFailed, n);

return 0;
}