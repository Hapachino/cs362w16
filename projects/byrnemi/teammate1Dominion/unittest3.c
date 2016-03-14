//*********************************************
//a program to test the function handCard() from
//dominion as implemented in dominion.c using
//randomized inputs.
//Author: Michael Byrne, OSU byrnemi
//For: CS 362 Software Engineering 2
//Sources: na
//*********************************************

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main () {

    int r;
    int errors = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
           remodel, smithy, village, baron, great_hall};

    struct gameState G;

    r = initializeGame(2, k, 1, &G);
    SelectStream(2);
    PutSeed(3);

    printf ("initializeGame(4, k, 1, &G) = %d\n", r);
    assert(r == 0);

    int i =0;
    int j = 0;
    int n = 0;
    int testCard;
    int testPos;
    int stateCard;
    int player = floor(Random()*2);
    int testHand[50];
//------------------- end prologue, begin tests: 1000 randomized tests  --------------//

printf("starting testing for handCard function\n");

    //we test handCard by generating a random hand, storing it locally, adding it to the state, and then retrieving the hand from the
    //state and comparing against the testhand()

    for (i;i<1000;i++){
            for(j;j<50;j++){
                testCard = floor(Random()*treasure_map);
                G.hand[player][j] = testCard;
                testHand[j] = testCard;
                //if verbose
                //printf("added %d at handpos %d\n",testCard,j);
            }
            testPos = floor(Random()*50);
            //if verbose
            stateCard = handCard(testPos,&G);
            //printf("found card %d at position %d\n",stateCard,testPos);
            if(stateCard != testHand[testPos]){
                printf("test hand mismatch\n");
                errors++;
            }
    }


  return 0;
}
