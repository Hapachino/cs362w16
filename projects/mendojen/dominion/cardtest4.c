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
	int j,p;
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int drawntreasure = 0;
	
    printf ("TESTING adventurer():\n");
	p=1;
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
	G.handCount[0]=0;
	printf ("****Playing adventurer card 1 time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);

	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);
	
	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);
	
	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);
	
	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);
	
	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);
	
	printf ("****Playing adventurer card another time****\n");
    playAdventurer(&G); 
	printf("Handcount: %d\n", G.handCount[0]);

	printf("Testing completed\n");
    return 0;
}

