//*********************************************
//a program to test the function getCost() from
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
    int randomCard = 0;
    int costOut = 0;
    int i;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    printf ("Starting game.\n");

    initializeGame(2, k, atoi(argv[1]), &G);
    //prep random function
    SelectStream(1);
    PutSeed(2);

    for(i;i<20000;i++){
        //pulls a random card from all possible
        randomCard = floor(Random() * treasure_map);
        //if verbose
        printf("random card: %d\  ",randomCard);
        costOut = getCost(randomCard);
        //if verbose
        printf("cost returned: %d\n",costOut);
        //check with conditionals that function is returning correct cost
        if (randomCard == curse || randomCard == copper)
            assert(costOut == 0);
        else if (randomCard == embargo || randomCard == estate)
            assert(costOut == 2);
        else if (randomCard == ambassador || randomCard == silver || randomCard == great_hall || randomCard == steward || randomCard == village)
            assert(costOut == 3);
        else if (randomCard == feast || randomCard == gardens || randomCard == remodel || randomCard == smithy || randomCard == baron || randomCard == cutpurse || randomCard == salvager || randomCard == sea_hag || randomCard == treasure_map)
            assert(costOut == 4);
        else if (randomCard == duchy || randomCard == council_room || randomCard == mine || randomCard == minion || randomCard == tribute || randomCard == outpost)
            assert(costOut == 5);
        else if (randomCard == adventurer || randomCard == gold)
            assert(costOut == 6);
        else if (randomCard == province)
            assert(costOut == 8);
        else{
            fprintf(stderr, "Invalid card to function...\n");
            exit(-1);
        }

    }

    //here we make sure the function returns -1 on bad input
    for(i;i<20000;i++){
        randomCard = floor(Random() * treasure_map+2);
        //if verbose
        printf("random card: %d\  ",randomCard);
        costOut = getCost(randomCard);
        //verify that function returns -1 on bad input
        if(randomCard < 0 || randomCard > treasure_map)
            assert(costOut == -1);
    }


  return 0;

}
