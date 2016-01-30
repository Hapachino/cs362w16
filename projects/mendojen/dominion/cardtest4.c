/* -----------------------------------------------------------------------
 * Demonstration of how to write unit tests for dominion-base
 * Include the following lines in your makefile:
 *
 * playAdventurer: cardtest4.c dominion.o rngs.o
 *      gcc -o card4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
	int j;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int drawntreasure = 0;
    srand(time(NULL));

    printf ("TESTING adventurer():\n");

    //testing Copper
    printf("Testing Copper\n");

 

    return 0;
}

