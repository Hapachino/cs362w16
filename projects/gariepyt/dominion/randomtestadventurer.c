/*
**Random test adventurer
**Written by: Tom Gariepy
**CS 325 Winter 2016
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

/* NOTE: need to make this random */
int main(int argc, char const *argv[]) {
    time_t curSeed = time(NULL);

    srand((unsigned int)curSeed);

    int result = 1;

    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    // int maxHandCount = 5;

    // arrays of all adventurers
    int ads[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        ads[i] = adventurer;
    }

    printf ("TESTING adventurer card with seed: %d\n", (unsigned int)curSeed);
    while (result < 100) {
        numPlayer = rand() % (MAX_PLAYERS - 2) + 2;
        p = rand() % numPlayer;
        handCount = rand() % 9 + 2;

    	printf("Test #%d: %d players, player %d playing adventurer card, hand size: %d\n", result, numPlayer, p, handCount);
    		
    	memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;
        G.handCount[p] = handCount;
        memcpy(G.hand[p], ads, sizeof(int) * handCount);

        r = playCard(0, 0, 0, 0, &G);

        printf("G.handCount = %d, %d <= expected <= %d\n", G.handCount[p], handCount - 1, handCount + 1);

        if (G.handCount[p] >= handCount - 1 && G.handCount[p] <= handCount + 1) {
    	   printf("The adventure card worked correctly\n");
           result++;
        }
        else {
    	   printf("The adventure card did not work correctly\n");
           // result = 0;
           result++;
        }
    }	
	
	return 0;
}