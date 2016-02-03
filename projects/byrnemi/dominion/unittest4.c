
//*********************************************
//a program to test the function isgameover() from
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
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    //printf ("Starting game.\n");

    int i = 0;
    int j = 0;
    int m = 0;
    int errors = 0;
    int overFlag;
    int testOverFlag;
    int randomSupply;
    SelectStream(1);
    PutSeed(2);
//------------------- end prologue, begin tests: 100 randomized tests  --------------//

printf("starting testing for supplyTest function\n");

    int supplyTest[treasure_map];
    for (i;i<100;i++){
        overFlag = 0;
        testOverFlag= 0;
        int count = 0;
        initializeGame(2, k, 2, &G);
        for (j;j<27;j++){
            randomSupply = floor(Random() * 5);
            supplyTest[j] = randomSupply;
            G.supplyCount[j] = randomSupply;
            if (G.supplyCount[j] == 0){
                count++;
            }
            if (G.supplyCount[province]==0){
                count =3;
                printf("province hit\n");
            }
            if (count == 3){
                testOverFlag = 1;
                break;
            }
            //if verbose
            //printf("assigned supply of %d to %d\n",randomSupply,j);
        }
        overFlag = isGameOver(&G);
        //printf("comparing state flag %d to %d sim\n",overFlag,testOverFlag);
        if(testOverFlag != overFlag){
            printf("failure at testFlag == overFlag\n");
            errors++;
        }

    }

printf("testing complete! %d errors\n",errors);



  return 0;
}
