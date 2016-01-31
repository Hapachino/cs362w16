/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
 *      gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int success;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    //create an array to hold four integer inputs
    int input[4];
    //randomly generate 4 ints
    for(int i=0; i<4; i++){
        input[i]= rand();
    }

    //call function
    printf("About to call Play card \n");

    success=playCard(input[0],input[1],input[2],input[3], post);
    printf("Play card called \n");
    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);

    //assert (success==0);
    if (success == -1){
        #if (NOISY_TEST == 1)
        printf ("Error in playCard function bad exit status.\n");
        #endif
        return 1;
    }

    //specific function check 
    //confirm that actions is one less
    if (pre.numActions != post->numActions+1){
        #if (NOISY_TEST == 1)
        printf("Error action count was not decrimented");
        #endif    
        return 2;
    }
    return 0;
}

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    printf ("TESTING updateCoins():\n");
    for (p = 0; p < numPlayer; p++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                #if (NOISY_TEST == 1)
                printf("Test player %d with %d treasure card(s) and %d bonus.\n", p, handCount, bonus);
                #endif
                memset(&G, 23, sizeof(struct gameState));   // clear the game state
                r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[p] = handCount;                 // set the number of cards on hand
                printf("function call \n");
                //Call function
                unitTest(&G);

            }
        }
    }
    printf("All tests passed!\n");

    return 0;
}
