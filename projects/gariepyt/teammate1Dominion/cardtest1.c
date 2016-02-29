/*
**Card test 1: Adventurer
**Written by: Tom Gariepy
**CS 325 Winter 2016
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

/*void playAdventurerCard(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int * temphand, int z)*/

int main(int argc, char const *argv[]) {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int p, r, handCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

    // arrays of all adventurers
    int ads[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        ads[i] = adventurer;
    }

    printf ("TESTING adventurer card:\n");
    for (p = 0; p < numPlayer; p++) {
    	for (handCount = 1; handCount <= maxHandCount; handCount++) {
    		printf("Test player %d playing adventurer card, hand size: %d\n", p, handCount);
    		
    		memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            G.whoseTurn = p;
            G.handCount[p] = handCount;
            memcpy(G.hand[p], ads, sizeof(int) * handCount);

            r = playCard(0, 0, 0, 0, &G);

            printf("G.handCount = %d, %d <= expected <= %d\n", G.handCount[p], handCount - 1, handCount + 1);

            if (G.handCount[p] >= handCount - 1 && G.handCount <= handCount + 1) {
            	printf("The adventure card worked correctly\n");
            }
            else {
            	printf("The adventure card did not work correctly\n");
            }
    	}
    }


	return 0;
}