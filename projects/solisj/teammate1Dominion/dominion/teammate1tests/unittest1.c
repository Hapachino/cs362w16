#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include "test_helper.h"
#include <math.h>

#define DEBUG 0


void randomizeDeck(struct gameState *game);
void unittest1(long seed);


/**************************************
 * To test the shuffle function, we're going to
 * Randomize the number of players
 * randomize the number of
 * cards in the deck for each player.
 *
 * We're going to randomize the cards in the deck, 
 * we're going to set the control and tester equal
 * then we're going to shuffle the tester
 * and compare the results with the control.
 *
 * Specifically, we're going to shuffle each player's deck one at a time
 * and confirm that the indicated player's deck is shuffled, but none
 * of the other player's deck has been shuffled.
 * Let's have some fun.
 *
 * Since we're using randomized testing, we've 
 * added assertions through our code to add confidence
 * that reported errors are part of the unit under test and 
 * not the test harness.
 * *************************************/
void unittest1(long seed)
{
    int i, j, m, res;
    int count, fail;
    count = 1000;
    fail = 0;
    res = 0;
    //run this test suite 10000 times
    for (int t = 0; t < 10000; t++)
    {
        int k[10];
        randomizeKingdomCards(k);
        
        struct gameState Tester;
        struct gameState Control;

        int numPlayers = floor(Random() * (MAX_PLAYERS - 2) + 2);
        assert(numPlayers >= 2 && numPlayers <=4);
        
        initializeGame(numPlayers, k, seed, &Tester);


        //set random number of cards in each player hand
        for (i = 0; i < Tester.numPlayers; i++){
        Tester.deckCount[i] = 0;
        while(Tester.deckCount[i] < 10) 
            Tester.deckCount[i] = ((Random() * MAX_DECK) + 10);
        
        //shuffle is returning deckCounts of 0, so we add this 
        //assertion to ensure it's not a randomization problem.
        assert(Tester.deckCount[i] >= 10);
        //check for how shuffle handles deckCount = 0;
        if (t % 100 == 0) Tester.deckCount[i] = 0;

        //Randmize the card selection
        for (j = 0; j < Tester.deckCount[i] ; j++)
        {
            Tester.deck[i][j] = (Random() * 26);
        }
    }

    //we shuffle the cards for each player in turn.
    for(i = 0; i < Tester.numPlayers; i++){
        
        memcpy(&Control, &Tester, sizeof(Control));
        res = shuffle(i, &Tester);
        if (res == -1 && Tester.deckCount[i] != 0){
            printf("\tPlayers: %d\tPlayer#: %d, Deck Count: %d\n",
                    Tester.numPlayers, i, Tester.deckCount[i]);
            fail++;
        } 
        else if (res != -1 && Tester.deckCount[i] == 0) {
            printf("Didn't exit on deck.count == 0\n");
            fail++;
        }
        if (res == -1) continue;

        //check that player i's deck shuffled
        for (j = 0; j < Tester.deckCount[i]; j++){
            if (Tester.deck[i][j] != Control.deck[i][j])
                j = Tester.deckCount[i];
            else if ((j == Tester.deckCount[i] -1) &&
                    Tester.deck[i][j] == Control.deck[i][j]){
                fail++;
                printf("Didn't shuffle.");
                printf("\tPlayers: %d\tPlayer#: %d, Deck Count: %d\n", 
                        Tester.numPlayers, i, Tester.deckCount[i]);
            }
        }
        //Check that other players' decks did not get shuffled.
        for (j = 0; j < Tester.numPlayers; j++){
            if (j != i){
                for (m = 0; m < Tester.deckCount[j]; m++){
                    if (Tester.deck[j][m] != Control.deck[j][m]){
                        fail++;
                        printf("Shuffled the wrong deck.");
                        printf("\tPlayers: %d\tPlayer#: %d, Deck Count: %d\n",
                                Tester.numPlayers, j, Tester.deckCount[j]);
                        break;
                        
            }
        }

        }
    }
 }
}      

        printf("Shuffle results: Tests: %d\tPassed: %d\tFailed: %d\n", count, count-fail, fail);
}


