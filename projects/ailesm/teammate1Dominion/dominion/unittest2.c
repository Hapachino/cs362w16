//*********************************************
//a program to test the function updateCoins() from
//dominion as implemented in dominion.c using
//randomized inputs.
//Author: Michael Byrne, OSU byrnemi
//For: CS 362 Software Engineering 2
//Sources: na
//*********************************************
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>

int main (int argc, char** argv) {
    struct gameState G;
    int player = 0;
    int coinCard;
    int m;
    int errors = 0;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};


//------------------- end prologue, begin tests: 20000 randomized tests of 50 card hands --------------//

    printf("starting testing for updateCoins function\n");

    for (m;m<200;m++){
        initializeGame(2, k, 2, &G);

        int i = 0;
        int j = 0;
        int testTotal = 0;
        //prep random function
        SelectStream(1);
        PutSeed(2);
        //pick player randomly
        player = floor(Random()*2);

        //only testing for max 50 cards in hand because the test assigns coin cards with .75 probability
        // rather than ~.2 with all possible cards in hand
        G.handCount[player] = 50;
        //here we assign each card as either a coin or a 0 and keep a running tally of total values
        for (i;i<50;i++){
            coinCard = floor(Random()*4);
            //if verbose
            //printf("card picked: %d\n",coinCard);
            if (coinCard == 0){
                G.hand[player][i] = copper;
                testTotal += 1;
            }
            else if (coinCard == 1){
                G.hand[player][i] = silver;
                testTotal += 2;
            }
            else if (coinCard == 2){
                G.hand[player][i] = gold;
                testTotal += 3;
            }
            else
                G.hand[player][i] = 0;
        }

        if(updateCoins(player,&G,0)!=0){
            printf("updatecoins has returned with an error code\n");
            errors++;
        }
        if(testTotal != G.coins){
            printf("coin value mismatch\n");
            errors++;
        }
    }

printf("testing complete! %d errors\n",errors);





  return 0;
}
